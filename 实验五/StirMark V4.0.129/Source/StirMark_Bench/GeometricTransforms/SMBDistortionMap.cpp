//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBDistortionMap.cpp
//
// Contents: Implementation of the CSMBDistortionMap class.
//
// Purpose:  See SMBDistortionMap.h
//
// Created:  Fabien Petitcolas, Microsoft Research, May 2000
//
// Modified:
//
// History:
//
// Copyright (c) 2000-2002, Microsoft Research Ltd , Institut National
// de Recherche en Informatique et Automatique (INRIA), Institut Eurécom
// and the Integrated Publication and Information Systems Institute at
// GMD - Forschungszentrum Informationstechnik GmbH (GMD-IPSI).
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted for non-commercial research and academic
// use only, provided that the following conditions are met:
// 
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer. Each
//   individual file must retain its own copyright notice.
// 
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions, the following disclaimer and the
//   list of contributors in the documentation and/or other materials
//   provided with the distribution.
// 
// - Modification of the program or portion of it is allowed provided
//   that the modified files carry prominent notices stating where and
//   when they have been changed. If you do modify this program you
//   should send to the contributors a general description of the changes
//   and send them a copy of your changes at their request. By sending
//   any changes to this program to the contributors, you are granting a
//   license on such changes under the same terms and conditions as
//   provided in this license agreement. However, the contributors are
//   under no obligation to accept your changes.
// 
// - All non-commercial advertising materials mentioning features or use
//   of this software must display the following acknowledgement:
// 
//     This product includes software developed by Microsoft Research
//     Ltd, Institut National de Recherche en Informatique et Automatique
//     (INRIA), Institut Eurécom and the Integrated Publication and
//     Information Systems Institute at GMD - Forschungszentrum
//     Informationstechnik GmbH (GMD-IPSI).
// 
// - Neither name of Microsoft Research Ltd, INRIA, Eurécom and GMD-IPSI
//   nor the names of their contributors may be used to endorse or
//   promote products derived from this software without specific prior
//   written permission.
// 
// - If you use StirMark Benchmark for your research, please cite:
// 
//     Fabien A. P. Petitcolas, Martin Steinebach, Frédéric Raynal, Jana
//     Dittmann, Caroline Fontaine, Nazim Fatès. A public automated
//     web-based evaluation service for watermarking schemes: StirMark
//     Benchmark. In Ping Wah Wong and Edward J. Delp, editors,
//     proceedings of electronic imaging, security and watermarking of
//     multimedia contents III, vol. 4314, San Jose, California, U.S.A.,
//     20-26 January 2001. The Society for imaging science and
//     technology (I.S.&T.) and the international Society for optical
//     engineering (SPIE). ISSN 0277-786X.
// 
// and
// 
//     Fabien A. P. Petitcolas. Watermarking schemes
//     evaluation. I.E.E.E. Signal Processing, vol. 17, no. 5,
//     pp. 58-64, September 2000.
// 
// THIS SOFTWARE IS NOT INTENDED FOR ANY COMMERCIAL APPLICATION AND IS
// PROVIDED BY MICROSOFT RESEARCH LTD, INRIA, EURÉCOM, GMD-IPSI AND
// CONTRIBUTORS 'AS IS', WITH ALL FAULTS AND ANY EXPRESS OR IMPLIED
// REPRESENTATIONS OR WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE, TITLE OR NONINFRINGEMENT OF INTELLECTUAL
// PROPERTY ARE DISCLAIMED. IN NO EVENT SHALL MICROSOFT RESEARCH LTD,
// INRIA, EURÉCOM, GMD-IPSI OR THEIR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// THE USE OF THIS SOFTWARE FOR CIRCUMVENTING WITHOUT AUTHORITY ANY
// EFFECTIVE TECHNOLOGICAL MEASURES DESIGNED TO PROTECT ANY COPYRIGHTS OR
// ANY RIGHTS RELATED TO COPYRIGHT AS PROVIDED BY LAW OR THE SUI GENERIS
// RIGHT PROVIDED BY SOME COUNTRIES IS STRICTLY PROHIBITED.
//
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/GeometricTransforms/SMBDistortionMap.cpp,v 1.14 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers
// DO NOT USE standard iostream headers (not compatible)
// See: http://www.sgi.com/Technology/STL/
#include <iostream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// Other standard headers
#include <assert.h>
#include <math.h>
#include <stdio.h>
#ifdef WIN32
#define snprintf _snprintf
#endif // WIN32

