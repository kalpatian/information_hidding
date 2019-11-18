//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBMarkingScheme.h
//
// Contents: Definition of the CSMBMarkingScheme class
//
// Purpose:  This class is a general wrapper for the possible watermarking
//           schemes that can be evaluated. Currently we use a SchemeFamily
//           type value to distinguishe the different type of watermarking
//           scheme. We could also have a root class and then use different
//           sub-classes for the different types of schemes.
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBMarkingScheme.h,v 1.18 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////

#if !defined(_SMB_MARKING_SCHEME_H_)
#define      _SMB_MARKING_SCHEME_H_

#if _MSC_VER > 1000
#pragma once
#pragma warning (push)
#pragma warning (disable: 4786 4290)
#endif // _MSC_VER > 1000

// SMB headers
#include "SMBTypes.h"
#include "SMBConfig.h"
#include "StirMarkBenchmark.h"
#include "SMBString.h"
#include "SMBImage.h"
#ifdef SMB_SQL_IS_ENABLED
#include "SMBDatabase.h"
#endif // SMB_SQL_IS_ENABLED

// Other standard header
#ifdef WIN32
#include <windows.h> // for DLL operations (HINSTANCE...)
#endif // WIN32
#ifdef __UNIX__
#include <dlfcn.h>   // dynamic library for Unix
#endif // __UNIX__


// Other definitions

// Type declarations for late loading of the methods in the Library
// THIS HAS TO BE EXACTLY LIKE IN THE LIBRARY HEADER

typedef ErrorNum (*lpSchemeInfoReturner)(uint      in_nInfo,
                                         STR      out_pbData,
                                         uint * inout_pcbData);

typedef ErrorNum (*lpImageEmbedder) (const SMBImage        in_imgOriginal, // Original image
                                     SMBImage *           out_pimgTarget,  // Image  to mark
                                     const SMBSchemePars * in_pPars );     // Pars for embedding

typedef ErrorNum (*lpImageExtractor) (const SMBImage     in_imgTest,     // Marked/attacked image
                                      const SMBImage     in_imgOriginal, // Marked/unmarked image | 0
                                      SMBSchemePars * inout_pPars   );   // Pars for extraction & output
class CSMBBench;

class CSMBMarkingScheme  
{
public:
  CSMBMarkingScheme(CSMBBench * in_pbenchInstance);

  // Set functions
  // length values in number of bytes
  void SetLibrary(TCString &in_LIBPath, CSMBMemoryException &inout_exception) throw (CSMBException *);

  void SetKey(TString in_strKey);
  void SetRandomKey(void);
  void SetRandomMsg(void);

  void SetPSNR(float in_fPSNR);
  void SetCertainty(double in_dpCertainty);
  void SetStrength(double in_dpStrength);

  double GetResult() const;
  

  // the initialisation is done in the constructor
  // using the DLL late loading
    
  // Equivalent header: SchemeInfoTag GetSchemeInfoMKS() const;
  lpSchemeInfoReturner GetSchemeInfoMKS; 
  
  // these methods are just encapsulating m_image_Embed/m_pExtract
  // having CSMBImage as parameter instead of SMBImage
  ErrorNum EmbedImg(const CSMBImage  &in_imgOriginal, // Original image
                          CSMBImage &out_imgMarked);   // Watermarked image

  ErrorNum ExtractImg(const CSMBImage &in_imgTest,      // Marked/attacked image
                      const CSMBImage &in_imgOriginal); // (Un)marked original | NULL

  virtual ~CSMBMarkingScheme();

  CSMBString GetName(void)           const { return CSMBString(m_strName); }
  CSMBString GetVersion(void)        const { return CSMBString(m_strVersion); }
  CSMBString GetAuthor(void)         const { return CSMBString(m_strAuthor); }
  CSMBString GetReleaseDate(void)    const { return CSMBString(m_strReleaseDate); }
  CSMBString GetDescription(void)    const { return CSMBString(m_strDescription); }
  CSMBString GetSourceLocation(void) const { return CSMBString(m_strSourceLocation); }
  CSMBString GetContactAddress(void) const { return CSMBString(m_strContactAddress); }
  uint GetSchemeFamily(void) const { return m_uiSchemeFamily; }
  uint GetMaxKeySize(void)   const { return m_uiMaxKeySize; }
  uint GetMaxMsgSize(void)   const { return m_uiMaxMsgSize; }
  
  //SMBSchemePars* GetSchemeParamters(void) const throw (CSMBMemoryException *);

  void LogInfo(void);

private:
  SMBSchemePars m_parScheme;
  CSMBString    m_strMsg; // Copy of original payload
  

#ifdef WIN32
  HINSTANCE     m_hLibrary;
#endif // WIN32 

#ifdef __UNIX__
  void * m_hLibrary;
#endif // __UNIX__

  lpImageEmbedder      m_pEmbed;
  lpImageExtractor     m_pExtract;
  lpSchemeInfoReturner m_pInfoScheme;

  // Status of the object
  Bool m_fInitialised;

    // Benchmark instance
  CSMBBench * const m_pbenchInstance;

  CSMBString m_strName;           // Name of the marking scheme
  CSMBString m_strVersion;        // Version of the scheme
  CSMBString m_strAuthor;         // Author(s), research group or company
  CSMBString m_strReleaseDate;    // Release date of the current version
  CSMBString m_strDescription;    // Notes and comments regarding the scheme
  CSMBString m_strSourceLocation; // URL of the sources
  CSMBString m_strContactAddress; // Email of the contact
  uint       m_uiMaxMsgSize;      // Maximum length of the embedded message
  uint       m_uiMaxKeySize;      // Maximum length of the stego-key
  uint       m_uiSchemeFamily;    // Family of the watermarking scheme
  
  double m_dpResult; // Certainy of extraction (type II schemes) or BER (type I)


  // Reset the object
  void Reset(void);

  // Utility function used to set the various string members
  void GetStringInformation(CSMBString &strData, int nInfo);
  uint GetNumberInformation(int nInfo);

  // Prevent use of copy constructor
  CSMBMarkingScheme(const CSMBMarkingScheme &);

  CSMBMarkingScheme();

  int HammingDistance(CSTR in_pszA, CSTR in_pszB, uint  in_cch) const;
};

#if _MSC_VER > 1000
#pragma warning (pop)
#endif // _MSC_VER > 1000

#endif // !defined(_SMB_MARKING_SCHEME_H_)
