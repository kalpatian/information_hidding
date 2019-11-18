//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBMarkingScheme.cpp
//
// Contents: Implementation of the CSMBMarkingScheme class.
//
// Purpose:  See SMBMarkingScheme.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, March 2000
//
// Modified: Nazim Fatès, Microsoft Research
//           Frédéric Raynal, INRIA
//
// History:  Frédéric added the UNIX specific code while Nazim and
//           Fabien took care of the Windows code.
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBMarkingScheme.cpp,v 1.26 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// Other standard headers
#include <assert.h>

// SMB headers
#include "SMBMarkingScheme.h"
#include "SMBTools.h"
#include "SMBRandomNumberGenerator.h"
#include "SMBBench.h"
#include "SMBError.h"
#include "SMBException.h"
#include "SMBMemoryException.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBMarkingScheme::CSMBMarkingScheme(CSMBBench * in_pbenchInstance)
: m_strMsg(),
  m_hLibrary(0),
  m_pbenchInstance(in_pbenchInstance)
{
  m_parScheme.in_pszKey        = NULL;
  m_parScheme.in_nKeyLength    = 0;

  m_parScheme.inout_pszMsg     = NULL;
  m_parScheme.inout_nMsgLength = 0;

  Reset();
}


CSMBMarkingScheme::~CSMBMarkingScheme()
{
  Reset();
}

void CSMBMarkingScheme::Reset(void)
{
  assert(m_pbenchInstance != NULL);

  m_fInitialised = FALSE;

  // Clear memory
  if (m_parScheme.in_pszKey) delete [] m_parScheme.in_pszKey;
  if (m_parScheme.inout_pszMsg) delete [] m_parScheme.inout_pszMsg;

  // Set scheme parameters to 0
  m_parScheme.out_dpCertainty  = 0;
  m_parScheme.in_dpPSNR        = 0;
  m_parScheme.in_dpStrength    = 0;
  m_parScheme.in_pszKey        = NULL;
  m_parScheme.in_nKeyLength    = 0;
  m_parScheme.inout_pszMsg     = NULL;
  m_parScheme.inout_nMsgLength = 0;
  m_strMsg                     = "";

  // Set members to 0
  m_pEmbed            = 0;
  m_pExtract          = 0;
  m_pInfoScheme       = 0;
  m_uiMaxKeySize      = 0;
  m_uiMaxMsgSize      = 0;
  m_uiSchemeFamily    = 0;
  m_dpResult          = 0.0;
  m_strName           = "";
  m_strAuthor         = "";
  m_strContactAddress = "";
  m_strDescription    = "";
  m_strReleaseDate    = "";
  m_strSourceLocation = "";
  m_strVersion        = "";

  // Unload library 
  if (m_hLibrary)
  {
#ifdef WIN32
  FreeLibrary(m_hLibrary);
#endif // WIN32

#ifdef __UNIX__
  dlclose(m_hLibrary);
#endif // __UNIX__
  }
}


//////////////////////////////////////////////////////////////////////
// Set/get functions
//////////////////////////////////////////////////////////////////////

void CSMBMarkingScheme::SetLibrary(TCString & in_LIBPath, CSMBMemoryException & inout_exception)
{
  if (m_fInitialised)
    Reset();

#ifdef WIN32
  m_hLibrary = LoadLibrary(in_LIBPath);
  if (m_hLibrary == NULL)
  {
    TString strMessage;
    LPVOID lpMsgBuf;
    FormatMessage( 
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM | 
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) &lpMsgBuf,
      0,
      NULL
      );
    strMessage = (LPTSTR)lpMsgBuf;
    LocalFree(lpMsgBuf);
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - " + strMessage);
  }

  // loading of GetSchemeInfo
  m_pInfoScheme =
    (lpSchemeInfoReturner) GetProcAddress(m_hLibrary, "GetSchemeInfo_Lib");
  if (m_pInfoScheme == 0)
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function GetSchemeInfo_Lib not found in DLL")

  // loading of m_Image_embed
  m_pEmbed =
    (lpImageEmbedder) GetProcAddress(m_hLibrary, "Embed_Image_Lib");
  if (m_pEmbed == 0)
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function Embed_Image_Lib not found in DLL")

  // loading of m_pExtract
  m_pExtract =
    (lpImageExtractor) GetProcAddress(m_hLibrary, "Extract_Image_Lib");
  if (m_pExtract == 0)
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function Extract_Image_Lib not found in DLL")
#endif // WIN32

