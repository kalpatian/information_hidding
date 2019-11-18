//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBGT_Affine.cpp
//
// Contents: Implementation of the CSMBGT_Affine class
//
// Purpose:  See SMBGT_Affine.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/GeometricTransforms/SMBGT_Affine.cpp,v 1.11 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <memory.h>
#include <assert.h>

// SMB headers
#include "SMBGT_Affine.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSMBGT_Affine::CSMBGT_Affine()
  : m_matTran(2, 3),
    m_matTran1(2, 3)
{
  // Default is identity matrix
  Set_F_Coefs(1, 0, 0, 0, 1, 0);
  SetInverseMatrix();
}


CSMBGT_Affine::CSMBGT_Affine(const CSMBMatrix * in_pmatTran)
  : m_matTran(*in_pmatTran),
    m_matTran1(2, 3)
{
  assert(in_pmatTran != 0);
  assert(in_pmatTran->Width() == 3 && in_pmatTran->Height() == 2);
  
  SetInverseMatrix();
}


CSMBGT_Affine::~CSMBGT_Affine()
{

}


CSMBGT_Affine & CSMBGT_Affine::operator =(const CSMBGT_Affine in_gt)
{
  m_matTran = in_gt.m_matTran;

  this->SetOrigin(in_gt.m_Xorigin, in_gt.m_Yorigin);

  SetInverseMatrix();

  return *this;
}


//////////////////////////////////////////////////////////////////////
// Application of the transformation or its inverse
dVector CSMBGT_Affine::F(double in_x, double in_y) const
{
  dVector dvTMP;

  dvTMP.x =  m_matTran.Get(0, 0) * in_x 
           + m_matTran.Get(0, 1) * in_y
           + m_matTran.Get(0, 2);

  dvTMP.y =  m_matTran.Get(1, 0) * in_x 
           + m_matTran.Get(1, 1) * in_y
           + m_matTran.Get(1, 2);

  return dvTMP;
}

dVector CSMBGT_Affine::F1(double in_x, double in_y) const
{
  dVector dvTMP;

  dvTMP.x =  m_matTran1.Get(0, 0) * in_x 
           + m_matTran1.Get(0, 1) * in_y
           + m_matTran1.Get(0, 2);

  dvTMP.y =  m_matTran1.Get(1, 0) * in_x 
           + m_matTran1.Get(1, 1) * in_y
           + m_matTran1.Get(1, 2);

  return dvTMP;
}

//////////////////////////////////////////////////////////////////////
// We use the convention that when two affine transforms A and B, with
// different origins O1 and O2, are composed to give AB, the resulting
// affine transform has O2 as an origin.
//
// Here this takes the value of composition (A <- AB)
//
// To compose transfo A with origin O1 by transfo B of origin O2, 
// we first move the origin of A to O2 and then use the classic
// compostion
//
// Rotation.ComposeRight(Translation) gives Rotation(Translation(object))

void CSMBGT_Affine::ComposeRight(const CSMBGT_Affine& in_affTranRight)
{
  // Move origin of this to origin of in_affTranRight
  TransferOrigin(in_affTranRight.GetXOrigin(), in_affTranRight.GetYOrigin());
  
  CSMBMatrix matTmp(2, 3);
  matTmp.Set(0, 0,   m_matTran.Get(0, 0) * in_affTranRight.m_matTran.Get(0, 0)
                   + m_matTran.Get(1, 0) * in_affTranRight.m_matTran.Get(0, 1));
  matTmp.Set(0, 1,   m_matTran.Get(0, 1) * in_affTranRight.m_matTran.Get(0, 0)
                   + m_matTran.Get(1, 1) * in_affTranRight.m_matTran.Get(0, 1));
  matTmp.Set(0, 2,   m_matTran.Get(0, 2) * in_affTranRight.m_matTran.Get(0, 0)
                   + m_matTran.Get(1, 2) * in_affTranRight.m_matTran.Get(0, 1)
                   + in_affTranRight.m_matTran.Get(0, 2));
  matTmp.Set(1, 0,   m_matTran.Get(0, 0) * in_affTranRight.m_matTran.Get(1, 0)
                   + m_matTran.Get(1, 0) * in_affTranRight.m_matTran.Get(1, 1));
  matTmp.Set(1, 1,   m_matTran.Get(0, 1) * in_affTranRight.m_matTran.Get(1, 0)
                   + m_matTran.Get(1, 1) * in_affTranRight.m_matTran.Get(1, 1));
  matTmp.Set(1, 2,   m_matTran.Get(0, 2) * in_affTranRight.m_matTran.Get(1, 0)
                   + m_matTran.Get(1, 2) * in_affTranRight.m_matTran.Get(1, 1)
                   + in_affTranRight.m_matTran.Get(1, 2));
  m_matTran = matTmp;
  
  SetInverseMatrix();
}


//////////////////////////////////////////////////////////////////////
// Setting of the coefficients
//////////////////////////////////////////////////////////////////////

void CSMBGT_Affine::SetCoefs(const CSMBMatrix * in_pmatTran)
{
  assert(in_pmatTran != 0);
  assert(in_pmatTran->Width() == 3 && in_pmatTran->Height() == 2);

  m_matTran = *in_pmatTran;
  SetInverseMatrix();
}


void CSMBGT_Affine::Set_F_Coefs(double in_f1, double in_f2, double in_df,
                                double in_g1, double in_g2, double in_dg)
{
  m_matTran.Set(0, 0, in_f1);
  m_matTran.Set(0, 1, in_f2);
  m_matTran.Set(0, 2, in_df);
  m_matTran.Set(1, 0, in_g1);
  m_matTran.Set(1, 1, in_g2);
  m_matTran.Set(1, 2, in_dg);
  SetInverseMatrix();
}


