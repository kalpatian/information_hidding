//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBImage.h
//
// Contents: General class for images whithin StirMark Benchmark software
//
// Purpose:  The CSMBImage class provides the very basic functionalities to 
//           handle raster image such as memory allocation and input ouput
//           facilities. Only grayscale and RGB images are supported.
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, March 2000
//
// Modified: Nazim Fatès, Microsoft Research
//           Frédéric Raynal, INRIA
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBImage.h,v 1.17 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#if !defined(_SMBIMAGE_H_)
#define      _SMBIMAGE_H_

#if _MSC_VER > 1000
#pragma once
#pragma warning (push)
#pragma warning (disable: 4290)
#endif // _MSC_VER > 1000

// STL headers
// DO NOT USE standard iostream headers (not compatible)
// See: http://www.sgi.com/Technology/STL/
#include <iostream>
#include <fstream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// Other standard headers
#include <stdio.h>

// SMB headers
#include "SMBString.h"
#include "SMBMemoryException.h"
#include "SMBFileException.h"
#include "SMBConfig.h"
#include "SMBTools.h"
#include "SMBError.h"

// Other definitions



class CSMBImage
{
  friend class CSMBMarkingScheme;

public:
  CSMBImage();
  virtual ~CSMBImage();

  ////////////////
  // Data access
  void SetPixel(uint in_x, uint in_y, uint in_c, Gray in_val);

  // Get the gray value of a pixel at given coordinates and
  // channel number. in_c may take value 0, 1 or 2.
  // Origin for coordinates is bottom left corner.
  Gray GetPixel  (int in_x, int in_y, uint in_c = 0) const;
  Gray operator()(int in_x, int in_y, uint in_c = 0) const;
  
  Gray GetPixelLuminance(int in_x, int in_y) const;
  
  TString GetTaggedPath(TString in_Tag, double in_Par) const;
  
  ////////////////
  // Basic initialisation of the object
  void Initialise(uint                     in_nCols,
                  uint                     in_nRows,
                  Gray                     in_gMaxVal,
                  ImageType                in_itType,
                  CSMBMemoryException & inout_exception)
                  throw (CSMBMemoryException *);
  void Clear(void);


  ////////////////
  // Initialisation using the parameters of another image
  void InitialiseFrom(const CSMBImage &        in_imgSource,
                      CSMBMemoryException & inout_exception)
                      throw (CSMBMemoryException *);

  void InitialiseFrom(const CSMBImage &        in_imgSource,
                      CSMBMemoryException & inout_exception,
                      uint                     in_nCols,
                      uint                     in_nRows)
                      throw (CSMBMemoryException *);

  ////////////////
  // The use of the copy constructor is prevented and
  // these functions are provided instead
  void CopyFrom(const CSMBImage &        in_imgSource,
                CSMBMemoryException & inout_exception)
                throw (CSMBMemoryException *); 
  
  ////////////////
  // Input/output. Supported ile formats: "PPM", "BMP", "JPEG", "JPG"
  void Save(TString  in_strFilePath,
            TCString in_strFileFormat,
            uint     in_JPEGQuality = 90) const
            throw (CSMBFileException *);
  
  void Load(TCString in_strFilePath)
            throw (CSMBException *);
  
  void SaveTaggedImage(TCString in_Tag, double in_Par) const
                       throw (CSMBFileException *);
  
  ////////////////
  // Access to members
  inline uint NumberOfColumns()  const { return (m_imgValue.nCols);     };
  inline uint NumberOfRows()     const { return (m_imgValue.nRows);     };
  inline uint NumberOfChannels() const { return (m_imgValue.nChannels); };
  
  inline Gray      GetMaxVal()    const { return (m_imgValue.gMaxVal); };
  inline ImageType GetImageType() const { return (m_imgValue.itType);  };

  inline double GetXmax() const { return (double)m_imgValue.nCols - 1.0; }
  inline double GetYmax() const { return (double)m_imgValue.nRows - 1.0; }

  void ExtractRegion(uint         in_xOrigin,
                     uint         in_yOrigin,
		                 CSMBImage & out_region) const;

  void SetBaseName(TCString &in_strImageName);
  TString GetBaseName() const { return TString(m_strBaseName); };


private:
  SMBImage   m_imgValue;
  uint       m_nSize;       // Number of gray values (col x lines x channels)
  TString    m_strBaseName; // Name of the image (e.g., myImage.ppm)

  // GetpImg is dangerous as it gives the adress of the m_imgValue
  // and therefore allows it to be modified (use GetImg otherwise)
  // this method is used in the Embed/Extract functions.
  // TODO: Remove these functions if possible:
  inline SMBImage   GetImg() const { return   m_imgValue; }
  inline SMBImage * GetpImg()      { return & m_imgValue; }

  ////////////////
  // Low level input/ouput function for different format of images
  void ReadPPM (ifstream & in_inStream ) throw (CSMBException *);
  void ReadBMP (FILE *     in_pinStream) throw (CSMBException *);
  void ReadJPEG(FILE *     in_pinStream) throw (CSMBException *);

  void WritePPM (ofstream & in_outStream ) const throw (CSMBException *);
  void WriteBMP (FILE *     in_poutStream) const throw (CSMBException *);
  void WriteJPEG(FILE *     in_poutStream, uint nQuality) const
                 throw (CSMBException *);

  int IsValid() const;
  int IsInBounds(uint in_x, uint in_y, uint in_c) const;

  ////////////////
  // Prevent the use of the copy constructor
  // This simplies files the handling of memory exception in the
  // constructor
private:
  CSMBImage(const CSMBImage&);

};

#if _MSC_VER > 1000
#pragma warning (pop)
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING
int SMBImage_Test();
#endif // SMB_CODE_TESTING

#endif // !defined(_SMBIMAGE_H_)