#ifdef __UNIX__
  m_hLibrary = dlopen(in_LIBPath, RTLD_LAZY);
  char *error = 0;

  // loading of GetSchemeInfo
  m_pInfoScheme = (lpSchemeInfoReturner)dlsym(m_hLibrary, "GetSchemeInfo_Lib");
  if ((error = dlerror()) != NULL)
  {
    cerr << error << endl;
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function GetSchemeInfo_Lib not found in lib");
  }

  // loading of m_Image_embed
  m_pEmbed = (lpImageEmbedder)dlsym(m_hLibrary, "Embed_Image_Lib");
  if ((error = dlerror()) != NULL)
  {
    cerr << error << endl;
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function Embed_Image_Lib not found in lib");
  }

  // loading of m_pExtract
  m_pExtract = (lpImageExtractor)dlsym(m_hLibrary, "Extract_Image_Lib");
  if ((error = dlerror()) != NULL)
  {
    cerr << error << endl;
    SMBThrowNewException("[CSMBMarkingScheme::SetLibrary] - Function Extract_Image_Lib not found in lib");
  }
#endif // __UNIX__

  GetStringInformation(m_strName, MS_NAME);
  GetStringInformation(m_strAuthor, MS_AUTHOR);
  GetStringInformation(m_strContactAddress, MS_CONTACTADDRESS);
  GetStringInformation(m_strDescription, MS_DESCRIPTION);
  GetStringInformation(m_strReleaseDate, MS_RELEASEDATE);
  GetStringInformation(m_strSourceLocation, MS_SOURCELOCATION);
  GetStringInformation(m_strVersion, MS_VERSION);
  m_uiSchemeFamily = GetNumberInformation(MS_SCHEMEFAMILY);
  m_uiMaxKeySize   = GetNumberInformation(MS_KEYMAXSIZE);
  m_uiMaxMsgSize   = GetNumberInformation(MS_MSGMAXSIZE);

#ifdef _DEBUG
  /*
    the following pointers should be NULL due to the reset call at the 
    begining of the function.
   */
  if (m_parScheme.in_pszKey)
    SMBWarning("[CSMBMarkingScheme::SetLibrary] - m_parScheme.in_pszKey not NULL => memory leak.");

  if (m_parScheme.inout_pszMsg)
    SMBWarning("[CSMBMarkingScheme::SetLibrary] - m_parScheme.inout_pszMsg not NULL => memory leak.");
#endif /* _DEBUG */

  if (m_uiMaxKeySize != 0)
    m_parScheme.in_pszKey     = new char [m_uiMaxKeySize + 1];

  if (m_uiMaxMsgSize != 0)
    m_parScheme.inout_pszMsg  = new char [m_uiMaxMsgSize + 1];

  if (((m_uiMaxMsgSize != 0) && (m_parScheme.inout_pszMsg == NULL)) ||
      ((m_uiMaxKeySize != 0) && (m_parScheme.in_pszKey == NULL)))
  {
    if (m_parScheme.in_pszKey != NULL) delete m_parScheme.in_pszKey;
    if (m_parScheme.inout_pszMsg != NULL) delete m_parScheme.inout_pszMsg;
    inout_exception.Throw(CSMBMemoryException::outOfMemory);
  }

  m_fInitialised = TRUE;
}


void CSMBMarkingScheme::SetKey(TString in_strKey)
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::SetKey] - Watermarking object not initialised properly.");
    return;
  }

  if (m_uiMaxMsgSize != 0)
  {
    assert(m_parScheme.inout_pszMsg != NULL);
    if (in_strKey.length() > m_uiMaxKeySize)
      SMBWarning("[CSMBMarkingScheme::SetKey] - Key too long and will be trunctated to maximum length permited by the scheme.");

    strncpy(m_parScheme.in_pszKey, in_strKey.c_str(), m_uiMaxKeySize);
    m_parScheme.in_nKeyLength = strlen(m_parScheme.in_pszKey);
  }
}


