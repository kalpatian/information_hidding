 //////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBST_Transposition.h
//
// Contents: Definition of the CSMBST_Transposition class.
//
// Purpose: parent for all the transpositions.
//           A transposition is either:
//              - a flip (horizontal, vertical, diagonal or antidiagonal)
//              - a rotation (90, 180 or 270)
//              - identity
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SpecialTransforms/SMBST_Transposition.h,v 1.10 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#if !defined(_SMBST_TRANSPOSITION_H_)
#define      _SMBST_TRANSPOSITION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// STL headers

// Other standard headers

// SMB headers
#include "../Base/SMBTypes.h"
#include "../Base/SMBPtrWrapper.h"

// Other definitions
class CSMBImage;

enum TranspositionType {
  TT_IDENTITY,
  TT_HFLIP,
  TT_VFLIP,
  TT_DFLIP,
  TT_AFLIP,
  TT_ROT90,
  TT_ROT180,
  TT_ROT270
};



class CSMBST_Transposition 
{
  friend CSMBPtrWrapper<CSMBST_Transposition>;

public:
  CSMBST_Transposition();
  virtual ~CSMBST_Transposition();
  
  // Since a transposition can change the size of the output image
  // these 2 functions are a way to know this new size.
  virtual long GetNewXSize(const CSMBImage & in_imgOriginal) const = 0;
  virtual long GetNewYSize(const CSMBImage & in_imgOriginal) const = 0;

  virtual TCString GetName() const = 0;
  virtual TranspositionType GetId() const = 0;

  Bool ApplyTransform(const CSMBImage  &in_imgOriginal, 
                            CSMBImage &out_imgTarget);

  
protected:
  // These transpositions only affects geometrical placements of the pixels.
  // the value is not chaged. It can only be called by ApplyTransform()
  virtual void GetNewPoint(int   in_x, int   in_y, 
                           int & out_x, int & out_y) const = 0;

  // Checks if the dimensions of input and  output are 
  // usable for this transposition
  virtual Bool IsValid(const CSMBImage & out_imgTarget) const = 0;

  // GetOriginalPixel will be used by GetNewPixelValue
  inline Gray GetOriginalPixel(int in_x, int in_y, uint in_channel);
  
  const CSMBImage * m_pimgOriginal;

  virtual CSMBST_Transposition* Clone(void) const = 0;
};


#ifdef SMB_CODE_TESTING

int SMBTransposition_Test(void);

#endif // SMB_CODE_TESTING

#endif // !defined(_SMBST_TRANSPOSITION_H_)
