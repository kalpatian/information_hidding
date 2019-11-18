//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTools.cpp
//
// Contents: Utility functions.
//
// Purpose:  Mathematicals and other basic functions for file
//           management, image processing and parsing.
//
// Created:  Nazim Fatès, Microsoft Research, 22 June 2000
//
// Modified: Frédéric Raynal, INRIA
//             '.ini' files parser
//           Fabien A. P. Petitcolas, Microsoft Research
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBTools.cpp,v 1.20 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

// STL headers

// Other standard headers
#include <time.h>
#include <math.h>
#ifdef __UNIX__
#include <dirent.h>
#include <time.h>   // for tzset
#endif // __UNIX__

// SMB headers
#include "SMBImage.h"
#include "SMBError.h"



//////////////////////////////////////////////////////////////////////
// Clip and round a double value to a Gray integeer

Gray RoundClip(double x)
{
  return (Gray)( x > 255 ? 255 : ( x < 0 ? 0 : (Gray)floor(x + 0.5)));
}

//////////////////////////////////////////////////////////////////////
// Time related functions
void SMBGetTimeDate(TString & out_strUTC)
{
  struct tm *gmt;
  time_t ltime;
  char * pszTime, * pch;
  
  // Set time zone from TZ environment variable
  tzset();

  time(&ltime);

  // UTC date and time
  gmt = gmtime(&ltime);
  pszTime = asctime(gmt);
  pch = pszTime;
  while ((pch = strstr(pch, ":")) != NULL)
    *pch++ = '.';
  pch = strstr(pszTime, "\n");
  *pch = '\0';
  out_strUTC = pszTime;
}


//////////////////////////////////////////////////////////////////////
// Parse the ini file to get the line containing the key.
// Return :
//   0 : the line is found and put in lpLine
//  !0 : no key found, lpLine = 0
#ifdef WIN32
#pragma warning (push)
#pragma warning (disable: 4706)
#endif // WIN32
static int _GetLineInIniFile(TCString lpAppName,  // section name
                             TCString lpKeyName,  // key name
                             TCString lpFileName, // initialization file name
                             STR      lpLine,     // the researched line
                             int      nSize = 255)
{
  // open file
  ifstream in;
  in.open(lpFileName);
  if (!in)
  {
    SMBWarning("[_GetLineInIniFile] Could not open " + lpFileName);
    return 1;
  }

  // Look for the section lpAppName
  // I use "strchr(line,']')-(line+1)" instead of just strlen(lpAppName)
  // since the match needs to be done on ALL what is between the [].
  // If one uses strlen(lpAppName), then there is a mistake if lpAppName
  // is the begining of another word since it belives it found the 
  // right answer.
  // For instance, if lpAppName="foo" and the line is "[foobar]", then 
  // the mistake occurs when using strlen(lpAppName) to compare, since 
  // it compares only the 3 first letters :(
  memset(lpLine, 0, nSize);
  while (in.getline(lpLine, nSize) && 
         strncmp(lpLine + 1, lpAppName, strlen(lpAppName)))
    ;

  // Look for the key lpKeyName
  int notFound = 1;
  while (!in.eof() &&
	       in.getline(lpLine, nSize) &&
	       lpLine[0] != '[' && // new section : stop searching
	       (notFound = strncmp(lpLine, lpKeyName, strlen(lpKeyName))))
    ;

  in.close();
  return notFound;
} // getLineInIniFile
#ifdef WIN32
#pragma warning (pop)
#endif // WIN32

//////////////////////////////////////////////////////////////////////
// No test is done to know if the found string (if any) contains a number.
ErrorNum 
ParseProfileReal(TCString & in_cstrAppName,  // Section name
                 TCString & in_cstrKeyName,  // Key name
                 TCString & in_cstrFileName, // Name of initialization file
                 double *  out_pdpValue)
{
  char line[256];
  int notFound = _GetLineInIniFile(in_cstrAppName, in_cstrKeyName, in_cstrFileName, line);

  if (notFound)
    return SMBFAILURE;

  *out_pdpValue = atof(strchr(line,'=') + 1);
  return SMBSUCCESS;
}


//////////////////////////////////////////////////////////////////////
// Retrun :
// - if what as to be returned (it could be either the wanted value or 
//   lpDefault) is longer than nSize, it returns valueFound[0...nSize-1],
//   this last char being replaced with \0.
// - if the section is not found, returns the default
// - if the key is not found, return the default
// - if everything is found, returns what is found
uint 
ParseProfileString(TCString & in_cstrAppName,       // Section name
                   TCString & in_cstrKeyName,       // Key name
                   TCString & in_cstrDefault,       // Default return value
                   TCString & in_cstrFileName,      // Name of initialization file
                   TString & out_strReturnedString) // Found string
{
  char line[256];
  int notFound = _GetLineInIniFile(in_cstrAppName, in_cstrKeyName, in_cstrFileName, line);

  // if we find it, we use it :)
  if (notFound)
    out_strReturnedString = in_cstrDefault;
  else
    out_strReturnedString = strchr(line, '=') + 1;
  // return
  return out_strReturnedString.length();
}