void CSMBMarkingScheme::SetRandomKey(void)
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::SetRandomKey] - Watermarking object not initialised properly.");
    return;
  }

  if (m_uiMaxKeySize != 0)
  {
    assert(m_parScheme.in_pszKey != NULL);
    CSMBRandomNumberGenerator rnd; // TODO: set a good seed for rnd
    for (uint i = 0; i < m_uiMaxKeySize; i++)
      if (rnd.GetDouble() > 0)
        m_parScheme.in_pszKey[i] = '0';
      else
        m_parScheme.in_pszKey[i] = '1';
    m_parScheme.in_pszKey[i] = '\0';
    m_parScheme.in_nKeyLength = m_uiMaxKeySize;
  }
}


void CSMBMarkingScheme::SetRandomMsg(void)
{
  if (!m_fInitialised) {
    SMBWarning("[CSMBMarkingScheme::SetRandomMsg] - Watermarking object not initialised properly.");
    return;
  }

  if (m_uiMaxMsgSize != 0)
  {
    assert(m_parScheme.inout_pszMsg != NULL);
    CSMBRandomNumberGenerator rnd; // TODO: set a good seed for rnd
    for (uint i = 0; i < m_uiMaxMsgSize; i++)
      if (rnd.GetDouble() > 0)
        m_parScheme.inout_pszMsg[i] = '0';
      else
        m_parScheme.inout_pszMsg[i] = '1';
    m_parScheme.inout_pszMsg[i] = '\0';
    m_parScheme.inout_nMsgLength = m_uiMaxMsgSize;

    m_strMsg = m_parScheme.inout_pszMsg;
  }
}


void CSMBMarkingScheme::SetPSNR(float in_fPSNR)
{
  if (in_fPSNR < SMB_DEFAULT_MINIMUM_PSNR)
  {
    m_parScheme.in_dpPSNR = SMB_DEFAULT_MINIMUM_PSNR;
    SMBWarning("[CSMBMarkingScheme::SetPSNR] - PSNR was too law and has be reset to default minimum value.");
    return;
  }

  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::SetPSNR] - Watermarking object not initialised properly.");
    return;
  }

  m_parScheme.in_dpPSNR = in_fPSNR;
}


void CSMBMarkingScheme::SetCertainty(double in_dpCertainty)
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::SetCertainty] - Watermarking object not initialised properly.");
    return;
  }

  if (in_dpCertainty < 0.0)
  {
    m_parScheme.out_dpCertainty = 0.0;
    SMBWarning("[CSMBMarkingScheme::SetCertainty] - dpCertainty cannot be negative and has been reset to 0.");
  }
  else if (in_dpCertainty > 100.0)
  {
    m_parScheme.out_dpCertainty = 100.0;
    SMBWarning("[CSMBMarkingScheme::SetCertainty] - dpCertainty cannot be greater than 100 and has been reset to 100.");
  }
  else
    m_parScheme.out_dpCertainty = in_dpCertainty;
}


void CSMBMarkingScheme::SetStrength(double in_dpStrength)
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::SetStrength] - Watermarking object not initialised properly.");
    return;
  }

  if (in_dpStrength < 0.0)
  {
    m_parScheme.in_dpStrength = 0.0;
    SMBWarning("[CSMBMarkingScheme::SetStrength] - dpStrength cannot be negative and has been reset to 0.");
  }
  else if (in_dpStrength > 100.0)
  {
    m_parScheme.in_dpStrength = 100.0;
    SMBWarning("[CSMBMarkingScheme::SetStrength] - dpStrength cannot be greater than 100 and has been reset to 100.");
  }
  else
    m_parScheme.in_dpStrength = in_dpStrength;
}


double CSMBMarkingScheme::GetResult() const
{
  if (!m_fInitialised)
    SMBWarning("[GetResult] - Watermarking object not initialised properly.");

  return m_dpResult;
}

