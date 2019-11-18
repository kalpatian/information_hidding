//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBString.cpp
//
// Contents: Implementation of the CSMBString class.
//
// Purpose:  See SMBString.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 14 September 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBString.cpp,v 1.17 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// Other standard headers
#include <stdio.h>
#include <assert.h>
#ifdef __UNIX__
#include <algo.h>
#endif
#ifdef WIN32
#define snprintf _snprintf
#endif

// SMB headers
#include "SMBString.h"
#include "SMBTypes.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBString::CSMBString()
  : string()
{

}

CSMBString::CSMBString(const char *in_sz)
  : string(in_sz)
{

}

CSMBString::CSMBString(int in_val)
  : string()
{
  char sz[10];
  snprintf(sz, 10, "%d", in_val);
  *this = sz;
}

CSMBString::CSMBString(const void *in_pvoid)
{
  char sz[11];
  snprintf(sz, 11, "0x%08X", (uint)in_pvoid);
  *this = sz;

}

CSMBString::CSMBString(double in_val)
  : string()
{
  char sz[10];
  snprintf(sz, 10, "%g", in_val);
  *this = sz;
}

CSMBString::CSMBString(const string &in_str)
  : string(in_str)
{

}

CSMBString::CSMBString(const CSMBString &in_str)
  : string(in_str)
{

}

CSMBString::~CSMBString()
{
}


//////////////////////////////////////////////////////////////////////
// Operators overloading
//////////////////////////////////////////////////////////////////////

CSMBString & CSMBString::operator +=(const char *in_sz)
{
  append(in_sz);
  return *this;
}

CSMBString & CSMBString::operator +=(const string &in_str)
{
  append(in_str);
  return *this;
}

CSMBString & CSMBString::operator +=(int in_val)
{
  append(CSMBString(in_val));
  return *this;
}

CSMBString & CSMBString::operator +=(double in_val)
{
  append(CSMBString(in_val));
  return *this;
}

CSMBString & CSMBString::operator = (const CSMBString &in_other) 
{
  string::operator=(in_other.c_str());
  return *this;
}

CSMBString::operator CSTR() const
{
  return c_str();
}


//////////////////////////////////////////////////////////////////////
// Filename functions
//////////////////////////////////////////////////////////////////////

CSMBString CSMBString::GetExtension() const
{
  size_t posExtension = this->find_last_of(".");
  if (posExtension == string::npos)
    return CSMBString("");
  else
    return this->substr(posExtension);
}

CSMBString CSMBString::GetBaseName() const
{
  size_t posExtension = this->find_last_of(".");
  if (posExtension == string::npos)
    return *this;
  else
    return this->substr(0, posExtension);
}

void CSMBString::AddExtension(const string &in_strFileExtension)
{
  if (!in_strFileExtension.empty()) 
  {
    // Extensions must start with a dot
    assert(in_strFileExtension.find_last_of(".") != string::npos);

    if (GetExtension() != in_strFileExtension)
      *this += in_strFileExtension;
  }
}


//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>
#include <string.h>

#define SMB_CODE_TESTING_EXTENSION ".extension"

ErrorNum SMBString_Test()
{
  // Constructors
  CSMBString strTest1;
  CSMBString strTest2("const char");
  CSMBString strTest3(16);
  CSMBString strTest4(strTest2);

  // Operators
  strTest1 += "String";
  strTest1 += 2;
  strTest1 += strTest3;
  strTest4 =  strTest1;
  if (strTest1 != "String216" ||
      strTest4 != "String216" ||
      strTest4 != strTest1)
    return SMBFAILURE;

  strTest3 =  strTest4 + strTest2;

  // Extensions
  strTest1.AddExtension(SMB_CODE_TESTING_EXTENSION);
  if (strTest1.GetExtension() != SMB_CODE_TESTING_EXTENSION)
    return SMBFAILURE;
  if (strTest1.GetBaseName() != strTest4)
    return SMBFAILURE;

  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
