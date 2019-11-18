//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBST_Transposition.cpp
//
// Contents: Implementation of the CSMBST_Transposition class.
//
// Purpose:  See SMBST_Transposition.h
//
// Created:  Frédéric Raynal, INRIA, 6 March 2001
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SpecialTransforms/SMBST_Transposition.cpp,v 1.16 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers

// SMB headers
#include "SMBST_Transposition.h"
#include "../Base/SMBImage.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBST_Transposition::CSMBST_Transposition()
{

}


CSMBST_Transposition::~CSMBST_Transposition()
{

}



//////////////////////////////////////////////////////////////////////

inline Gray CSMBST_Transposition::GetOriginalPixel(int in_x, int in_y, uint in_channel)
{
  return m_pimgOriginal->GetPixel(in_x, in_y, in_channel);
}



//////////////////////////////////////////////////////////////////////

Bool CSMBST_Transposition::ApplyTransform(const CSMBImage &in_imgOriginal, 
                                         CSMBImage &out_imgTarget)
{
  // we save the address of the original image in a member pointer
  // so we can use the GetOriginalPixel method in the derived classes
  m_pimgOriginal=&in_imgOriginal;

  if (!IsValid(out_imgTarget)) 
    return SMBFAILURE;
  
  long x,y,ch,Xmax,Ymax,CHmax;

  Xmax  = m_pimgOriginal->NumberOfColumns();
  Ymax  = m_pimgOriginal->NumberOfRows();
  CHmax = m_pimgOriginal->NumberOfChannels();

  for (x = 0; x < Xmax; x++) {
    for (y = 0; y < Ymax; y++) {

      int out_x, out_y;
      GetNewPoint(x, y, out_x, out_y);

      for (ch = 0; ch < CHmax; ch++) {

        out_imgTarget.SetPixel(out_x, out_y, ch, 
			       m_pimgOriginal->GetPixel(x, y, ch));

      } // for ch
    } // for y
  } // for x
  return SMBSUCCESS;
}





//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <list>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif
#include <assert.h>
#include "../Base/SMBConfig.h"
#include "../Base/SMBMemoryException.h"
#include "../Base/SMBPtrWrapper.h"
#include "../Base/SMBError.h"
#include "../SpecialTransforms/SMBST_Identity.h"
#include "../SpecialTransforms/SMBST_HFlip.h"
#include "../SpecialTransforms/SMBST_VFlip.h"
#include "../SpecialTransforms/SMBST_DFlip.h"
#include "../SpecialTransforms/SMBST_AFlip.h"
#include "../SpecialTransforms/SMBST_Rot90.h"
#include "../SpecialTransforms/SMBST_Rot180.h"
#include "../SpecialTransforms/SMBST_Rot270.h"


typedef CSMBPtrWrapper<CSMBST_Transposition> CSMBTransPtrWrapper;

int SMBTransposition_Test(void)
{

  CSMBMemoryException e;
  CSMBImage img, out;

  try
  {
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_1);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
    delete pException;
    return SMBFAILURE;
  }
  img.SetBaseName(SMB_DEFAULT_SAMPLE_IMAGE_1);

  list<CSMBTransPtrWrapper> lstrans;
  lstrans.push_back(new CSMBST_Identity());
  lstrans.push_back(new CSMBST_HFlip());
  lstrans.push_back(new CSMBST_VFlip());
  lstrans.push_back(new CSMBST_DFlip());
  lstrans.push_back(new CSMBST_AFlip());
  lstrans.push_back(new CSMBST_Rot90());
  lstrans.push_back(new CSMBST_Rot180());
  lstrans.push_back(new CSMBST_Rot270());

  for (list<CSMBTransPtrWrapper>::iterator
       pwrpTrans  = lstrans.begin();
       pwrpTrans != lstrans.end();
       pwrpTrans++)
  {
    try
    {
      out.InitialiseFrom(img, e, (*pwrpTrans)()->GetNewXSize(img), (*pwrpTrans)()->GetNewYSize(img));
    }
    catch (CSMBMemoryException *pe)
    {
      pe->PrintMsg();
      return SMBFAILURE;
    }
    
    if ((*pwrpTrans)()->ApplyTransform(img, out) != SMBSUCCESS)
      SMBWarning("[SMBTransposition_Test] - Error applying " + (*pwrpTrans)()->GetName());
    try
    {
      out.SaveTaggedImage((*pwrpTrans)()->GetName(), 0);
    }
    catch (CSMBException *pe)
    {
      pe->PrintMsg();
      delete pe;
      return SMBFAILURE;
    }
  }
  return SMBSUCCESS;
}


#endif // SMB_CODE_TESTING