/*
SMBSchemePars* CSMBMarkingScheme::GetSchemeParamters(void) const 
  throw (CSMBMemoryException *)
{

  SMBSchemePars *out_parScheme = new SMBSchemePars;
  if (out_parScheme == 0) goto Error1;

  out_parScheme->in_pKey    = new char [m_uiMaxKeySize];
  if (out_parScheme->in_pKey == 0) goto Error2;

  out_parScheme->inout_pMsg = new char [m_uiMaxMsgSize];
  if (out_parScheme->inout_pMsg == 0) goto Error3;

  memcpy(out_parScheme->in_pKey, m_parScheme.in_pKey, m_uiMaxKeySize);
  memcpy(out_parScheme->inout_pMsg, m_parScheme.inout_pMsg, m_uiMaxMsgSize);

  out_parScheme->in_dpStrength   = m_parScheme.in_dpStrength;
  out_parScheme->out_dpCertainty = m_parScheme.out_dpCertainty;
  out_parScheme->in_dpPSNR       = m_parScheme.in_dpPSNR;

  return out_parScheme;

Error3:
  delete out_parScheme->in_pKey;
Error2:
  delete out_parScheme;
Error1:
    return NULL;
}
*/


//////////////////////////////////////////////////////////////////////
// Embed/Extract
//////////////////////////////////////////////////////////////////////

ErrorNum CSMBMarkingScheme::EmbedImg(const CSMBImage &  in_imgOriginal,// Original image
                                           CSMBImage & out_imgMarked)  // Watermarked image
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::EmbedImg] - Watermarking object not initialised properly.");
    return SMBFAILURE;
  }

  SMBInformation("  Watermark embedding");

  // Assume that the watermark image has the same
  // caracteristics as the original one (size, colour depth, etc.)
  CSMBMemoryException e;
  try
  {
    out_imgMarked.InitialiseFrom(in_imgOriginal, e);
  }
  catch (CSMBMemoryException *pException)
  {
    pException->PrintMsg();
    return SMBERROR_NOT_ENOUGH_MEMORY;
  }

  // Calls to ExtractImg modify m_parScheme.inout_pszMsg
  // Make sure the correct payload is used
  strncpy(m_parScheme.inout_pszMsg, m_strMsg.c_str(), m_uiMaxMsgSize);

  // TODO: should provide a copy of the image rather than direct access
  // to the structure in the object
#ifdef VERBOSE2
  DumpSchemeParStruct(m_parScheme);
  DumpImageStruct(in_imgOriginal.GetImg());
  DumpImageStruct(out_imgMarked.GetImg());
#endif
  ErrorNum err;
  try
  {
    err = m_pEmbed( in_imgOriginal.GetImg(),
                   out_imgMarked.GetpImg(),
                   & m_parScheme);
  }
  catch (...)
  {
    SMBWarning("[CSMBMarkingScheme::EmbedImg] - The extraction function provided by the library threw an unknown exception.");
    return SMBFAILURE;
  }

  return err;
}


// this is the classical function using SMBSchemePars
ErrorNum CSMBMarkingScheme::ExtractImg(const CSMBImage & in_imgTest,     // Marked/attacked image
                                       const CSMBImage & in_imgOriginal) // (Un)marked original | SMB_NULL_IMAGE
{
  if (!m_fInitialised)
  {
    SMBWarning("[CSMBMarkingScheme::ExtractImg] - Watermarking object not initialised properly.");
    return SMBFAILURE;
  }

  SMBInformation("  Watermark extraction");

  // TODO: should provide a copy of the image rather than direct access
  // to the structure in the object

  // Don't give out the payload to the library
  if (m_uiMaxMsgSize != 0)
    for (uint i = 0; i <= m_uiMaxMsgSize; m_parScheme.inout_pszMsg[i++] = '\0');

  // Try to detect or extract the watermark
  ErrorNum result;
  switch (m_uiSchemeFamily)
  {
  case SF_PRIVATE_1:
  case SF_PRIVATE_2:
      result = m_pExtract(in_imgTest.GetImg(),
                          in_imgOriginal.GetImg(),
                          &m_parScheme);
    break;

  case SF_BLIND_1:
  case SF_BLIND_2:
#ifdef VERBOSE2
    DumpSchemeParStruct(m_parScheme);
    DumpImageStruct(in_imgTest.GetImg());
#endif
    try
    {
      SMBImage imgNull = SMB_NULL_IMAGE;
      result = m_pExtract(in_imgTest.GetImg(), imgNull, &m_parScheme);
    }
    catch (...)
    {
      SMBWarning("[CSMBMarkingScheme::ExtractImg] - The extraction function provided by the library threw an unknown exception.");
      return SMBFAILURE;
    }
    break;

  default:
    return SMBERROR_UNSUPPORTED_SCHEME_FAMILY;
  }
  if (result != SMBSUCCESS) return result;

  // Output de result:
  // - bit error rate for Type 1
  // - certainty for Type 2
  switch (m_uiSchemeFamily)
  {
  case SF_PRIVATE_1:
  case SF_BLIND_1:
    m_dpResult = (double)HammingDistance(m_parScheme.inout_pszMsg,
                                         m_strMsg.c_str(),
                                         min(m_uiMaxMsgSize, m_parScheme.inout_nMsgLength))
                 / (double)m_uiMaxMsgSize;
    break;

  case SF_PRIVATE_2:
  case SF_BLIND_2:
    m_dpResult = m_parScheme.out_dpCertainty;
    break;

  default:
    return SMBERROR_UNSUPPORTED_SCHEME_FAMILY;
  }

  return SMBSUCCESS;
}

