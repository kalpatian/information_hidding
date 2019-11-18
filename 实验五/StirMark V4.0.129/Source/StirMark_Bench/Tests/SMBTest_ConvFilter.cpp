//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTest_ConvFilter.cpp
//
// Contents: Implementation of the CSMBTest_ConvFilter class.
//
// Purpose:  See SMBTest_ConvFilter.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTest_ConvFilter.cpp,v 1.14 2002/04/19 10:24:00 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#include "../Tests/SMBTest_ConvFilter.h"

// STL headers
// DO NOT USE standard iostream headers (not compatible)
// See: http://www.sgi.com/Technology/STL/
#include <iostream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// Other standard headers
#include <assert.h>

// SMB headers
#include "../SignalProcessing/SMBSP_ConvFilter.h"
#include "../Base/SMBConfig.h"
#include "../Base/SMBTools.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSMBTest_ConvFilter::CSMBTest_ConvFilter()
  : CSMBTestSP()
{
  Setup();
}


CSMBTest_ConvFilter::CSMBTest_ConvFilter(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance)
  : CSMBTestSP(in_cstrIniPath, in_pbenchInstance)
{
  Setup();
}


CSMBTest_ConvFilter::~CSMBTest_ConvFilter()
{

}




void CSMBTest_ConvFilter::Setup()
{
  m_strTestName = "Test_ConvFilter";
  m_strTestTag  = "CONV";
}


void CSMBTest_ConvFilter::InitTest(const CSMBImage &in_imgSource)
{
  CSMBMatrix * pFilter;
  list<double> lstdValues;

  int n = 1;
  int count;

  while ( (count = ParseProfileListReal(m_strTestName,
					TString("filter") + CSMBString(n),
					m_strIniFilePath,
					lstdValues)) )
  {
    assert(count >= 4);
    int width    = (int)(lstdValues.front()); lstdValues.pop_front();
    int height   = (int)(lstdValues.front()); lstdValues.pop_front();
    double scale = lstdValues.front(); lstdValues.pop_front();

    pFilter = new CSMBMatrix(width, height);
    for (int i = 0; i < width; i++)
    {
      for (int j = 0; j < height; j++)
      {
        pFilter->Set(i, j, lstdValues.front() / scale);
        lstdValues.pop_front();
      }
    }

    m_lstptrfwValueSet.push_back(pFilter);
    m_lstdpValueSet.push_back(n++);
  }
}


void CSMBTest_ConvFilter::SetParameter(const CSMBImage &in_imgOriginal,
                                             double     in_par)
{
  int n = 1;
  m_ptrfwValueSet = m_lstptrfwValueSet.begin();
  while (n++ < in_par) m_ptrfwValueSet++;
}

//////////////////////////////////////////////////////////////////////
// Run: main function
//////////////////////////////////////////////////////////////////////
void CSMBTest_ConvFilter::DoTransform(const CSMBImage &in_imgSource, 
                                      CSMBImage      &out_imgAttacked) 
{
  CSMBSP_ConvFilter *pConvFilter = new CSMBSP_ConvFilter((*m_ptrfwValueSet)());
  
  pConvFilter->ApplyTransform(in_imgSource, out_imgAttacked);

  delete pConvFilter;
}