// SMB headers
#include "SMBDistortionMap.h"
#include "../Base/SMBConfig.h"
#include "../Base/SMBImage.h"


// From LTLib::srfft.c
extern "C"
{
  extern void  srifft(double *xr, double *xi, int logm);
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBDistortionMap::CSMBDistortionMap()
  : m_dRandomness(1),
    m_rgdMap(0),
    m_lCols(0),
    m_lRows(0)
{

}


CSMBDistortionMap::CSMBDistortionMap(const CSMBDistortionMap &in_distMap)
  : m_dRandomness(in_distMap.m_dRandomness),
    m_rgdMap(0),
    m_lCols(in_distMap.m_lCols),
    m_lRows(in_distMap.m_lRows)
{
  if (in_distMap.m_rgdMap != 0)
  {
    m_rgdMap = new double [m_lCols * m_lRows];
    // TODO: CSMBMemoryException...
    memcpy(m_rgdMap, in_distMap.m_rgdMap, m_lCols * m_lRows);
  }
}


void CSMBDistortionMap::SetRandomParameters(double in_dMapRandomness /* = 1 */)
{
  m_dRandomness = in_dMapRandomness;
}


CSMBDistortionMap::~CSMBDistortionMap()
{
  Clear();
}


void CSMBDistortionMap::Clear(void)
{
  if (m_rgdMap != 0)
    delete [] m_rgdMap;

  m_dRandomness = 1;
  m_rgdMap      = 0;
  m_lCols       = 0;
  m_lRows       = 0;
}


//////////////////////////////////////////////////////////////////////
// Purpose:
//   Displays line by line the content of a matrix in a form which can be
//   copied and used in MATLAB
//
// Parameters:
//   double* M      matrix to be displayed
//   int maxi       number of lines
//   int maxj       number of colones
//   char *lprzName name-to-be-displayed of the matrix
//
// Return value:
//   none
//
#ifdef SMB_DISTMAP_DUMP_MATRICES
void CSMBDistortionMap::DumpMatrix(double *in_rgdM, uint in_maxi, uint in_maxj, char *in_szName)
{
	int i, j;
  char szBuff[16];

	cout << endl;
  cout << in_szName << " -------------";
  cout << endl;
	
  cout << "[";
	for (i = 0; i < in_maxi; i++)
	{
		cout << "[";
		for (j = 0; j < in_maxj; j++)
		{
      snprintf(szBuff, 15, "%.8f  ", in_rgdM[i * in_maxj + j]);
		}
		cout << "];" << endl;
	}
	cout << "]" << endl;
}
#endif // DUMP_MATRICES


//////////////////////////////////////////////////////////////////////
// CSMBDistortionMap::Amplitude
//
// Function used for the amplitude of the Fourier transform of the
// distortion map. in_fx and in_fy are the values of the frequencies.

double CSMBDistortionMap::Amplitude(int in_fx, int in_fy, const CSMBRandomNumberGenerator &in_RNG)
{
  if (in_fx == 0 && in_fy == 0)
    return ((double)0);
  else
    return (in_RNG.GetDouble() /
            exp(log(in_fx * in_fx + in_fy * in_fy) * m_dRandomness));
}


//////////////////////////////////////////////////////////////////////
// CSMBDistortionMap::Generate
//
// Generate a random map of size M by N using a given pseudo random
// number generator object by specifying pseudo randomly the
// Fourier transform of this map.

// Since matrices are stored as vector the following macros
// are used to access an element given its 'coordinates' in
// the matrix and its transpose respectively.
#define INDEX(i, j)  ((i) * N2 + (j))
#define INDEXT(i, j) ((i) * M2 + (j))

void CSMBDistortionMap::Generate(uint                          in_N,
                                 uint                          in_M,
                                 CSMBRandomNumberGenerator &   in_RNG,
                                 CSMBMemoryException &      inout_exception)
                                 throw (CSMBMemoryException *)
{
	double *ro, *phi;      // Amplitude and phase
	double *real, *imag;   // Real and imaginary part
	double *realt, *imagt; // Tranpose matrices
  double rmin, rmax;     // Min and max values of the map
	int i, j;
	int log2M, log2N;        // Log base 2 of the final size of the map
  int M2, N2;            // Actual size of the map

  Clear();

	// Get the closest size which is a power ot 2       
	log2M = (int)ceil(log((double)(in_M)) / log(2.0));
	log2N = (int)ceil(log((double)(in_N)) / log(2.0));
	M2 = 1 << log2M;
	N2 = 1 << log2N;

  // To avoid distortions maps that are continuous across the border     
  // warp-around we want the size of the map to be stricly larger than the
  // size of the image to b distorted. Otherwise this warp-around        
  // gives away some information to a potential counter-attack.          
  if (M2 == in_M) { log2M++; M2 *= 2; };
  if (N2 == in_N) { log2N++; N2 *= 2; };

	// Two matrices to store the amplitude and phase
	ro  = new double[N2 * M2];
	phi = new double[N2 * M2];
  if (ro == 0 || phi == 0) goto MemoryException;

	// The following makes sure that some symmetry properties 
	// of the 2D Fourier transform are respected in order to 
	// end up with a real inverse Fourier transform.         
  in_RNG.SetRange(-PI, PI);
	for (i = 1; i < M2 / 2; i++)
	{
		for (j = 1; j < N2 / 2; j++)
		{
			ro[INDEX(i, j)]
				= ro[INDEX(M2 - i, j)]
				= ro[INDEX(M2 - i, N2 - j)]
				= ro[INDEX(i, N2 - j)]
				= Amplitude(i, j, in_RNG);

			phi[INDEX(i, j)]      = in_RNG.GetDoubleInRange();
			phi[INDEX(M2 - i, j)] = in_RNG.GetDoubleInRange();
				
			phi[INDEX(M2 - i, N2 - j)] = - phi[INDEX(i, j)];
			phi[INDEX(i, N2 - j)]      = - phi[INDEX(M2 - i, j)];
		}
	}

	for (i = 1;  i < M2 / 2; i++)
	{
		ro[INDEX(i, 0)]           = Amplitude(i, 0, in_RNG);
    ro[INDEX(M2 - i, 0)]      = ro[INDEX(i, 0)];
		ro[INDEX(i, N2 / 2)]      = Amplitude(i, N2 / 2, in_RNG);
    ro[INDEX(M2 - i, N2 / 2)] = ro[INDEX(i, N2 / 2)];
	}

	for (j = 1;  j < N2 / 2; j++)
	{
		ro[INDEX(0, j)]           = Amplitude(0, j, in_RNG);
    ro[INDEX(0, N2 - j)]      = ro[INDEX(0, j)];
		ro[INDEX(M2 / 2, j)]      = Amplitude(M2 / 2, j, in_RNG);
    ro[INDEX(M2 / 2, N2 - j)] = ro[INDEX(M2 / 2, j)];
	}

	for (i = 1;  i < M2 / 2; i++)
  {
		phi[INDEX(i, 0)]      = in_RNG.GetDoubleInRange();
		phi[INDEX(M2 - i, 0)] = - phi[INDEX(i, 0)];
	}

	for (i = 1;  i < M2 / 2; i++)
  {
		phi[INDEX(i, N2 / 2)]      = in_RNG.GetDoubleInRange();
		phi[INDEX(M2 - i, N2 / 2)] = - phi[INDEX(i, N2 / 2)];
	}

	for (j = 1;  j < N2 / 2; j++)
  { 
		phi[INDEX(0, j)]      = in_RNG.GetDoubleInRange(); 
		phi[INDEX(0, N2 - j)] = - phi[INDEX(0, j)]; 
	}

	for (j = 1;  j < N2 / 2; j++)
  { 
		phi[INDEX(M2 / 2, j)]      = in_RNG.GetDoubleInRange(); 
		phi[INDEX(M2 / 2, N2 - j)] = - phi[INDEX(M2 / 2, j)]; 
	}

	// DC coefficient 
	ro[0] = 0;
	ro[INDEX(0, N2 / 2)] = 0;
	ro[INDEX(M2 / 2, 0)] = 0;
	ro[INDEX(M2 / 2, N2 / 2)] = 0;
	phi[0] = 0;
  phi[INDEX(0, N2 / 2)] = 0;
  phi[INDEX(M2 / 2, 0)] = 0;
  phi[INDEX(M2 / 2, N2 / 2)] = 0;

	// Convert to complex numbers 
	imag = new double [N2 * M2];
	real = new double [N2 * M2];
  if (imag == 0 || real == 0) goto MemoryException;
	for (i = 0; i < M2; i++)
	{
		for (j = 0; j < N2; j++)
		{
			real[INDEX(i, j)] = ro[INDEX(i, j)] * cos(phi[INDEX(i, j)]);
			imag[INDEX(i, j)] = ro[INDEX(i, j)] * sin(phi[INDEX(i, j)]);
		}
	}
	delete [] ro;  ro = 0;
	delete [] phi; phi = 0;

	// Applies the IFFT algorithm to the rows 
	for (i = 0; i < M2; i++)
	{
		srifft(real + INDEX(i, 0), imag + INDEX(i, 0), log2N);
	}

	// Compute the transposed matrix 
	imagt = new double [N2 * M2];
	realt = new double [N2 * M2];
  if (imagt == 0 || realt == 0) goto MemoryException;

	for (i = 0; i < M2; i++)
	{
		for (j = 0; j < N2; j++)
		{
			realt[INDEXT(j, i)] = real[INDEX(i, j)];
			imagt[INDEXT(j, i)] = imag[INDEX(i, j)];
		}
	}
	delete [] imag; imag = 0;
  delete [] real; real = 0;

	// Applies the IFFT to the rows of the transpose 
	for (i = 0; i < N2; i++)
	{
		srifft(realt + INDEXT(i, 0), imagt + INDEXT(i, 0), log2M);
	}
  delete [] imagt; imagt = 0;
    
	// Transpose the real part only as the imaginary part is 0 
  // and extract central part so we get the required size   
  m_lCols = in_N;
  m_lRows = in_M;
  m_rgdMap = new double [in_M * in_N];
  if (m_rgdMap == 0) goto MemoryException;

  for (i = 0; i < in_M; i++)
  {
    for (j = 0; j < in_N; j++)
    {
      m_rgdMap[i * in_N + j] = realt[INDEXT(j + (N2 - in_N) / 2, i + (M2 - in_M) / 2)];
    }
  }
	delete [] realt; realt = 0;

    // Rescale so min is 0 and max is 1 
	rmin = 1;
  rmax = 0;
	for (i = 1; i < in_M * in_N; i++)
	{
		rmin = (m_rgdMap[i] < rmin) ? m_rgdMap[i] : rmin;
		rmax = (m_rgdMap[i] > rmax) ? m_rgdMap[i] : rmax;
	}
	for (i = 1; i < in_M * in_N; i++)
	{
    m_rgdMap[i] = (m_rgdMap[i] - rmin) / (rmax - rmin);
		if (m_rgdMap[i] < 0) { m_rgdMap[i] = 0;}
		if (m_rgdMap[i] > 1) { m_rgdMap[i] = 1;}
	}

  return;

MemoryException:
  delete [] ro;    ro    = 0;
  delete [] phi;   phi   = 0;
  delete [] imag;  imag  = 0;
  delete [] real;  real  = 0;
  delete [] imagt; imagt = 0;
  delete [] realt; realt = 0;
  Clear();

  inout_exception.Throw(CSMBMemoryException::outOfMemory);
}

//////////////////////////////////////////////////////////////////////
// Access to the value of the map
double CSMBDistortionMap::operator()(unsigned in_ulx, unsigned in_uly) const
{
  if (m_rgdMap == 0)
    return 0;
  else
    return *(m_rgdMap + (in_uly * m_lCols + in_ulx));
}


//////////////////////////////////////////////////////////////////////
//
void CSMBDistortionMap::ConvertToImage(CSMBImage             &out_imgRandomMap,
                                       CSMBMemoryException &inout_exception) const
throw (CSMBMemoryException *)
{
  out_imgRandomMap.Initialise(m_lCols, m_lRows, 255, /* TODO: Remove: 1,*/ IT_GRAY, inout_exception);
  
  for (double x = 0; x < m_lCols; x++)
  {
    for (double y = 0; y < m_lRows; y++)
    {
      int id = (int)(y * (double)m_lCols + x);
      out_imgRandomMap.SetPixel((int)x, (int)y, 0, (Gray) floor(255 * m_rgdMap[id]));
    }
  }
}


//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>
#include <string.h>

int SMBDistortionMap_Test()
{
  CSMBRandomNumberGenerator rng;
  CSMBImage img;
  CSMBMemoryException e;
  CSMBDistortionMap distMap1;
 
  try {
    // Generation
    distMap1.Generate(256, 256, rng, e);

    // Conversion to grayscale image
    distMap1.ConvertToImage(img, e);
    img.Save("SMBDistortionMap_Test", "BMP");
  }
  catch (CSMBMemoryException *pException) {
    pException->PrintMsg();
    return SMBFAILURE;
  }

  // Copy constructor
  CSMBDistortionMap distMap2(distMap1);

  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
