//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTestTR.cpp
//
// Contents: Implementation of the CSMBTestTR class.
//
// Purpose:  See SMBTestTR.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 17 February 2002
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTestTR.cpp,v 1.10 2002/04/19 10:24:00 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL Headers

// Other standard headers

// SMB headers
#include "SMBTestTR.h"
#include "../Base/SMBMarkingScheme.h"
#include "../Base/SMBError.h"
#include "../Base/SMBMemoryException.h"
#include "../Base/SMBFileException.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTestTR::CSMBTestTR()
  : CSMBTest()
{

}


CSMBTestTR::CSMBTestTR(TCString &in_cstrIniPath, 
		       CSMBBench *const in_pbenchInstance)
: CSMBTest(in_cstrIniPath, in_pbenchInstance)
{

}


CSMBTestTR::~CSMBTestTR()
{

}


//////////////////////////////////////////////////////////////////////
// Main function
//////////////////////////////////////////////////////////////////////

ErrorNum CSMBTestTR::Run(const CSMBImage         &in_imgOriginal,
                               CSMBMarkingScheme &in_mksUnderTest)
{
  list<double>::iterator pdpValue;

  //////////////////////////
  // Test initialisation
  SMBInformation(TString("Initialise ") + m_strTestName);
  InitTest(in_imgOriginal);

  // TODO: How many times should the watermark/attack
  //       process be repeated?

  //////////////////////////
  // Image watermarking
  CSMBImage imgOut, imgWM;

  // Use a random key and a random message to embedd the watermark
  in_mksUnderTest.SetRandomKey();
  in_mksUnderTest.SetRandomMsg();
  in_mksUnderTest.SetStrength(SMB_DEFAULT_MARKING_STRENGTH);
  ErrorNum result = in_mksUnderTest.EmbedImg(in_imgOriginal, imgWM);
  if (result != SMBSUCCESS)
  {
    SMBWarning("[SMBTestTR::Run] - Could not watermark the image. Exit test.");
    return result;
  }


  //////////////////////////
  // For all the parameters of the test
  for (pdpValue  = m_lstdpValueSet.begin();
       pdpValue != m_lstdpValueSet.end();
       pdpValue++)
  {
    SMBInformation(TString("  parameter = ") + TString(*pdpValue));
    SetParameter(imgWM, *pdpValue);

    // Output image may have a different size
    uint NewX, NewY;
    GetNewSize(in_imgOriginal, NewX, NewY);
    CSMBImage imgOut;
    CSMBMemoryException e;
    try
    {
      imgOut.InitialiseFrom(in_imgOriginal, e, NewX, NewY); 
    }
    catch (CSMBMemoryException *in_exception)
    {
      in_exception->PrintMsg("[CSMBTestTR::Run] - Not enough memory to create temporary image. Exit test.");
      return SMBFAILURE;
    }
    SMBInformation(TString("  Output image created (") +
                   TString((int)NewX) + TString("x") + TString((int)NewY) + ")");
    
    SMBInformation("  Applying transformation");
    DoTransform(imgWM, imgOut);

    try
    {
      imgOut.SaveTaggedImage(m_strTestTag, *pdpValue);
    }
    catch (CSMBFileException *pException)
    {
      pException->PrintMsg();
      delete pException;
      break;
    }


    // Watermark detection/extraction
    result = in_mksUnderTest.ExtractImg(imgOut, in_imgOriginal);
    if (result != SMBSUCCESS)
    {
      SMBWarning("[CSMBTestTR::Run] - " + GetTestName() + " failed.");
      break;
    }

    
    // Log results including PSNR
    switch (in_mksUnderTest.GetSchemeFamily())
    {
    case SF_PRIVATE_1:
    case SF_BLIND_1:
      LogNumericalResult(*pdpValue, imgOut, imgWM, "BER", in_mksUnderTest.GetResult());
      break;

    case SF_PRIVATE_2:
    case SF_BLIND_2:
      LogNumericalResult(*pdpValue, imgOut, imgWM, "Certainty", in_mksUnderTest.GetResult());
      break;

    default:
      LogNumericalResult(*pdpValue, imgOut, imgWM, "Extraction result", in_mksUnderTest.GetResult());
      break;
    }
  } // For pdpValue
  
  return SMBSUCCESS;
}
