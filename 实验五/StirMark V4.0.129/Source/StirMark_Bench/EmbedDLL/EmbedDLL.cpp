//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - EmbedDLL.cpp
//
// Contents: Sample watermarking library for StirMark Benchmark.
//           The scheme simply adds a random pattern to the
//           image. Detection is achieved using linear correlation,
//
// Purpose:  See EmbedDLL.h
//
// Created:  Nazim Fatès, Microsoft Research, 9 May 2000
//
// Modified: Fabien A. P. Petitcolas, Microsoft Research
//
// History:  26 February 2002 - Simplified the scheme to a very basic
//           random pattern embedding / linear correlation detection
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/EmbedDLL/EmbedDLL.cpp,v 1.16 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers - DO NOT USE standard iostream headers (not compatible)
// See: http://www.sgi.com/Technology/STL/
#include <iostream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// Other standard headers
#include <stdlib.h>
#include <math.h>   // for sqrt
#include <assert.h>

// SMB headers
#include "EmbedDLL.h"
#include "../Base/StirMarkBenchmark.h"

// Other defintions
Gray Clip(double x);

ErrorNum StringInfoCopy(STR      out_pbData,
                        uint * inout_pcbData,
                        CSTR      in_pszData);

ErrorNum ValueInfo(STR      out_pbData,
                   uint * inout_pcbData,
                   uint      in_uiValue);




//////////////////////////////////////////////////////////////////////
// Embed a watermark by adding a random pattern to the image
//
// See Base/StirMarkBenchmark.h for function behaviour

ErrorNum Embed_Image_Lib(const SMBImage        in_imgOriginal, // original image
                               SMBImage *     out_pimgTarget,  // image to mark
                         const SMBSchemePars * in_pPars)       // parameters for embedding
{
  assert((out_pimgTarget != NULL) &&
         (out_pimgTarget->pgData != NULL) &&
         (in_imgOriginal.pgData != NULL) &&
         (in_pPars != NULL) &&
         (in_pPars->in_nKeyLength <= SCHEME_MAX_KEY_SIZE) &&
         (in_pPars->in_pszKey != NULL) &&
         (in_pPars->inout_nMsgLength <= SCHEME_MAX_PAYLOAD_SIZE) &&
         (in_pPars->in_dpStrength >= 0.0) &&
         (strlen(in_pPars->in_pszKey) == in_pPars->in_nKeyLength));

  uint nWidth   = in_imgOriginal.nCols;
  uint nHeight  = in_imgOriginal.nRows;
  uint nChannel = in_imgOriginal.nChannels;
  
  uint nPixels  = nWidth * nHeight * nChannel;

  // The random number generator is seeded with the
  // watermarking key and used to generate a pseudo
  // random watermark reference pattern which is added
  // to the signal without taking into account the
  // different colour components
  uint nSeed = 0;
  for(uint i = 0; i < in_pPars->in_nKeyLength; i++)
    if (in_pPars->in_pszKey[i] == '1')
      nSeed += 1 << i;
  srand(nSeed);
  double dAmp = in_pPars->in_dpStrength / 4;
  for (i = 0; i < nPixels; i++)
  {
    double dNoise = (((double)rand() / (double)RAND_MAX) > 0 ? 1 : -1) * dAmp;
    out_pimgTarget->pgData[i] = Clip(in_imgOriginal.pgData[i] + dNoise);
  }

  return SMBSUCCESS;
}


//////////////////////////////////////////////////////////////////////
// Detect a watermark using linear correlation
//
// See Base/StirMarkBenchmark.h for function behaviour