//////////////////////////////////////////////////////////////////////
// Information function
//////////////////////////////////////////////////////////////////////
void CSMBMarkingScheme::GetStringInformation(CSMBString &strData, int nInfo)
{
  uint cbData = 0;

  // Find out lenght of information data
  ErrorNum result = m_pInfoScheme(nInfo, 0, &cbData);
  if (result != SMBSUCCESS || cbData == 0)
  {
    SMBWarning("[GetStringInformation] - The library return an unexpted lenght for string information.");
    strData = "";
    return;
  }

  // Get the information data
  STR pbData = new char[cbData];
  result = m_pInfoScheme(nInfo, pbData, &cbData); 
  assert(result == SMBSUCCESS);
  assert(pbData[cbData - 1] == 0);
  if (result != SMBSUCCESS || pbData == 0)
  {
    SMBWarning("[GetStringInformation] - There was an error while retrieving scheme information data from the library.");
    strData = "";
    return;
  }

  strData = (char *)pbData;
  delete [] pbData;
}


uint CSMBMarkingScheme::GetNumberInformation(int nInfo)
{
  uint cData;
  uint cbData = sizeof(cData);

  ErrorNum result = m_pInfoScheme(nInfo, (STR)&cData, &cbData);
  assert(result == SMBSUCCESS);
  if (result != SMBSUCCESS)
  {
    SMBWarning("[GetNumberInformation] - There was an error while retrieving scheme information data from the library.");
    return 0;
  }
  return cData; 
}


//////////////////////////////////////////////////////////////////////

int CSMBMarkingScheme::HammingDistance(CSTR in_pszA,
                                       CSTR in_pszB,
                                       uint in_cch) const
{
  int nDistance;

  nDistance = 0;
  for(uint ich = 0; ich < in_cch; ich++)
  {
    assert(in_pszA[ich] == '0' || in_pszA[ich] == '1');
    assert(in_pszB[ich] == '0' || in_pszB[ich] == '1');
    if (in_pszA[ich] != in_pszB[ich])
      nDistance++;
  }

  return nDistance;
}


//////////////////////////////////////////////////////////////////////
// Log and database functions

void CSMBMarkingScheme::LogInfo(void)
{ 
    TString strUTC;
    SMBGetTimeDate(strUTC);

    m_pbenchInstance->LogMessage("MarkBench - Bench Report - " + strUTC + "\n");
    m_pbenchInstance->LogMessage("MS name            : " + GetName() + " - " + GetVersion());
    m_pbenchInstance->LogMessage("MS release date    : " + GetReleaseDate());
    m_pbenchInstance->LogMessage("MS contact address : " + GetContactAddress());

    m_pbenchInstance->LogMessage("MS source location : " + GetSourceLocation());
    m_pbenchInstance->LogMessage("MS family type     : " + TString((int)GetSchemeFamily()));
    m_pbenchInstance->LogMessage("MS max key size    : " + TString((int)GetMaxKeySize()));
    m_pbenchInstance->LogMessage("MS max msg size    : " + TString((int)GetMaxMsgSize()));

    m_pbenchInstance->LogMessage("\n\n");
}
