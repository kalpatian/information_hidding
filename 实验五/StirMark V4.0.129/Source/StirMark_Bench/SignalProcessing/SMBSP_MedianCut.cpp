//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBSP_MedianCut.cpp
//
// Contents: Implementation of the CSMBSP_MedianCut class.
//
// Purpose:  See SMBSP_MedianCut.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SMBSP_MedianCut.cpp,v 1.11 2002/04/19 10:23:58 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers

// SMB headers
#include "SMBSP_MedianCut.h"
#include "../Base/SMBError.h"
#include "../Tests/SMBTestGT.h"
#include "../Base/SMBImage.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBSP_MedianCut::CSMBSP_MedianCut(uint in_size)
{

  if (in_size > SMB_MEDIAN_CUT_MAX_SIZE)
  {
    SMBWarning(TString("[CSMBSP_MedianCut] - Unexpected size. Max default size (") + 
      SMB_MEDIAN_CUT_MAX_SIZE + TString(") will be used."));
    m_GridPar = SMB_MEDIAN_CUT_MAX_SIZE;
  }
  else if (in_size == 0)
  {
    SMBWarning(TString("[CSMBSP_MedianCut] - Unexpected size. Default size (")+ 
      SMB_MEDIAN_CUT_DEFAULT_SIZE + TString(") will be used."));
    m_GridPar = SMB_MEDIAN_CUT_DEFAULT_SIZE;
  }
  else if (in_size % 2 == 0)
  {
    SMBWarning(TString("[CSMBSP_MedianCut] - Size must be an odd number."));
    m_GridPar = in_size + 1;
  }
  else
    m_GridPar = in_size;
  m_rggPixelTable = new Gray[m_GridPar * m_GridPar];
  m_GridPar = m_GridPar / 2;

  // Very improbable...
  if (m_rggPixelTable == 0)
    m_GridPar = 0;
}

CSMBSP_MedianCut::~CSMBSP_MedianCut()
{
  delete [] m_rggPixelTable;
}


//////////////////////////////////////////////////////////////////////

static int _GrayCompare(const void *arg1, const void *arg2)
{
  return (*(Gray*)(arg1) - *(Gray*)(arg2));
}  

Gray CSMBSP_MedianCut::GetNewPixelValue(int in_x, int in_y, uint in_channel)
{
  
  int dx, dy, c;
  long x, y;
    
  // initialisatin of the Pixel table
  c = 0;
  if (m_GridPar == 0)
    return m_pimgOriginal->GetPixel(in_x, in_y, in_channel);

  for (dx = -m_GridPar; dx <= m_GridPar; dx++)
  {
    for (dy = -m_GridPar; dy <= m_GridPar; dy++)
    {
      x = in_x + dx;
      y = in_y + dy;
      if (!(x < 0 || x >= (int)m_pimgOriginal->NumberOfColumns() ||
            y < 0 || y >= (int)m_pimgOriginal->NumberOfRows()))
        m_rggPixelTable[c++] = m_pimgOriginal->GetPixel(x, y, in_channel);
    }
  }
  
  // median cut
  qsort(m_rggPixelTable, c, sizeof(Gray), _GrayCompare); 

  return m_rggPixelTable[(c + 1) / 2];
}
