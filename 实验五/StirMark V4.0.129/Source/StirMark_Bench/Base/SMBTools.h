//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - CSMBRandomNumberGenerator.h
//
// Contents:
//
// Purpose:
//
// Created:  Nazim Fatès, Microsoft Research, 22 June 2000
//
// Modified: Fabien A. P. Petitcolas, Microsoft Research
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBTools.h,v 1.14 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#if !defined (_SMBTOOLS_H_)
#define       _SMBTOOLS_H_

// STL headers

// Other standard headers

// SMB headers
#include "SMBTypes.h"

// Other definitions
class CSMBImage;



#define FLOOR(x)  ((x) < 0 ? (long) ((x) - 1)   : (long) (x))
#define ROUND(x)  ((x) < 0 ? (long) ((x) - 0.5) : (long) ((x) + 0.5))

#ifdef VERBOSE
#define WARNING(msg) { cerr << "[Warning] " << msg << endl; }
#endif // VERBOSE
#define SMBThrowNewException(msg) { throw new CSMBException(msg); }


template <class T>
T SMBMax(T a, T b)
{
    return (a > b ? a : b);
}

template <class T>
T SMBMin(T a, T b)
{
    return (a < b ? a : b);
}


void displayParams(SMBSchemePars* );

// Convert double to Gray taking the [0 255] range into account
Gray RoundClip(double x);

void SMBGetTimeDate(TString &out_strUTC);

// bring two images into one with coef alpha
void ImageFusion(const CSMBImage & in_image1,
                 const CSMBImage & in_image2,
                 double            in_alpha,
                 CSMBImage &      out_image3);

void ImageBestFusion(const CSMBImage & in_image1,
                     const CSMBImage & in_image2,
                     const CSMBImage & in_WMOriginalImage,
                     CSMBImage &      out_image3);

// Parser similar to the Windows GetProfile* functions
ErrorNum 
ParseProfileReal(TCString & in_cstrAppName,  // Section name
                 TCString & in_cstrKeyName,  // Key name
                 TCString & in_cstrFileName, // Name of initialization file
                 double *  out_pdpValue);

uint 
ParseProfileString(TCString & in_cstrAppName,        // Section name
                   TCString & in_cstrKeyName,        // Key name
                   TCString & in_cstrDefault,        // Default return value
                   TCString & in_cstrFileName,       // Name of initialization file
                   TString & out_strReturnedString); // Found string

// Paser for list of values separated by space
int 
ParseProfileListReal(TCString &      in_cstrAppName,  // Section name
                     TCString &      in_cstrKeyName,  // Key name
                     TCString &      in_cstrFileName, // Name of initialization file
                     list<double> & out_rdpValues);

int ParseProfileListString(TCString &       in_cstrAppName,  // Section name
                           TCString &       in_cstrKeyName,  // Key name
                           TCString &       in_cstrFileName, // Name of initialization file
                           list<TString> & out_rdpValues);

void DumpSchemeParStruct(SMBSchemePars in_par);
void DumpImageStruct(SMBImage in_img);

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING
int SMBTools_Test(void);
#endif // SMB_CODE_TESTING

#endif // !defined(_SMBTOOLS_H_)
