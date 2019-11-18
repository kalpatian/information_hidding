//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBGT_SmallRandomDistortions.h
//
// Contents: Implementation of the CSMBGT_SmallRandomDistortions class
//
// Purpose:  This classes implements the small random geometric
//           distortions which appeared in the previous version of
//           StirMark. It also provides distortions which have been
//           improved since the last version.
//           The type of distortion can be selected using the
//           DistortionType num values.
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 6 July 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/GeometricTransforms/SMBGT_SmallRandomDistortions.h,v 1.14 2002/04/19 10:23:56 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#if !defined(_SMBGT_SMALLRANDOMDISTORTIONS_H_)
#define      _SMBGT_SMALLRANDOMDISTORTIONS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// STL headers

// Other standard headers

// SMB headers
#include "SMBTransformer.h"
#include "SMBDistortionMap.h"

// Other definitions
class CSMBImage;

#define SMBGT_RNDDIST_INWARDS        (2.0)  // Default inward corner displacement
#define SMBGT_RNDDIST_OUTWARDS       (0.7)  // Default outward corner displacement
#define SMBGT_RNDDIST_RANDOM_FACTOR  (0.2)  // Default randomisation factor
#define SMBGT_RNDDIST_BENDING_FACTOR (2.0)  // Default bending deviation
#define SMBGT_RNDDIST_MAP_AMPLITUDE  (1.75) // Percentage of image size
#define SMBGT_RNDDIST_MAP_RANDOMNESS (1)    // 'randomness' factor used for the
                                            // distortion map
#define SMBGT_RNDDIST_PHASE_RANGE    (PI)   // Random phase for geometric distortions
                                            // between -PHASE_RANGE and +PHASE_RANGE



class CSMBGT_SmallRandomDistortions : public CSMBTransformer  
{
public:
  ////////////////
  // Construction / destruction

  // If the seed is 0, the current time is used as seed to the
  // random number generator
	CSMBGT_SmallRandomDistortions(uint in_uSeed = 0);
	virtual ~CSMBGT_SmallRandomDistortions();


  ////////////////
  // Options

  // Distortion type
  enum DistortionType
  {
    StirMark1,
    StirMark2,
    StirMark3,
    Latest
  };


  ////////////////
  // Basic initialisation
  void Initialise(const CSMBImage & in_imgOriginal);


  ////////////////
  // Set functions
  void SetMaxInwardCornerDisplacement (int    in_nInwards);  // %
  void SetMaxInwardCornerDisplacement (double in_dInwards);  // Pixel
  void SetMaxOutwardCornerDisplacement(int    in_nOutwards); // %
  void SetMaxOutwardCornerDisplacement(double in_dOutwards); // Pixel

  void SetStrength(double in_dStrength);

  void SetType(DistortionType in_nType);
  
  inline void SetMaxChannelVariation(double in_dDeviation);
  
  inline void SetRandomFactor (double in_dRandomFactor);
  inline void SetBendingFactor(double in_dBendingFactor);
  inline void SetMapAmplitude (double in_dMapAmplitude);


protected:
  // Virtual function inhereted from CSMBTransformer
  dVector F1(double in_x, double in_y) const;


private:
  ////////////////
  // Distortion parameters

  // StirMark1
  Bool m_isRelativeInwards;  // Define whether dInwards is a % or a number of pixels
  Bool m_isRelativeOutwards; // Define whether dOutwards is a % or a number of pixels

  double m_dInwards;
  double m_dOutwards;

  dVector m_dvulDev; // Upper left corner deviation
  dVector m_dvurDev; // Upper right corner deviation
  dVector m_dvllDev; // Lower left corner deviation
  dVector m_dvlrDev; // Lower right corner deviation

  // StirMark2
  double m_dBendingFactor;  // Amplitude of the global bending
  double m_dRandomFactor;   // Amplitude of the high frequency perturbations
  
  dVector m_dvPhase; // Phase of the wobbling introduced

  // Latest
  double m_dMapAmplitude;
  
  CSMBDistortionMap m_DistMapx; // Distortion map for x coordinate
  CSMBDistortionMap m_DistMapy; // Distortion map for y coordinate

#ifdef TEST_DISTORTION
  float m_fFrequency;
#endif


  ////////////////
  // Other parameters
  DistortionType m_nType;
  double         m_dStrength; // Multiplicative factor of the distortion

  // Size of the original image
  uint  m_lCols;
  uint  m_lRows;
  uint  m_nChannels;

  // Random number generator
  CSMBRandomNumberGenerator m_RNG;
};

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING
int SMBGT_SmallRandomDistortions_Test();
#endif // SMB_CODE_TESTING

#endif // !defined(_SMBGT_SMALLRANDOMDISTORTIONS_H_)
