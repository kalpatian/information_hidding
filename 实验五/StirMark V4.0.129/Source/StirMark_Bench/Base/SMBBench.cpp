//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBBench.cpp
//
// Contents: Implementation of the CSMBBench class.
//
// Purpose:  See SMBBench.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, March 2000
//
// Modified: Nazim Fatès, Microsoft Research
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBBench.cpp,v 1.26 2002/04/19 10:23:54 petitcolas Exp $
//////////////////////////////////////////////////////////////////////


// STL headers

// Other standard headers

// SMB headers
#include "SMBBench.h"
#include "SMBTools.h"
#include "SMBMarkingScheme.h"
#include "SMBError.h"
#include "SMBMemoryException.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBBench::CSMBBench(TCString & in_cstrLibPath,
                     TCString & in_cstrIniPath,
                     TCString & in_cstrLogPath)
: m_strLibPath(in_cstrLibPath),
  m_strLogPath(in_cstrLogPath),
  m_strIniPath(in_cstrIniPath)
{

}


CSMBBench::~CSMBBench()
{

}

//////////////////////////////////////////////////////////////////////
// Setup functions
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Writes the benchmark results in the log file
void CSMBBench::LogResultSummary(void)
{ 
  cout << "\n\nNumber of tests failed: " << m_nFailedTest << endl;
  
  TString strUTC;
  SMBGetTimeDate(strUTC);

  m_outStreamLog << "\n\n\n";
  m_outStreamLog << "MarkBench - Bench Results  - ";
  m_outStreamLog << strUTC << endl;

  m_outStreamLog << "Number of tests which failed:";
  m_outStreamLog << m_nFailedTest;
  m_outStreamLog << endl;
}

//////////////////////////////////////////////////////////////////////
ErrorNum CSMBBench::LogMessage(const TCString &in_strMessage)
{
  m_outStreamLog << in_strMessage << endl;

  if (!m_outStreamLog.good()) 
    SMBWarning("[CSMBBench::LogMessage()] - stream troubles while writing.");

  return (m_outStreamLog.good() ? SMBSUCCESS : SMBFAILURE);
}



//////////////////////////////////////////////////////////////////////
// Main function
//////////////////////////////////////////////////////////////////////

ErrorNum CSMBBench::operator()(void)
{ 
  m_nFailedTest = 0;
  TString strFilePath, strFileName, strBaseName, strUTC;
  CSMBImage myImg;

  

#ifdef SMB_SQL_IS_ENABLED
  SMBInformation("\nLogging on database...", 0);
  
  // TODO: SQL support
  m_dbResults.Open();
  m_dbResults.AddCommand("INSERT INTO Evaluation (EvalutionDate, Platform) VALUES(""10/10/2001"", ""WIN32"")");
  m_dbResults.ExecuteCommandStack();
#endif // SMB_SQL_IS_ENABLED


  strFileName = m_strLogPath;
  SMBGetTimeDate(strUTC);
  strFileName += strUTC;
  strFileName += SMB_DEFAULT_REPORT_FILE_EXT;

  SMBInformation(TString("\nCreating log file [") + strFileName + "] ...\n");
  
  m_outStreamLog.open(strFileName);
  if (!m_outStreamLog.good())
  {
    SMBWarning("[CSMBBench::()] - Could not create log file. Benchmark aborded.");
    return SMBFAILURE;
  }

  
  // Setup the marking scheme and log details into logfile
  CSMBMarkingScheme in_mks(this);
  CSMBMemoryException e;
  try
  {
    in_mks.SetLibrary(SMB_DEFAULT_LIBRARY_FOLDER + m_strLibPath, e);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg("Program will be terminated.");
    delete pException;
    return SMBFAILURE;
  }
  in_mks.LogInfo();

  
  // Prepare evaluation profile
  m_lstimgSource.Initialise(SMB_DEFAULT_SETTINGS_FOLDER + m_strIniPath);
  m_lsttstBench.Initialise(SMB_DEFAULT_SETTINGS_FOLDER + m_strIniPath, this);

  
  // Start the actual evalution: for all test and for all images
  // defined by the evaluation profile apply each test to each image

  SMBInformation("\nStarting benchmark...\n", 0);

  // For each test
  for (CSMBTestList::iterator
       pwrpTest  = m_lsttstBench.begin();
       pwrpTest != m_lsttstBench.end();
       pwrpTest++)
  {

       SMBGetTimeDate(strUTC);
       m_outStreamLog << "\n\n" << SMB_LOG_TEST_SEPARATOR;
       m_outStreamLog << (*pwrpTest)()->GetTestName() << " -- " << strUTC << endl;
       m_outStreamLog << SMB_LOG_TEST_SEPARATOR;
         
       // For each image
       for (CSMBImageList::iterator
            pstrImageName =  m_lstimgSource.begin();
            pstrImageName != m_lstimgSource.end();
            pstrImageName++)
       {

            // Store the name of the image without extension as a base name
            strFileName = *pstrImageName;
            strBaseName = strFileName.GetBaseName();

            // Path to load the file
            strFilePath = SMB_DEFAULT_DATABASE_FOLDER + "/" + strFileName; 

            SMBInformation(SMB_LOG_TEST_SEPARATOR);
            SMBInformation(TString("Applying ") + (*pwrpTest)()->GetTestName()
                           + TString(" to [") + strFileName + "] ...", 0);
 
            // Load image and assign a BaseName to it
            try
            {
              myImg.Load(strFilePath);
            }
            catch (CSMBException *pException)
            {
              pException->PrintMsg();
              SMBWarning("[CSMBBench::()] - Image (\"" + strFilePath + "\") could not be read and will be skipped.");
              delete pException;
              continue; // Use next image
            }
            myImg.SetBaseName(strBaseName);

            // Try to run the test on the newly loaded image
            ErrorNum result;
            try
            {
              result = (*pwrpTest)()->Run(myImg, in_mks);
            }
            catch (CSMBException *pException)
            {
              pException->PrintMsg();
              SMBWarning("[CSMBBench::()] - The current test (" +
                         (*pwrpTest)()->GetTestName() +
                         ") has been skipped.");
              m_nFailedTest++;
              delete pException;
              break; // Next image
            }
       } // For images

       SMBInformation(TString((*pwrpTest)()->GetTestName()) +
                      " completed sucessfully");
  } // For tests

  LogResultSummary();

  return SMBSUCCESS;
}