//////////////////////////////////////////////////////////////////////
// No test is done to know if the found string (if any) contains a number.
// Returns the number of values found

int ParseProfileListReal(TCString &      in_cstrAppName,  // Section name
                         TCString &      in_cstrKeyName,  // Key name
                         TCString &      in_cstrFileName, // Name of initialization file
                         list<double> & out_rdpValues)
{
  char line[256];
  char *pch = 0;
  int  cdpFound = 0;

  out_rdpValues.clear();

  int notFound = _GetLineInIniFile(in_cstrAppName, in_cstrKeyName, in_cstrFileName, line);
  
  if (!notFound)
  {
    pch = strchr(line, '=') + 1;
    while (pch)
    {
      while (*pch == ' ') pch++;
      if (pch[0] != 0)
      {
        out_rdpValues.push_back(atof(pch));
        pch = strchr(pch, ' ');
        cdpFound++;
      }
      else
        pch = 0;
    }
  }

  return cdpFound;
}



//////////////////////////////////////////////////////////////////////

int ParseProfileListString(TCString &       in_cstrAppName,  // Section name
                           TCString &       in_cstrKeyName,  // Key name
                           TCString &       in_cstrFileName, // Name of initialization file
                           list<TString> & out_rdpValues)
{
  char line[256];
  char *pch1 = 0, *pch2 = 0;
  int  cdpFound = 0;
  TString str;

  out_rdpValues.clear();

  int notFound = _GetLineInIniFile(in_cstrAppName, in_cstrKeyName, in_cstrFileName, line);
  
  if (!notFound)
  {
    pch1 = strchr(line, '=') + 1;
    while (pch1)
    {
      while (*pch1 == ' ') pch1++;
      if (pch1[0] != 0)
      {
        pch2 = strchr(pch1, ' ');
        if (pch2 == NULL)
          str.assign(pch1);
        else
          str.assign(pch1, pch2 - pch1);
        out_rdpValues.push_back(str);
        pch1 = pch2;
        cdpFound++;
      }
      else
        pch1 = 0;
    }
  }

  return cdpFound;
}



//////////////////////////////////////////////////////////////////////
void DumpSchemeParStruct(SMBSchemePars in_par)
{
  SMBInformation(TString("  PSNR:       ") + TString(in_par.in_dpPSNR));
  SMBInformation(TString("  Strength:   ") + TString(in_par.in_dpStrength));
  if (in_par.in_pszKey != NULL)
    SMBInformation(TString("  Key:        ") + TString(in_par.in_pszKey));
  SMBInformation(TString("  Key length: ") + TString((int)in_par.in_nKeyLength));
  if (in_par.inout_pszMsg != NULL)
    SMBInformation(TString("  Msg:        ") + TString(in_par.inout_pszMsg));
  SMBInformation(TString("  Msg length: ") + TString((int)in_par.inout_nMsgLength));
  SMBInformation(TString("  Certainty:  ") + TString(in_par.out_dpCertainty));
}

void DumpImageStruct(SMBImage in_img)
{
  SMBInformation(TString("  Border mode:  ") + TString((int)in_img.bmMode));
  SMBInformation(TString("  Border value: ") + TString(in_img.gBrdValue));
  SMBInformation(TString("  Max value:    ") + TString(in_img.gMaxVal));
  SMBInformation(TString("  Type:         ") + TString((int)in_img.itType));
  SMBInformation(TString("  Width:        ") + TString((long)in_img.nCols));
  SMBInformation(TString("  Height:       ") + TString((long)in_img.nRows));
  SMBInformation(TString("  Channels:     ") + TString((long)in_img.nChannels));
  SMBInformation(TString("  Data:         ") + TString((long)in_img.pgData));
}


//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>
#include "SMBConfig.h"

int SMBTools_Test()
{
  list<double> rdpValues;
  list<double>::iterator pdpValue;

  // Assume the following entry in SMB_DEFAULT_SETTINGS_FILE
  // ; #ifdef SMB_CODE_TESTING
  // [SMBTools_Test]
  // list=1.5 -2.1 8.1 0 
  // ; #endif SMB_CODE_TESTING

  if (ParseProfileListReal("SMBTools_Test",
                           "list",
                           SMB_DEFAULT_SETTINGS_FOLDER + SMB_DEFAULT_SETTINGS_FILE,
                           rdpValues) != 4)
     return SMBFAILURE;

  pdpValue = rdpValues.begin();

  if ((*pdpValue++ !=   1.5) ||
      (*pdpValue++ !=  -2.1) ||
      (*pdpValue++ !=   8.1) ||
      (*pdpValue   !=   0.0))
      return SMBFAILURE;

  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
