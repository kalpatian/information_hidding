//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTest_SmallRandomDistortions.cpp
//
// Contents: implementation of the CSMBTest_SmallRandomDistortions class.
//
// Purpose:  See SMBTest_SmallRandomDistortions.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTest_SmallRandomDistortions.cpp,v 1.13 2002/04/19 10:24:00 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL Headers

// Other standard headers

// SMB headers
#include "SMBTest_SmallRandomDistortions.h"
#include "../GeometricTransforms/SMBRecInterpolatingQuadratic.h"
#include "../GeometricTransforms/SMBSamPoint.h"
#include "../Base/SMBMemoryException.h"
#include "../Base/SMBImage.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTest_SmallRandomDistortions::CSMBTest_SmallRandomDistortions()
  : CSMBTestST(),
    m_rnddist(0),
    m_RNG()
{
  Setup();
}

CSMBTest_SmallRandomDistortions::CSMBTest_SmallRandomDistortions(TCString &in_strIniPath, CSMBBench *const in_pbenchInstance)
  : CSMBTestST(in_strIniPath, in_pbenchInstance)
{
  Setup();
}


CSMBTest_SmallRandomDistortions::~CSMBTest_SmallRandomDistortions()
{

}

void CSMBTest_SmallRandomDistortions::Setup()
{
  m_strTestName = "Test_SmallRandomDistortions";
  m_strTestTag  = "RNDDIST";
}


//////////////////////////////////////////////////////////////////////
void CSMBTest_SmallRandomDistortions::GetNewSize(const CSMBImage & in_imgOriginal, 
                                                       uint &     out_lXSize,
                                                       uint &     out_lYSize) const
{
  out_lXSize = in_imgOriginal.NumberOfColumns();
  out_lYSize = in_imgOriginal.NumberOfRows();
}

void CSMBTest_SmallRandomDistortions::SetParameter(const CSMBImage &in_imgOriginal, double in_dpStrength)
{
  m_rnddist.SetStrength(in_dpStrength);
}

void CSMBTest_SmallRandomDistortions::InitTest(const CSMBImage &in_imgSource)
{
  CSMBTestST::InitTest(in_imgSource);
  m_rnddist.Initialise(in_imgSource);
}

void CSMBTest_SmallRandomDistortions::DoTransform(const CSMBImage &in_imgSource, 
                                                  CSMBImage      &out_imgAttacked)
{

  CSMBRecInterpolatingQuadratic rec;
  CSMBSamPoint sam;
  CSMBImage imgTemp;
  CSMBMemoryException e;

  try
  {
    imgTemp.InitialiseFrom(in_imgSource, e);
  }
  catch (CSMBMemoryException *pException)
  {
    pException->PrintMsg("[DoTransform] - RNDDIST cannot be applied. Attacked image may be random.");
    return;
  }

  dCanvas canNew = m_rnddist.GetNewCanvas(in_imgSource.GetXmax(), 
                                          in_imgSource.GetYmax());
  sam.SetOffset( (int)canNew.min.x, (int)canNew.min.y);
  sam.Resample(in_imgSource, imgTemp, rec, m_rnddist);

  m_dithernoise.ApplyTransform(imgTemp, out_imgAttacked);
}



//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING_NEVER

#include <assert.h>
#include <string.h>

#include "../Base/SMBMarkingScheme.h"

int SMBTest_SmallRandomDistortions_Test()
{
  CSMBImage img;
  CSMBException e;
  CSMBGT_SmallRandomDistortions rnddist1;
  CSMBMarkingScheme mks;
  
  try
  {
    mks.SetLibrary(SMB_DEFAULT_LIBRARY_FILE);
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_1);
  }
  catch (CSMBException *)
  {
    e.PrintMsg();
    return SMBFAILURE;
  }

  CSMBTest_SmallRandomDistortions tst1(TCString("SMBSettings.ini"), TCString("SMBReport.log"));
  tst1.Run(img, mks);

  // Copy constructor
  CSMBTest_SmallRandomDistortions tst2(tst1);

  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
