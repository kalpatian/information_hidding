//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTestList.cpp
//
// Contents: Implementation of the CSMBTestList class.
//
// Purpose:  See SMBTestList.h.
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 15 September 2000
//           parts based on code by
//           Nazim Fatès, Microsoft Research, June 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTestList.cpp,v 1.20 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////



// STL headers
// DO NOT USE standard iostream headers (not compatible)
// See: http://www.sgi.com/Technology/STL/
#include <iostream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// SMB headers
#include "SMBTestList.h"
#include "../Base/SMBTools.h"
#include "../Base/SMBError.h"
#include "../Base/SMBException.h"
#include "../Base/SMBConfig.h"
#include "SMBTest_EmbedTime.h"
#include "SMBTest_PSNR.h"
#include "SMBTest_Cropping.h"
#include "SMBTest_Rescale.h"
#include "SMBTest_Rotation.h"
#include "SMBTest_RotationCrop.h"
#include "SMBTest_RotationScale.h"
#include "SMBTest_RemoveLines.h"
#include "SMBTest_ConvFilter.h"
#include "SMBTest_MedianCut.h"
#include "SMBTest_AddNoise.h"
#include "SMBTest_JPEG.h"
#include "SMBTest_Affine.h"
#include "SMBTest_SmallRandomDistortions.h"
#include "SMBTest_LatestSmallRandomDistortions.h"
#include "SMBTest_SelfSimilarities.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTestList::CSMBTestList()
  :list<CSMBTestPtrWrapper>()
{

}

CSMBTestList::CSMBTestList(const CSMBTestList &in_other) 
  :list<CSMBTestPtrWrapper>(in_other) 
{

}

CSMBTestList::~CSMBTestList()
{
  clear();
}

//////////////////////////////////////////////////////////////////////
// Initialise
//
// Generate a list of test objects using the list provided in the
// initialisation file

void CSMBTestList::Initialise(TCString &in_cstrIniFilePath, CSMBBench *const in_pbenchInstance)
{
  SMBInformation("  TESTS >>", 0);

  // Clear content if necessary
  clear();
    
  TString strTestName;

  int i = 1;
  // Check all Test1, Test2, etc. entries in the initialisation file
  // and construct a list of test.
  while (ParseProfileString(SMB_DEFAULT_TEST_LIST_SECTION,
                            SMB_DEFAULT_TEST_LIST_KEY + TString(i++),
                            "",
                            in_cstrIniFilePath,
                            strTestName))
  {
    if (strTestName == "Test_EmbedTime")
      push_back(new CSMBTest_EmbedTime(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_PSNR")
      push_back(new CSMBTest_PSNR(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_Cropping")
      push_back(new CSMBTest_Cropping(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_Rescale")
      push_back(new CSMBTest_Rescale(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_Rotation")
      push_back(new CSMBTest_Rotation(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_RotationCrop")
      push_back(new CSMBTest_RotationCrop(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_RotationScale")
      push_back(new CSMBTest_RotationScale(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_RemoveLines")
      push_back(new CSMBTest_RemoveLines(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_ConvFilter")
      push_back(new CSMBTest_ConvFilter(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_MedianCut")
      push_back(new CSMBTest_MedianCut(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_AddNoise")
      push_back(new CSMBTest_AddNoise(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_JPEG")
      push_back(new CSMBTest_JPEG(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_Affine")
      push_back(new CSMBTest_Affine(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_SmallRandomDistortions")
      push_back(new CSMBTest_SmallRandomDistortions(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_LatestSmallRandomDistortions")
      push_back(new CSMBTest_LatestSmallRandomDistortions(in_cstrIniFilePath, in_pbenchInstance));

    else if (strTestName == "Test_SelfSimilarities")
      push_back(new CSMBTest_SelfSimilarities(in_cstrIniFilePath, in_pbenchInstance));

    else
      SMBWarning(TString(" [SMBTestList] unrecognised test in initialisation file (") + strTestName + ") - please check the spelling.");

    SMBInformation(TString("    ") + strTestName, 0);
  }
  // The CSMBTestPtrWrapper deletes automatically memory allocated
  // for the pointer when an instance of the class is destroyed
}

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>

int SMBTestList_Test()
{
  SMBInformation("SMBTestList testing (begin)");

  /////////////////////////////////////////////////
  // CSMBTestPtrWrapper
  CSMBTestPtrWrapper wrptstTest1(new CSMBTest_Affine(SMB_DEFAULT_SETTINGS_FILE, NULL));
  CSMBTestPtrWrapper wrptstTest2(wrptstTest1);

  assert(wrptstTest1()->GetTestName() == wrptstTest2()->GetTestName());

  /////////////////////////////////////////////////
  // CSMBTestList
  CSMBTestList lsttstTest;
  CSMBTestList::iterator iterstrTest;

  lsttstTest.Initialise(SMB_DEFAULT_SETTINGS_FOLDER + SMB_DEFAULT_SETTINGS_FILE, NULL);

  cout << "\nThe following test have been added to the list:" << endl;
  for (iterstrTest = lsttstTest.begin(); iterstrTest != lsttstTest.end(); iterstrTest++)
    cout << "\t" << (*iterstrTest)()->GetTestName() << endl;

  lsttstTest.clear();
  cout << "\n\nSMBTestList testing (end)" << endl;
  return 0;
}
#endif // SMB_CODE_TESTING
