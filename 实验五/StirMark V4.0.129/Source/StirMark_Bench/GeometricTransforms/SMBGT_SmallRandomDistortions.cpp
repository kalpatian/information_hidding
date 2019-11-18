//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBGT_SmallRandomDistortions.cpp
//
// Contents: Implementation of the CSMBGT_SmallRandomDistortions class
//
// Purpose:  See SMBGT_SmallRandomDistortions.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 6 July 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/GeometricTransforms/SMBGT_SmallRandomDistortions.cpp,v 1.18 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <assert.h>
#include <math.h>

// SMB headers
#include "SMBGT_SmallRandomDistortions.h"
#include "SMBDistortionMap.h"
#include "../Base/SMBConfig.h"
#include "../Base/SMBError.h"
#include "../Base/SMBImage.h"
#include "../Base/SMBMemoryException.h"
#include "../Base/SMBFileException.h"



//////////////////////////////////////////////////////////////////////
// Vectorial stuff for geometrical distortion attack
//////////////////////////////////////////////////////////////////////

static inline
void _V(dVector &AB, dVector A, dVector B)
{
  AB.x = B.x - A.x;
  AB.y = B.y - A.y;
}

static inline
void _P(dVector &A, double ax, double ay)
{
  A.x = ax;
  A.y = ay;
}

