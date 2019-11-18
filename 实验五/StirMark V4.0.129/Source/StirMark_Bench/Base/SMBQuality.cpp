//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBQuality.cpp
//
// Contents: Quality measures.
//
// Purpose:  A few measures to be applied on still images are implemented
//           here: SNR, PSNR.
//           TODO: a special class should be implemented for quality
//                 metrics... for the time being these simple functions
//                 will do
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 25 May 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBQuality.cpp,v 1.15 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <math.h>

// SMB headers
#include "SMBImage.h"
#include "SMBConfig.h"



//////////////////////////////////////////////////////////////////////
double MaxLuminance(const CSMBImage &in_imgI)
{
  double dpMax = 0.0, dpCurrent = 0.0;

  for (uint x = 0; x < in_imgI.NumberOfColumns(); x++)
  {
    for (uint y = 0; y < in_imgI.NumberOfRows(); y++)
    {
      dpCurrent = in_imgI.GetPixelLuminance(x, y);
      if (dpCurrent > dpMax)
        dpMax = dpCurrent;
    } // for y
  } // for x
  
  return (dpMax);
}


//////////////////////////////////////////////////////////////////////
double DotProduct(const CSMBImage &in_imgI, const CSMBImage &in_imgJ)
{
  double dpSum = 0.0, dpLI = 0.0, dpLJ = 0.0;

  if((in_imgI.NumberOfColumns()  != in_imgJ.NumberOfColumns())  ||
     (in_imgI.NumberOfRows()     != in_imgJ.NumberOfRows())     ||
     (in_imgI.NumberOfChannels() != in_imgJ.NumberOfChannels()))
     return 0;

  for (uint x = 0; x < in_imgI.NumberOfColumns(); x++)
  {
    for (uint y = 0; y < in_imgI.NumberOfRows(); y++)
    {
      dpLI = in_imgI.GetPixelLuminance(x, y);
      dpLJ = in_imgJ.GetPixelLuminance(x, y);
      
      dpSum += dpLI * dpLJ;
    } // for y
  } // for x
  return (dpSum);
}

//////////////////////////////////////////////////////////////////////
double Norm2(const CSMBImage &in_imgI)
{
  return DotProduct(in_imgI, in_imgI);
}


//////////////////////////////////////////////////////////////////////
double DiffNorm2(const CSMBImage &in_imgI, const CSMBImage &in_imgJ)
{
  double dpSum = 0.0, dpLI = 0.0, dpLJ = 0.0;

  if((in_imgI.NumberOfColumns()  != in_imgJ.NumberOfColumns())  ||
     (in_imgI.NumberOfRows()     != in_imgJ.NumberOfRows())     ||
     (in_imgI.NumberOfChannels() != in_imgJ.NumberOfChannels()))
     return SMB_MAX_DOUBLE;

  for (uint x = 0; x < in_imgI.NumberOfColumns(); x++)
  {
    for (uint y = 0; y < in_imgI.NumberOfRows(); y++)
    {
      dpLI = in_imgI.GetPixelLuminance(x, y);
      dpLJ = in_imgJ.GetPixelLuminance(x, y);
      
      dpSum += (dpLI - dpLJ) * (dpLI - dpLJ);
    } // for y
  } // for x
  return (dpSum);
}


//////////////////////////////////////////////////////////////////////
// Signal to noise ratio (SNR)
//
//                         N   2
//                        Sum X
//                        i=1  i
// SNR = 10 log_10   ----------------
//                     N           2
//                    Sum (X  - X')
//                    i=1   i    i
// where X_i and and X'_i are the original and modified pixel values and N the
// total number of pixels in the image. SNR is used to measure the signal
// quality.
//////////////////////////////////////////////////////////////////////
double SNR(const CSMBImage &in_imgI, const CSMBImage &in_imgJ)
{
  if((in_imgI.NumberOfColumns()  != in_imgJ.NumberOfColumns())  ||
     (in_imgI.NumberOfRows()     != in_imgJ.NumberOfRows())     ||
     (in_imgI.NumberOfChannels() != in_imgJ.NumberOfChannels()))
     return (-SMB_MAX_DOUBLE);
  
  return (10 * log10(Norm2(in_imgI) / DiffNorm2(in_imgI, in_imgJ)));
}

//////////////////////////////////////////////////////////////////////
// Peak Signal to noise ration (PSNR)
//
//                                2
//                        N  max X
//                            i   i
// PSNR = 10 log_10   ------------------
//                       N           2
//                      Sum (X  - X')
//                      i=1   i    i
// where X_i and and X'_i are the original and modified pixel values and N the
// total number of pixels in the image. SNR is used to measure the visual
// quality, even though it is not monotonically related to subjective visual
// quality.
//////////////////////////////////////////////////////////////////////
double PSNR(const CSMBImage &in_imgI, const CSMBImage &in_imgJ)
{
  if((in_imgI.NumberOfColumns()  != in_imgJ.NumberOfColumns())  ||
     (in_imgI.NumberOfRows()     != in_imgJ.NumberOfRows())     ||
     (in_imgI.NumberOfChannels() != in_imgJ.NumberOfChannels()))
     return (-SMB_MAX_DOUBLE);

    double dpMax = MaxLuminance(in_imgI);
    return (20 * log10(dpMax) +
            10 * log10(in_imgI.NumberOfColumns() * in_imgI.NumberOfRows()) -
            10 * log10(DiffNorm2(in_imgI, in_imgJ)));
}


//////////////////////////////////////////////////////////////////////

#ifdef SMB_CODE_TESTING

#include "SMBException.h"

int SMBQuality_Test()
{
  TString str_img1, str_img2;
  CSMBImage img1, img2;

  cout<<"Enter img1 name:";
  cout.flush();
  cin >> str_img1;
  try
  { 
    img1.Load(str_img1);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
  }

  cout<<"Enter img2 name:";
  cout.flush();
  cin >> str_img2;


  img2.Load(str_img2);
  
  return SMBSUCCESS;
}

#endif // SMB_CODE_TESTING
