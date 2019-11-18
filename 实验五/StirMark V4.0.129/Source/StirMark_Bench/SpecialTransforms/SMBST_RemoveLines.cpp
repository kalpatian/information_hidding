//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBST_RemoveLines.cpp
//
// Contents: Implementation of the CSMBST_RemoveLines class.
//
// Purpose:  See SMBST_RemoveLines.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SpecialTransforms/SMBST_RemoveLines.cpp,v 1.10 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers

// SMB headers
#include "SMBST_RemoveLines.h"
#include "../Base/SMBTools.h"
#include "../Base/SMBImage.h"
#include "../Base/SMBException.h"
#include "../GeometricTransforms/SMBSamPoint.h"
#include "../GeometricTransforms/SMBGT_Affine.h"
#include "../GeometricTransforms/SMBRecNearestNeighbour.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBST_RemoveLines::CSMBST_RemoveLines()
{
  m_Xfreq = 0;
  m_Yfreq = 0;  // produces an error 
}

CSMBST_RemoveLines::~CSMBST_RemoveLines()
{

}

//////////////////////////////////////////////////////////////////////
// Get/Set methods
//////////////////////////////////////////////////////////////////////

long CSMBST_RemoveLines::GetNewXSize(const CSMBImage &in_imgTarget) const
{
  long colRemoved = (in_imgTarget.NumberOfColumns() - 1) / m_Xfreq + 1;
  return in_imgTarget.NumberOfColumns() - colRemoved;
}

long CSMBST_RemoveLines::GetNewYSize(const CSMBImage &in_imgTarget) const
{
  long rowRemoved = (in_imgTarget.NumberOfRows() - 1) / m_Yfreq + 1;
  return in_imgTarget.NumberOfRows() - rowRemoved;
}

void CSMBST_RemoveLines::SetRemoveFrequency(long in_Xfreq, long in_Yfreq)
{
  if (in_Xfreq <= 0 || in_Yfreq <= 0)
    SMBThrowNewException("[CSMBST_RemoveLines::SetRemoveFrequency] - Freq. removal has to be > 0");
  
  m_Xfreq = in_Xfreq;
  m_Yfreq = in_Yfreq;
}
  

//////////////////////////////////////////////////////////////////////
// Main function: remove rows and columns at a given frequency
// (e.g., 1 line every 10 lines)
//////////////////////////////////////////////////////////////////////

void CSMBST_RemoveLines::ApplyTransform(const CSMBImage  &in_imgOriginal, 
                                              CSMBImage &out_imgTarget)
{
  long Xmax, Ymax, CHmax;
  long x_original, y_original, dx, dy;   
  Gray NewPixel;

  Xmax  = out_imgTarget.NumberOfColumns();
  Ymax  = out_imgTarget.NumberOfRows();
  CHmax = out_imgTarget.NumberOfChannels();

  dx = 0;
  for (long x = 0; x < Xmax; x++)
  {
    if (x % (m_Xfreq - 1) == 0)
      dx++; // we skip this column
    
    dy = 0;
    for (long y = 0; y < Ymax; y++)
    {
      if (y % (m_Yfreq - 1) == 0)
        dy++;  // we skip this row
      
      x_original = x + dx;
      y_original = y + dy;
      
      for (int ch = 0; ch < CHmax; ch++)
      {
        NewPixel = in_imgOriginal.GetPixel(x_original, y_original, ch);
        out_imgTarget.SetPixel(x, y, ch, NewPixel);
      } // for ch
    } // for y
  } // for x
}