static inline
void _ADD(dVector &v, dVector v1, dVector v2)
{
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBGT_SmallRandomDistortions::CSMBGT_SmallRandomDistortions(unsigned in_uSeed /* = 0 */)
: m_isRelativeInwards(TRUE),
  m_isRelativeOutwards(FALSE),
  m_dInwards(SMBGT_RNDDIST_INWARDS),
  m_dOutwards(SMBGT_RNDDIST_OUTWARDS),
  m_dBendingFactor(SMBGT_RNDDIST_BENDING_FACTOR),
  m_dRandomFactor(SMBGT_RNDDIST_RANDOM_FACTOR),
  m_dMapAmplitude(SMBGT_RNDDIST_MAP_AMPLITUDE),
#ifdef TEST_DISTORTION
  m_fFrequency(0),
#endif
  m_nType(StirMark3),
  m_dStrength(1),
  m_lCols(0),
  m_lRows(0),
  m_nChannels(1),
  m_RNG(in_uSeed)

{
  m_dvulDev.x = 0; // Upper left corner deviation
  m_dvulDev.y = 0;
  m_dvurDev.x = 0; // Upper right corner deviation
  m_dvurDev.y = 0;
  m_dvllDev.x = 0; // Lower left corner deviation
  m_dvllDev.y = 0;
  m_dvlrDev.x = 0; // Lower right corner deviation
  m_dvlrDev.y = 0;
  m_dvPhase.x = 0; // Phase of the distortions
  m_dvPhase.y = 0;
}


CSMBGT_SmallRandomDistortions::~CSMBGT_SmallRandomDistortions()
{

}


//////////////////////////////////////////////////////////////////////
// Setting functions
//////////////////////////////////////////////////////////////////////

inline
void CSMBGT_SmallRandomDistortions::SetRandomFactor (double in_dRandomFactor)
{
  m_dRandomFactor  = in_dRandomFactor;
}

inline
void CSMBGT_SmallRandomDistortions::SetBendingFactor(double in_dBendingFactor)
{
  m_dBendingFactor = in_dBendingFactor;
}

inline
void CSMBGT_SmallRandomDistortions::SetMapAmplitude (double in_dMapAmplitude) 
{
  m_dMapAmplitude  = in_dMapAmplitude;
}

void CSMBGT_SmallRandomDistortions::SetType(DistortionType in_nType)
{
  m_nType = in_nType;
}

void CSMBGT_SmallRandomDistortions::SetMaxInwardCornerDisplacement(int in_nInwards)
{
  // In this case the input parameter is a percentage of the image size
  assert((in_nInwards >= 0) && (in_nInwards <= 100));

  m_isRelativeInwards = TRUE;
  m_dInwards          = in_nInwards;
}

void CSMBGT_SmallRandomDistortions::SetMaxInwardCornerDisplacement(double in_dInwards)
{
  // In this case the input parameter is a number of pixels
  m_isRelativeInwards = FALSE;
  m_dInwards          = in_dInwards;
}

void CSMBGT_SmallRandomDistortions::SetMaxOutwardCornerDisplacement(int in_nOutwards)
{
  // In this case the input parameter is a percentage of the image size
  assert(in_nOutwards >= 0 && in_nOutwards <= 100);

  m_isRelativeOutwards = TRUE;
  m_dOutwards          = in_nOutwards;
}

void CSMBGT_SmallRandomDistortions::SetMaxOutwardCornerDisplacement(double in_dOutwards)
{
  // In this case the input parameter is a number of pixels
  m_isRelativeOutwards = FALSE;
  m_dOutwards          = in_dOutwards;
}

void CSMBGT_SmallRandomDistortions::SetStrength(double in_dStrength)
{
  if (in_dStrength <= 0)
  {
    SMBWarning("[CSMBGT_SmallRandomDistortions::SetStrength] - The strengh factor must be a positive value for this attack. Using default strength (1).");
    m_dStrength = 1.0;
  }
  else
    m_dStrength = in_dStrength;
}


//////////////////////////////////////////////////////////////////////
// CSMBGT_SmallRandomDistortions::Initialise
//
// Prepare the random distortion parameters according the input
// picture (in particular its size).

void CSMBGT_SmallRandomDistortions::Initialise(const CSMBImage & in_imgOriginal)
{
  // TODO: Error handling
  // Distortions can only be applied on non empty images
  assert(in_imgOriginal.NumberOfColumns() && in_imgOriginal.NumberOfRows());
  m_lCols     = in_imgOriginal.NumberOfColumns();
  m_lRows     = in_imgOriginal.NumberOfRows();
  m_nChannels = in_imgOriginal.NumberOfChannels();

  // Generate new distortion parameters
  if (m_isRelativeInwards)
    m_dInwards  = (m_lCols < m_lRows ? m_lCols : m_lRows) * m_dInwards / 100.0;
  if (m_isRelativeOutwards)
    m_dOutwards = (m_lCols < m_lRows ? m_lCols : m_lRows) * m_dOutwards / 100.0;

  // Experimental...
  m_dBendingFactor *= (m_lCols + m_lRows) / 400.0;

  m_dvulDev.x =  m_RNG.GetDouble() * (m_dInwards + m_dOutwards) - m_dOutwards;
  m_dvulDev.y = -m_RNG.GetDouble() * (m_dInwards + m_dOutwards) + m_dOutwards;
  m_dvllDev.x =  m_RNG.GetDouble() * (m_dInwards + m_dOutwards) - m_dOutwards;
  m_dvllDev.y =  m_RNG.GetDouble() * (m_dInwards + m_dOutwards) - m_dOutwards;
  m_dvurDev.x = -m_RNG.GetDouble() * (m_dInwards + m_dOutwards) + m_dOutwards;
  m_dvurDev.y = -m_RNG.GetDouble() * (m_dInwards + m_dOutwards) + m_dOutwards;
  m_dvlrDev.x = -m_RNG.GetDouble() * (m_dInwards + m_dOutwards) + m_dOutwards;
  m_dvlrDev.y =  m_RNG.GetDouble() * (m_dInwards + m_dOutwards) - m_dOutwards;

  // use new base: usual base for picture where upper left corner
  // is the origin and the y-axis goes down
  m_dvulDev.y = -m_dvulDev.y;
  m_dvllDev.y = -m_dvllDev.y;
  m_dvurDev.y = -m_dvurDev.y;
  m_dvlrDev.y = -m_dvlrDev.y;


  CSMBMemoryException e;      
#if defined VERBOSE
  CSMBImage imgRandomMap;
#endif

  switch(m_nType)
  {
  case Latest:
    try
    {
      // Prepare two distortion maps
	    m_DistMapx.SetRandomParameters();
	    m_DistMapx.Generate(m_lCols, m_lRows, m_RNG, e);
	    m_DistMapy.SetRandomParameters();
	    m_DistMapy.Generate(m_lCols, m_lRows, m_RNG, e);
    }
    catch (CSMBMemoryException *pException)
    {
	    SMBWarning("SMBGT_SmallRandomDistortions::Initialise - Could not generate distortion map. "
		             "Not enough memory. Continue without distortion map.");
	    pException->PrintMsg();
    }
#if (defined _DEBUG) && (defined VERBOSE)
    // Convert one of the distortion maps to a gray
    // scale picture for debugging purpose
    try
    {
	    m_DistMapx.ConvertToImage(imgRandomMap, e);
	    imgRandomMap.Save(SMB_DEFAULT_MAPX_IMAGE, SMB_DEFAULT_MAP_IMAGE_FORMAT);
      
	    m_DistMapy.ConvertToImage(imgRandomMap, e);
	    imgRandomMap.Save(SMB_DEFAULT_MAPY_IMAGE, SMB_DEFAULT_MAP_IMAGE_FORMAT);
	  }
    catch (CSMBMemoryException *pe)
	  {
	    pe->PrintMsg("Could not create the distortion (x or y) map image.");
	  }
    catch (CSMBFileException *pe)
	  {
	    pe->PrintMsg("Could not save the distortion (x or y) map image.");
	  }
#endif // (defined _DEBUG) && (defined VERBOSE)
    break;
  
  case StirMark3:
    // Fall trough

  case StirMark2:
    m_dvPhase.x = PI * m_RNG.GetDouble();
    m_dvPhase.y = PI * m_RNG.GetDouble();
    // Fall trough

  case StirMark1:
    break;
    
  default:
    SMBWarning("Unsupported type used in CSMBGT_SmallRandomDistortions::Initialise()");
  }
}


//////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Distortion function
//
// M = b.(a.A + (1 - a).D) + (1 - b).(a.B + (1 - a).C)
// where A is the lower left corner of the image and other letters are given
// in the clockwise order and where a and b are the coordiantes of M relatively
// to A, B, C and D.

dVector CSMBGT_SmallRandomDistortions::F1(double in_x,  double in_y) const
{
  dVector A, B, C, D, AB, CB, CD, v, P1, f;
  dVector M; // Current pixel

  M.x = in_x;
  M.y = in_y;

  // Bilinear transformation (all m_nType)
  // Coordinates of the corners of the image after
  // distortion expressed in the old base (down Y axis)
  _P(A, m_dvllDev.x * m_dStrength, m_lRows + m_dvllDev.y * m_dStrength);
  _P(B, m_dvulDev.x * m_dStrength, m_dvulDev.y * m_dStrength);
  _P(C, m_lCols + m_dvurDev.x * m_dStrength, m_dvurDev.y * m_dStrength);
  _P(D, m_lCols + m_dvlrDev.x * m_dStrength, m_lRows + m_dvlrDev.y * m_dStrength);
  
  _V(AB, A, B);
  _V(CB, C, B);
  _V(CD, C, D);
  _ADD(v, AB, CD);
  
  P1.x = 1 - M.x / m_lCols;
  P1.y = M.y / m_lRows;
  
  M.x = - P1.x * P1.y * v.x + P1.x * CB.x + P1.y * CD.x + C.x;
  M.y = - P1.x * P1.y * v.y + P1.x * CB.y + P1.y * CD.y + C.y;

  if (m_nType == StirMark2 || m_nType == StirMark3)
  {
    // Global bending to the picture
    if (m_dBendingFactor != 0.0)
    {
      M.x += m_dBendingFactor * m_dStrength * sin(M.y * PI / m_lRows + m_dvPhase.x);
      M.y += m_dBendingFactor * m_dStrength * sin(M.x * PI / m_lCols + m_dvPhase.y);
    }

    // Randomiser: changes slightly the coordinates ot the pixels
    if (m_dRandomFactor != 0.0)
    {
      f.x = floor(m_lCols / 20) / m_lCols;
      f.y = floor(m_lRows / 20) / m_lRows;
      double displacement = m_dRandomFactor * (sin(M.x * 2 * PI * f.x) * 
                                               sin(M.y * 2 * PI * f.y));
      displacement *= m_dStrength;

      M.x += displacement * (1 + m_RNG.GetDouble());
      M.y += displacement * (1 + m_RNG.GetDouble());
    }
  }

  if (m_nType == Latest)
  {
	  M.x += m_dMapAmplitude * m_dStrength * m_lCols / 100 * m_DistMapx((int)in_x, (int)in_y);
	  M.y += m_dMapAmplitude * m_dStrength * m_lRows / 100 * m_DistMapy((int)in_x, (int)in_y);
  }


#if defined(TEST_DISTORTION)
    // Used for testing purpose only.
    M.x += m_dBendingFactor * m_dStrength * sin(M.y * 2 * d.freq * PI / m_lRows);
    M.y += m_dBendingFactor * m_dStrength * sin(M.x * 2 * d.freq * PI / m_lCols);
#endif

    return M;
}


//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>
#include <string.h>

int SMBGT_SmallRandomDistortions_Test()
{
  CSMBImage img;
  CSMBException e;
  CSMBGT_SmallRandomDistortions rnddist1;
  
  try {
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_1);
  }
  catch (CSMBException *) {
    e.PrintMsg();
    return SMBFAILURE;
  }

  rnddist1.Initialise(img);

  // Copy constructor
  CSMBGT_SmallRandomDistortions rnddist2(rnddist1);

  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
