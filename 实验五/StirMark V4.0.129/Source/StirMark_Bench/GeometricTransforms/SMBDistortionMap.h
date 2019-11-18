//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBDistortionMap.h
//
// Contents: Definition of the CSMBDistortionMap class.
//
// Purpose:  TODO
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 27 July 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/GeometricTransforms/SMBDistortionMap.h,v 1.14 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////

#if !defined(_SMBDISTORTIONMAP_H_)
#define      _SMBDISTORTIONMAP_H_

#if _MSC_VER > 1000
#pragma once
#pragma warning (push)
#pragma warning (disable: 4290)
#endif // _MSC_VER > 1000



// STL headers

// Other standard headers

// SMB headers
#include "../Base/SMBRandomNumberGenerator.h"
#include "../Base/SMBMemoryException.h"

// Other definitions
class CSMBImage;

#define SMB_DISTMAP_DUMP_MATRICES



class CSMBDistortionMap
{
public:
	CSMBDistortionMap();
	CSMBDistortionMap(const CSMBDistortionMap &in_distMap);
  virtual ~CSMBDistortionMap();

  void Generate(uint in_N, uint in_M,
                CSMBRandomNumberGenerator &  in_RNG,
                CSMBMemoryException &     inout_exception)
                throw (CSMBMemoryException *);

  void SetRandomParameters(double in_dMapRandomness = 1.0);

  // Access to a particular value of the map
  double operator()(uint in_ux, uint in_uy) const;

  // Convert random map as a grayscale image that can be saved
  void ConvertToImage(CSMBImage &             out_imgRandomMap,
                      CSMBMemoryException & inout_exception) const
                      throw (CSMBMemoryException *);


private:
  double Amplitude(int in_fx, int in_fy, const CSMBRandomNumberGenerator &in_RNG);
  void Clear(void);

#ifdef SMB_DISTMAP_DUMP_MATRICES
  void DumpMatrix(double *in_grdM, uint in_maxi, uint in_maxj, char * in_szName);
#endif

  double   m_dRandomness;
  double * m_rgdMap;
  uint     m_lCols;
  uint     m_lRows;
};

#if _MSC_VER > 1000
#pragma warning (pop)
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING
int SMBDistortionMap_Test();
#endif // SMB_CODE_TESTING

#endif // !defined(_SMBDISTORTIONMAP_H_)
