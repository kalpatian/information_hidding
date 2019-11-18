//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBTestGT.cpp
//
// Contents: Implementation of the CSMBTestGT class.
//
// Purpose:  See SMBTestGT.h
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Tests/SMBTestGT.cpp,v 1.16 2002/04/19 10:23:59 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL Headers

// Other standard headers

// SMB headers
#include "SMBTestGT.h"
#include "../Base/SMBConfig.h"
#include "../Base/SMBMemoryException.h"
#include "../GeometricTransforms/SMBTransformer.h"
#include "../Base/SMBImage.h"

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


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTestGT::CSMBTestGT()
  : CSMBTestST()
{
  
}

CSMBTestGT::CSMBTestGT(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance)
  : CSMBTestST(in_cstrIniPath, in_pbenchInstance)
    // m_psamResampler(0)
    // m_precReconstructor(0)
{
  
}

CSMBTestGT::~CSMBTestGT()
{

}

void CSMBTestGT::GetNewSize(const CSMBImage & in_imgOriginal, 
                                  uint &     out_lXSize,
                                  uint &     out_lYSize) const
{
  dCanvas NewCanvas =  GetpTransformer()->GetNewCanvas(in_imgOriginal.GetXmax(),
                                                       in_imgOriginal.GetYmax());
    
  out_lXSize = (long) (NewCanvas.max.x - NewCanvas.min.x + 1);
  out_lYSize = (long) (NewCanvas.max.y - NewCanvas.min.y + 1);
}

//////////////////////////////////////////////////////////////////////
// For the particular case of geometric transformations,
// resampler, transformer and reconstructor are used.
void CSMBTestGT::DoTransform(const CSMBImage &in_imgSource, 
                             CSMBImage      &out_imgAttacked)
{
  recDefault rec;
  samDefault sam;

  dCanvas canNew =  GetpTransformer()->GetNewCanvas(in_imgSource.GetXmax(), 
                                                   in_imgSource.GetYmax());
  sam.SetOffset( (int)canNew.min.x, (int)canNew.min.y);

  sam.Resample(in_imgSource, out_imgAttacked, rec, * GetpTransformer());
}

