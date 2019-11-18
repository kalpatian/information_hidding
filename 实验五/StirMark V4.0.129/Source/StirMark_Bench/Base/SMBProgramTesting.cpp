//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBProgramTesting.cpp
//
// Contents: Implementation of the main code testing program.
//
// Purpose:  This program should be used to test the implementation
//           of the various classes of the whole project.
//
// History:
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, May 2000
//
// Modified:
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBProgramTesting.cpp,v 1.15 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#ifdef WIN32
// Memory leak detection
// Technical article: Edward Wright, "Detecting and Isolating Memory Leaks
// Using Microsoft Visual C++", MSDN, Microsoft Corporation, May 1999
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // WIN32
#include <assert.h>
#include <typeinfo>

// SMB Headers
#include "SMBConfig.h"
#include "SMBImage.h"
#include "SMBTools.h"
#include "SMBString.h"
#include "SMBImageList.h"
#include "SMBMemoryException.h"
#include "SMBException.h"
#ifdef SMB_SQL_IS_ENABLED
#include "SMBDatabase.h"
#endif // SMB_SQL_IS_ENABLED
#include "SMBError.h"
#include "../Uncompleted/SMBPoint.h"
#include "../Uncompleted/SMBRectangle.h"
#include "../Tests/SMBTestList.h"
#include "../Base/SMBQuality.h"
#include "../Tests/SMBTest_SmallRandomDistortions.h"
#include "../GeometricTransforms/SMBSamPoint.h"
#include "../GeometricTransforms/SMBReconstructor.h"
#include "../GeometricTransforms/SMBRecNearestNeighbour.h"
#include "../GeometricTransforms/SMBRecLinearInterpolation.h"
#include "../GeometricTransforms/SMBRecInterpolatingQuadratic.h"
#include "../GeometricTransforms/SMBGT_Rotation.h"
#include "../GeometricTransforms/SMBGT_SmallRandomDistortions.h"
#include "../SpecialTransforms/SMBST_Transposition.h"
#include "../SignalProcessing/SMBSP_SelfSimilarities.h"



//////////////////////////////////////////////////////////////////////
// Test functions for CSMBPoint and CSMBRectangle

int SMBPoint_Test(void)
{
  CSMBlPoint p1(1, 0);
  CSMBdPoint p2(p1);
  
  if (!(p2 == p1))
  {
    cout << "Error: " << p2 << " != " << p1 << endl;
    return SMBFAILURE;
  }

  p2.SetLocation(1.1, 0.1);

  if (!(p1 == p2))
  {
    cout << "Error: " << p1 << " != " << p2 << endl;
    return SMBFAILURE;
  }

  if (p2 == p1)
  {
    cout << "Error: " << p2 << " == " << p1 << endl;
    return SMBFAILURE;
  }
  
  p1.Translate(p2);
  
  if (!(p1 == CSMBlPoint(2, 0)))
  {
    cout << "Error: translation did not succeed" << endl;
    return SMBFAILURE;
  }
  
  return SMBSUCCESS;
}

int SMBRectangle_Test(void)
{
  CSMBlRectangle lr(1, 2, 3, 4);
  CSMBfRectangle fr(1., 2., 3., 4.);
  CSMBdRectangle dr(1.1, 2., 3., 4.);

  cout << "Rectangles:" << lr << " " << fr << " " << dr << endl;

  if (!(lr == dr))
  {
    cout << "Error: " << lr << " != " << dr << endl;
    return SMBFAILURE;
  }
 
  if (dr == lr)
  {
    cout << "Error: " << dr << " == " << lr << endl;
    return SMBFAILURE;
  }
  
  lr.Union(dr);
  if (!(lr == CSMBlRectangle(1, 2, 3, 4)))
  {
    cout << "Rectangle union failed: " << lr << endl;
    return SMBFAILURE;
  }
  
  return SMBSUCCESS;
}

//////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
#ifdef WIN32
  // Dump memory leaks whenever the program exists
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_DELAY_FREE_MEM_DF);
#endif

  CSMBMemoryException memException;

  /////////////////////////////////////////////////
  cout<<"Testing SMBSP_SelfSimilarities"<<endl;
  if (SMBSP_SelfSimilarities_Test() != SMBSUCCESS)
    SMBWarning("SMBSP_SelfSimilarities test failed");

  return 0;

  /////////////////////////////////////////////////
  cout<<"Testing SMBImage"<<endl;
  if (SMBImage_Test() != SMBSUCCESS)
    SMBWarning("Image test failed");

  /////////////////////////////////////////////////
  // CSMBImageList class
  cout<<"Testing SMBImageList"<<endl;
  if (SMBImageList_Test() != SMBSUCCESS)
    SMBWarning("ImageList test failed");

  /////////////////////////////////////////////////
  // CSMBDistortionMap class
  cout<<"Testing SMBDistortionMap"<<endl;
  if (SMBDistortionMap_Test() != SMBSUCCESS)
    SMBWarning("DistortionMap test failed");


  /////////////////////////////////////////////////
  // CSMBGT_SmallRandomDistortions class
  cout<<"Testing SMBGT_SmallRandomDistortions"<<endl;
  if (SMBGT_SmallRandomDistortions_Test() != SMBSUCCESS)
    SMBWarning("GT_SmallRandomDistortions test failed");

  /////////////////////////////////////////////////