//////////////////////////////////////////////////////////////////////

dVector CSMBGT_Affine::XYTransfo(double in_x, double in_y) const
{
  dVector dvTMP;

  dvTMP = F(in_x - m_Xorigin, in_y - m_Yorigin);
  dvTMP.x += m_Xorigin;
  dvTMP.y += m_Yorigin;

  return dvTMP;
}


//////////////////////////////////////////////////////////////////////
// Inverse matric computation: m_matTran gives the new coord. (X') as
// a function of the old ones (X) so if we have:
//                  X' = A . X + S 
// then             
//                  X  = B . X' + T
// where
//                  B  = inv(A)
//                  T  = - B . S
//
// we will then be able to compute the coord of some transformed point

void CSMBGT_Affine::SetInverseMatrix(void)
{
  double  detA;

  detA =  m_matTran.Get(0, 0) * m_matTran.Get(1, 1)
        - m_matTran.Get(0, 1) * m_matTran.Get(1, 0);

  // Inv(A)= comA transpose
  m_matTran1.Set(0, 0,   m_matTran.Get(1, 1) / detA);
  m_matTran1.Set(0, 1, - m_matTran.Get(0, 1) / detA);
  m_matTran1.Set(1, 0, - m_matTran.Get(1, 0) / detA);
  m_matTran1.Set(1, 1,   m_matTran.Get(0, 0) / detA);

  m_matTran1.Set(0, 2, - m_matTran1.Get(0, 0) * m_matTran.Get(0, 2)
                       - m_matTran1.Get(0, 1) * m_matTran.Get(1, 2));
  m_matTran1.Set(1, 2, - m_matTran1.Get(1, 0) * m_matTran.Get(0, 2)
                       - m_matTran1.Get(1, 1) * m_matTran.Get(1, 2));
}


//////////////////////////////////////////////////////////////////////
// New canvas of the transformed image
//////////////////////////////////////////////////////////////////////

dCanvas CSMBGT_Affine::GetNewCanvas(double in_Xmax, double in_Ymax) const
{
  
  dCanvas NewCanvas; 
  
  // image of a point of the canevas
  double Xcalc,Ycalc;

  // We compute the coordinates of the 4 canvas points of the transformed image
  // and find the box that contains these points.

  // image of (0, 0)
  NewCanvas.min.x = NewCanvas.max.x = m_matTran.Get(0, 2);
  NewCanvas.max.y = NewCanvas.min.y = m_matTran.Get(1, 2);
  
  // image of (in_Xmax, 0)
  Xcalc = in_Xmax * m_matTran.Get(0, 0) + m_matTran.Get(0, 2);
  Ycalc = in_Xmax * m_matTran.Get(1, 0) + m_matTran.Get(1, 2);
  
  if (Xcalc > NewCanvas.max.x) NewCanvas.max.x = Xcalc;
  if (Ycalc > NewCanvas.max.y) NewCanvas.max.y = Ycalc;
  if (Xcalc < NewCanvas.min.x) NewCanvas.min.x = Xcalc;
  if (Ycalc < NewCanvas.min.y) NewCanvas.min.y = Ycalc;

  // image of (in_Xmax, in_Ymax)
  Xcalc = in_Xmax * m_matTran.Get(0, 0) + in_Ymax * m_matTran.Get(0, 1) + m_matTran.Get(0, 2); 
  Ycalc = in_Xmax * m_matTran.Get(1, 0) + in_Ymax * m_matTran.Get(1, 1) + m_matTran.Get(1, 2); 
  
  if (Xcalc > NewCanvas.max.x) NewCanvas.max.x = Xcalc;
  if (Ycalc > NewCanvas.max.y) NewCanvas.max.y = Ycalc;
  if (Xcalc < NewCanvas.min.x) NewCanvas.min.x = Xcalc;
  if (Ycalc < NewCanvas.min.y) NewCanvas.min.y = Ycalc;
  
  // image of (0, in_Ymax)
  Xcalc = in_Ymax * m_matTran.Get(0, 1) + m_matTran.Get(0, 2); 
  Ycalc = in_Ymax * m_matTran.Get(1, 1) + m_matTran.Get(1, 2); 
  
  if (Xcalc > NewCanvas.max.x) NewCanvas.max.x = Xcalc;
  if (Ycalc > NewCanvas.max.y) NewCanvas.max.y = Ycalc;
  if (Xcalc < NewCanvas.min.x) NewCanvas.min.x = Xcalc;
  if (Ycalc < NewCanvas.min.y) NewCanvas.min.y = Ycalc;
  
  return NewCanvas;  
}


//////////////////////////////////////////////////////////////////////
// Changes the origin of the affine tranformation
//
// if we have 
//            X' - X1 = A.(X - X1)                      >> origin X1
// then we have
//            X' - X2 = A.(X - X2) + (A - 1).(X2 - X1); >> origin X2
void CSMBGT_Affine::TransferOrigin(double in_x, double in_y)
{
  double dx, dy;
  double a11, a12, a21, a22;

  // X2 - X1
  dx = in_x - GetXOrigin(); 
  dy = in_y - GetYOrigin();

  a11 = m_matTran.Get(0, 0);
  a12 = m_matTran.Get(0, 1);
  a21 = m_matTran.Get(1, 0);
  a22 = m_matTran.Get(1, 1);

  m_matTran.Set(0, 2, m_matTran.Get(0, 2) +  ( a11 - 1 ) * dx  +     a12   * dy);
  m_matTran.Set(1, 2, m_matTran.Get(1, 2) +      a21     * dx  + ( a22 -1) * dy);

  SetOrigin(in_x, in_y);
}
