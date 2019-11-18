//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTest_RotationScale.cpp
//
// Contents: Implementation of the CSMBTest_RotationScale class.
//
// Purpose:  See SMBTest_RotationScale.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 9 January 2001
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTest_RotationScale.cpp,v 1.15 2002/04/19 10:24:00 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL Headers

// Other standard headers
#include <math.h>

// SMB headers
#include "SMBTest_RotationScale.h"
#include "../Base/SMBTools.h"
#include "../GeometricTransforms/SMBGT_Rotation.h"
#include "../GeometricTransforms/SMBGT_Rescale.h"
#include "../Base/SMBImage.h"
#include "SMBTest_RotationCrop.h"
#include "../Base/SMBConfig.h"

#ifdef SMB_DEFAULT_REC

  #if   (SMB_DEFAULT_REC == SMB_REC_INTERPOLATING_QUADRATIC)
    #include "../GeometricTransforms/SMBRecInterpolatingQuadratic.h"
    typedef CSMBRecInterpolatingQuadratic recDefault;
  #elif (SMB_DEFAULT_REC == SMB_REC_LINEAR_INTERPOLATION)
    #include "../GeometricTransforms/SMBRecLinearInterpolation.h"
    typedef CSMBRecLinearInterpolation recDefault;
  #elif (SMB_DEFAULT_REC == SMB_REC_NEAREST_NEIGHBOUR)
    #include "../GeometricTransforms/SMBRecNearestNeighbour.h"
    typedef CSMBRecNearestNeighbour recDefault;
  #else
    #error SMB ERROR: No valid default reconstructor defined
  #endif // SMB_DEFAULT_REC

#else

  #error SMB ERROR: No default reconstructor defined

#endif // SMB_DEFAULT_REC


#ifdef SMB_DEFAULT_SAM

  #if (SMB_DEFAULT_SAM == SMB_SAM_POINT)
    #include "../GeometricTransforms/SMBSamPoint.h"
    typedef CSMBSamPoint samDefault;
  #else
    #error SMB ERROR: No valid default reconstructor defined
  #endif // SMB_DEFAULT_SAM

#else

  #error SMB ERROR: No default reconstructor defined

#endif // SMB_DEFAULT_SAM

// Other definitions



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTest_RotationScale::CSMBTest_RotationScale()
  : CSMBTest_Rotation()
{
  Setup();
}

CSMBTest_RotationScale::CSMBTest_RotationScale(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance)
  : CSMBTest_Rotation(in_cstrIniPath, in_pbenchInstance)
{
  Setup();
}

CSMBTest_RotationScale::~CSMBTest_RotationScale()
{

}

void CSMBTest_RotationScale::Setup()
{
  m_strTestName = "Test_RotationScale";
  m_strTestTag  = "ROTSCALE";
}

//////////////////////////////////////////////////////////////////////
// Main function
//////////////////////////////////////////////////////////////////////
void CSMBTest_RotationScale::SetParameter(const CSMBImage &in_imgOriginal, double in_par)
{
  double alpha = (double)in_par; /* Deg */

  CSMBGT_Rotation traRotation;
  traRotation.SetRotationPars(alpha, 0, 0);

  double rotateAngle = fabs(traRotation.GetRotationAngleRad());
  double sinAngle = sin(rotateAngle);
  double cosAngle = cos(rotateAngle);
  double a = SMBMax(in_imgOriginal.NumberOfColumns(), in_imgOriginal.NumberOfRows());
  double b = SMBMin(in_imgOriginal.NumberOfColumns(), in_imgOriginal.NumberOfRows());
  double scale = SMBMin(fabs(b / (a * sinAngle + b * cosAngle)),
                        fabs(b / (a * sinAngle - b * cosAngle)));


  CSMBGT_Rescale traScale;
  assert(scale != 0);
  traScale.SetRescaleFactor(1 / scale);

  m_traAffine = traScale;
  m_traAffine.ComposeRight(traRotation);
  m_traAffine.SetOrigin(in_imgOriginal.GetXmax() / 2, in_imgOriginal.GetYmax() / 2);
}



void CSMBTest_RotationScale::GetNewSize(const CSMBImage & in_imgOriginal, 
                                              uint &     out_lXSize,
                                              uint &     out_lYSize) const
{
  out_lXSize = in_imgOriginal.NumberOfColumns();
  out_lYSize = in_imgOriginal.NumberOfRows();
}

//////////////////////////////////////////////////////////////////////
// For the particular case of geometric transformations,
// resampler, transformer and reconstructor are used.
void CSMBTest_RotationScale::DoTransform(const CSMBImage &in_imgSource, 
                                        CSMBImage       &out_imgAttacked)
{
  recDefault rec;
  samDefault sam;
  
  sam.SetOffset((int)((in_imgSource.GetXmax() - out_imgAttacked.GetXmax()) / 2.0),
	              (int)((in_imgSource.GetYmax() - out_imgAttacked.GetYmax()) / 2.0));

  sam.Resample(in_imgSource, out_imgAttacked, rec, * GetpTransformer());
}



  