#ifdef SMB_SQL_IS_ENABLED
  if (SMBDatabase_Test() != SMBSUCCESS)
    SMBWarning("Database test failed");
#endif // SMB_SQL_IS_ENABLED

  /////////////////////////////////////////////////
  // CSMBTestList class
  cout<<"Testing SMBTestList"<<endl;
  if (SMBTestList_Test() != SMBSUCCESS)
    SMBWarning("TestList failed");
  
  /////////////////////////////////////////////////
  // Image class

  // Image initialisation
  CSMBImage * pImage = new CSMBImage();

  // Generate a file exception
  try { pImage->Load(" "); }
  catch (CSMBException *pException) { pException->PrintMsg(); delete pException; };

  // Generate a not enough memory exception
  try { pImage->Initialise(100000, 100000, 255, IT_RGB, memException); }
  catch (CSMBMemoryException *pMemException) { pMemException->PrintMsg(); };

  // Load the default sample image
  try
  {
    pImage->Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_1);

    // Test the CopyFrom function
    CSMBImage imgTesting;
    try { imgTesting.CopyFrom(*pImage, memException); }
    catch (CSMBMemoryException *pMemException) { pMemException->PrintMsg(); }

    // Test the save function
    try { imgTesting.Save("CSMBImage.Save.Test", "PPM"); }
    catch (CSMBException *pException) { pException->PrintMsg(); delete pException; };
    try { imgTesting.Save("CSMBImage.Save.Test", "BMP"); }
    catch (CSMBException *pException) { pException->PrintMsg(); delete pException; };
    try { imgTesting.Save("CSMBImage.Save.Test", "JPG"); }
    catch (CSMBException *pException) { pException->PrintMsg(); delete pException; };

    /////////////////////////////////////////////////
    // Geometric transformations classes
    typedef list<CSMBReconstructor *> LST_REC;

    LST_REC lst_rec;
    lst_rec.push_front(new CSMBRecInterpolatingQuadratic());
    lst_rec.push_front(new CSMBRecNearestNeighbour());
    lst_rec.push_front(new CSMBRecLinearInterpolation());

    CSMBGT_SmallRandomDistortions gt_rnddist(0);
    gt_rnddist.Initialise(*pImage);
    
    for (LST_REC::iterator pRec = lst_rec.begin(); pRec != lst_rec.end(); pRec++)
    {
      CSMBImage     imgOut;
      CSMBImage     imgOriginal;
      CSMBSamPoint  sam;
  
      try { imgOut.InitialiseFrom(*pImage, memException); }
      catch (CSMBException *pException) { pException->PrintMsg();};
    
      sam.Resample(*pImage, imgOut, **pRec, gt_rnddist);
    
      try { imgOut.Save(TString("Sample ") + (typeid(**pRec)).name(), "BMP"); }
      catch (CSMBException *pException) { pException->PrintMsg(); }
      catch (bad_typeid* pException) { }; // TODO: anything to do here?
      
      delete *pRec; *pRec = 0;
    }
  }
  catch (CSMBException *pException) { pException->PrintMsg(); delete pException; };

  delete pImage;

  /////////////////////////////////////////////////
  // CSMBString class
  cout<<"Testing SMBString"<<endl;
  if (SMBString_Test() != SMBSUCCESS)
    SMBWarning("String test failed");

  /////////////////////////////////////////////////
  // Memory exception class
  cout<<"Testing CSMBMemoryException"<<endl;
  try
  {
    SMBInformation("Throwing memory exception");
    memException.Throw(CSMBMemoryException::generic);
  }
  catch (CSMBMemoryException *pMemException)
  {
    SMBInformation("Memory exception caught");
    assert(pMemException == &memException);
    pMemException->PrintMsg();
  }

  /////////////////////////////////////////////////
  // Tool functions
  cout<<"Testing SMBTools"<<endl;
  if (SMBTools_Test() != SMBSUCCESS)
    SMBWarning("Tools test failed");

  /////////////////////////////////////////////////
  // Points and rectangles
  cout<<"Testing SMBPoint"<<endl;
  if (SMBPoint_Test() != SMBSUCCESS)
    SMBWarning("Point test failed");

  cout<<"Testing SMBRectangle"<<endl;
  if (SMBRectangle_Test() != SMBSUCCESS)
    SMBWarning("Rectangle test failed");

  /////////////////////////////////////////////////
  // CSMBST_Transposition class
  cout<<"Testing CSMBST_Transposition"<<endl;
  if (SMBTransposition_Test() != SMBSUCCESS)
    SMBWarning("Transposition test failed");


  return 0;
}

