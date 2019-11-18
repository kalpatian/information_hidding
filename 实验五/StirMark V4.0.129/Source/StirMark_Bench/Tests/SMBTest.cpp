//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTest.cpp
//
// Contents: Implementation of the CSMBTest class.
//
// Purpose:  See CSMBTest.h
//
// Created:  Nazim Fatès, Microsoft Research, May 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTest.cpp,v 1.21 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers

// SMB headers
#include "SMBTest.h"
#include "../Base/SMBTools.h"
#include "../Base/SMBQuality.h"
#include "../Base/SMBBench.h"
#include "../Base/SMBImage.h"
#include "../Base/SMBError.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTest::CSMBTest()
{

}


CSMBTest::CSMBTest(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance)
{
  if (in_pbenchInstance == 0)
    SMBFatalError("[CSMBTest::CSMBTest] - Fatal error: null pointer parameter.");
  else
    m_pbenchInstance = in_pbenchInstance;

  SetIniLogPath(in_cstrIniPath);
}


CSMBTest::~CSMBTest()
{

}

/*
void CSMBTest::Setup()
{
  m_strTestName = "Error: test name not set"; // Has to be defined in the derived class
  m_strTestTag  = "Error: test tag no set properly"; // Has to be defined in the derived class

  m_strIniFilePath = "";  // Should be provided by the caller

  m_lstdpValueSet.clear();
}
*/

//////////////////////////////////////////////////////////////////////
// Get/Set methods
//////////////////////////////////////////////////////////////////////

void CSMBTest::SetIniLogPath(TCString &in_cstrIniPath)
{
  if (in_cstrIniPath.empty())
    m_strIniFilePath = SMB_DEFAULT_SETTINGS_FILE;
  else
    m_strIniFilePath = in_cstrIniPath;
}


TString CSMBTest::GetTestName() const
{
  return m_strTestName;
}


//////////////////////////////////////////////////////////////////////
// Initialisation
//////////////////////////////////////////////////////////////////////

void CSMBTest::InitTest(const CSMBImage &in_imgSource)
{
  // Get parameters from initialisation file
  
  ParseProfileListReal(m_strTestName, 
	                     "list", 
	                     m_strIniFilePath, 
		                   m_lstdpValueSet);
  
  // If the start - step - end values are defined, then add to the list
  double dpStart = 0.0, dpEnd = 0.0, dpStep = 0.0;
  if (ParseProfileReal(m_strTestName, "start", m_strIniFilePath, &dpStart) == SMBSUCCESS &&
      ParseProfileReal(m_strTestName, "end",   m_strIniFilePath, &dpEnd)   == SMBSUCCESS &&
      ParseProfileReal(m_strTestName, "step",  m_strIniFilePath, &dpStep)  == SMBSUCCESS)
  {
    if (dpStep == 0.0)
      SMBWarning("[CSMBTest::InitTest] - Step parameter cannot be 0.");
    else
    {
      if (dpStep < 0)
        dpStep = - dpStep;

      if (dpStart > dpEnd)
      {
        double tmp = dpEnd;
        dpEnd = dpStart;
        dpStart = tmp;
      }

      for(double dp = dpStart; dp <= dpEnd; dp += dpStep)
        m_lstdpValueSet.push_back(dp);
    } // end if
  } // end if

  // Eliminates duplicates
  m_lstdpValueSet.sort();
  m_lstdpValueSet.unique();
}


//////////////////////////////////////////////////////////////////////
// Writes result in the log file
//////////////////////////////////////////////////////////////////////
void CSMBTest::LogNumericalResult(int              in_Parameter,
                                  const CSMBImage &in_imgOriginal,
                                  const CSMBImage &in_imgModified,
                                  TCString        &in_cstrResultName,
                                  double           in_Result,
                                  TCString         in_strComment /* = "" */) const
{
  LogNumericalResult((double)in_Parameter,
                     in_imgOriginal,
                     in_imgModified,
                     in_cstrResultName,
                     in_Result,
                     in_strComment);
}


void CSMBTest::LogNumericalResult(double           in_Parameter,
                                  const CSMBImage &in_imgOriginal,
                                  const CSMBImage &in_imgModified,
                                  TCString        &in_cstrResultName,
                                  double           in_Result,
                                  TCString         in_strComment /* = "" */) const
{
  TString msg;

  // Test name | Test parameter | Image name | Result name | Result value | PSNR | Comment

  msg = m_strTestName + SMB_LOG_SEPARATOR +
        TString(in_Parameter) + SMB_LOG_SEPARATOR +
        in_imgOriginal.GetBaseName() + SMB_LOG_SEPARATOR +
        in_cstrResultName + SMB_LOG_SEPARATOR +
        TString(in_Result)  + SMB_LOG_SEPARATOR;

  double dpPSNR = PSNR(in_imgOriginal, in_imgModified);
  if (dpPSNR != -SMB_MAX_DOUBLE)
    msg += TString(dpPSNR) + TCString(" dB");
  else
    msg += "NA";

  msg += SMB_LOG_SEPARATOR + in_strComment;

  m_pbenchInstance->LogMessage(msg);
}