ErrorNum Extract_Image_Lib(const SMBImage    in_imgTest,     // Marked/attacked image
                           const SMBImage    in_imgOriginal, // Marked/unmarked image | 0
                           SMBSchemePars *inout_pPars)       // Pars for extraction & output
{
  // in_imgOriginal is not used as this is a blind scheme
  assert((in_imgTest.pgData != NULL) &&
         (inout_pPars != NULL) &&
         (inout_pPars->in_nKeyLength <= SCHEME_MAX_KEY_SIZE) &&
         (inout_pPars->in_pszKey != NULL) &&
         (strlen(inout_pPars->in_pszKey) == inout_pPars->in_nKeyLength));

  uint nWidth   = in_imgTest.nCols;
  uint nHeight  = in_imgTest.nRows;
  uint nChannel = in_imgTest.nChannels;
  
  uint nPixels  = nWidth * nHeight * nChannel;

  // The random number generator is seeded with the
  // watermarking key and used to generate a pseudo
  // random reference pattern. The test image is then
  // correlated with this pattern.
  uint nSeed = 0;
  for(uint i = 0; i < inout_pPars->in_nKeyLength; i++)
    if (inout_pPars->in_pszKey[i] == '1')
      nSeed += 1 << i;
  srand(nSeed);
  double dCor = 0.0;
  for (i = 0; i < nPixels; i++)
  {
    double dNoise = (((double)rand() / (double)RAND_MAX) > 0 ? 1 : -1);
    dCor += in_imgTest.pgData[i] * dNoise;
  }
  dCor /= nPixels;
  
  // Return the linear correlation value as a measure of certainy
  // TODO: this is wrong
  inout_pPars->out_dpCertainty = dCor;

  return SMBSUCCESS;
}


//////////////////////////////////////////////////////////////////////
// The information function returns information that can be used by
// the benchmark to determine the type of watermarking algorithm is
// being tested and to populate the databse of results
//
// See Base/StirMarkBenchmark.h for behaviour

ErrorNum GetSchemeInfo_Lib(uint      in_nInfo,
                           STR      out_pbData,
                           uint * inout_pcbData)
{
  switch (in_nInfo)
  {
  case MS_NAME:           // Name of the marking scheme
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_NAME);

  case MS_VERSION:        // Version of the scheme
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_VERSION);

  case MS_AUTHOR:         // Author(s), research group or company
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_AUTHOR);

  case MS_RELEASEDATE:    // Release date of the current version
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_RELEASE_DATE);

  case MS_DESCRIPTION:    // Notes and comments regarding the scheme
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_DESCRIPTION);

  case MS_SOURCELOCATION: // URL of the sources
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_SOURCE_LOCATION);

  case MS_CONTACTADDRESS: // Email of the contact
    return StringInfoCopy(out_pbData, inout_pcbData, SCHEME_CONTACT_ADDRESS);

  case MS_MSGMAXSIZE:     // Maximum length of the embedded message (bit) 
    return ValueInfo(out_pbData, inout_pcbData, SCHEME_MAX_PAYLOAD_SIZE);

  case MS_KEYMAXSIZE:     // Maximum length of the stego-key (bit)
    return ValueInfo(out_pbData, inout_pcbData, SCHEME_MAX_KEY_SIZE);

  case MS_SCHEMEFAMILY:   // Family of the watermarking scheme
    return ValueInfo(out_pbData, inout_pcbData, SCHEME_FAMILY);

  default:
    return SMBERROR_UNEXPECTED_PARAMETER;
  }
}


//////////////////////////////////////////////////////////////////////
// Clip and round a double value to a Gray integeer

Gray Clip(double x)
{
  return (Gray)( x > 255 ? 255 : ( x < 0 ? 0 : (Gray)floor(x + 0.5)));
}


//////////////////////////////////////////////////////////////////////
// Same behaviour as GetSchemeInfo_Lib
// One version for strings and another one for numerical data.

ErrorNum StringInfoCopy(STR      out_pbData,
                        uint * inout_pcbData,
                        CSTR      in_pszData)
{
  assert(in_pszData != 0);

  if (out_pbData)
  {
    if (*inout_pcbData < strlen(in_pszData) + 1)
        return (SMBERROR_MORE_DATA_AVAILABLE);
    else
    {
      memcpy(out_pbData, in_pszData, strlen(in_pszData) + 1);
      return (SMBSUCCESS);
    }
  }
  else
  {
    *inout_pcbData = strlen(in_pszData) + 1;
    return (SMBSUCCESS);
  }
}

ErrorNum ValueInfo(STR      out_pbData,
                   uint * inout_pcbData,
                   uint      in_uiValue)
{
  assert(out_pbData != 0);
  
  if (*inout_pcbData < sizeof(in_uiValue))
    return (SMBERROR_MORE_DATA_AVAILABLE);
  else
  {
    memcpy(out_pbData, &in_uiValue, sizeof(in_uiValue));
    return (SMBSUCCESS);
  }
}
