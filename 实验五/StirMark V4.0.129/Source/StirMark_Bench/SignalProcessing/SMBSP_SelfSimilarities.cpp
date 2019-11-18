//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBSP_SelfSimilarities.cpp
//
// Contents: Implementation of the CSMBS_SelfSimilarities class.
//
// Purpose:  See SMBSP_SelfSimilarities.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 1 April 2002
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SMBSP_SelfSimilarities.cpp,v 1.7 2002/04/19 10:23:58 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <stdio.h>
#include <assert.h>
#ifdef WIN32
#include <io.h>
#define unlink _unlink
#define fileno _fileno
#define dup _dup
#define dup2 _dup2
#endif
#ifdef __UNIX__
#include <unistd.h>
#endif


// SMB headers
#include "SMBSP_SelfSimilarities.h"
#include "../Base/SMBError.h"
#include "../Base/SMBMemoryException.h"
#include "../Base/SMBImage.h"
#include "../Base/SMBConfig.h"



//////////////////////////////////////////////////////////////////////
// Redirection of stderr and stdout which are used by the
// self similarities library so the output does not interfere
// with the one of StirMark Benchmark
//////////////////////////////////////////////////////////////////////

#if !defined(VERBOSE3)
#define SMB_NEW_OUT_NAME ("SMBTmpOut.log")

static Bool   isRedirected = FALSE;

static FILE * new_stdout;
static int    old_stdout_no;
#endif // !defined(VERBOSE3)

static void _RedirectStdStreams(void)
{
#if !defined(VERBOSE3)
  if (isRedirected == FALSE)
  {
    // Save handle to stdout
    old_stdout_no = dup(1);
    if (old_stdout_no == -1)
      SMBFatalError("[_RedirectStdStreams] - dup(1) failure. Fatal error. Exit.");

    // Create temporary file
    new_stdout = fopen(SMB_NEW_OUT_NAME, "w");
    if (new_stdout == NULL)
    {
      SMBWarning("[_RedirectStdStreams] - Could not create file for redirection of stdout.");
      return;
    }

    // Redirect stdout
    if (dup2(fileno(new_stdout), 1) == -1)
    {
      SMBWarning("[_RedirectStdStreams] - Could not redirect stdout.");
      return;
    }

    isRedirected = TRUE;
  }
#endif // !defined(VERBOSE3)
}

static void _RestoreStdStreams(void)
{
#if !defined(VERBOSE3)
  if (isRedirected)
  {
    fflush(stdout);
    fclose(new_stdout);

    // Restore original stdout
    if (dup2(old_stdout_no, 1) == -1)
      SMBFatalError("[_RedirectStdStreams] - Could not restore stdout. Fatal Error. Exit.");

    // Delete temporary file
    unlink(SMB_NEW_OUT_NAME);

    isRedirected = FALSE;
  }
#endif // !defined(VERBOSE3)
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBSP_SelfSimilarities::CSMBSP_SelfSimilarities()
: m_nColourSpace(SS_RGB),
  m_nPercent(60),
  m_nAttack(SS_SPATIAL)
{
  m_rgfC[0] = SS_ATTACK;
  m_rgfC[1] = SS_NO_ATTACK;
  m_rgfC[2] = SS_NO_ATTACK;
}


CSMBSP_SelfSimilarities::~CSMBSP_SelfSimilarities()
{

}



//////////////////////////////////////////////////////////////////////

void CSMBSP_SelfSimilarities::SetParameter(const optionsCmd in_option)
{
  if (in_option.colorSpace != SS_RGB &&
      in_option.colorSpace != SS_YUV &&
      in_option.colorSpace != SS_HSV &&
      in_option.colorSpace != SS_LAB &&
      in_option.colorSpace != SS_XYZ)
  {
    SMBWarning("[CSMBSP_SelfSimilarities::SetParameter] - Invalid colour space.");
    return;
  }

  if (in_option.c1_flag != SS_NO_ATTACK &&
      in_option.c1_flag != SS_ATTACK    &&
      in_option.c2_flag != SS_NO_ATTACK &&
      in_option.c2_flag != SS_ATTACK    &&
      in_option.c3_flag != SS_NO_ATTACK &&
      in_option.c3_flag != SS_ATTACK    &&
      in_option.type    != SS_SWITCH    &&
      in_option.type    != SS_SPATIAL   &&
      in_option.type    != SS_SWITCH)
  {
    SMBWarning("[CSMBSP_SelfSimilarities::SetParameter] - Invalid attack type.");
    return;
  }

  if (in_option.type != SS_SWITCH)
  {
    if (in_option.percent > 100 || in_option.percent < 0)
    {
      SMBWarning("[CSMBSP_SelfSimilarities::SetParameter] - Invalid attack type.");
      return;
    }
  }

  // All tests passed

  m_rgfC[0] = in_option.c1_flag;
  m_rgfC[1] = in_option.c2_flag;
  m_rgfC[2] = in_option.c3_flag;
  m_nAttack = in_option.type;
  m_nColourSpace = in_option.colorSpace;
  m_nPercent     = in_option.percent;
}



//////////////////////////////////////////////////////////////////////
// Image format conversion function
//////////////////////////////////////////////////////////////////////

ErrorNum CSMBSP_SelfSimilarities::SMBConvertImageFormat(const CSMBImage & in_imgSource,
                                                        SSImage **       out_prgC1,
                                                        SSImage **       out_prgC2,
                                                        SSImage **       out_prgC3,
                                                        uint              in_nColourSpace)
{
  *out_prgC1 = *out_prgC2 = *out_prgC3 = NULL;

  if (in_imgSource.NumberOfChannels() != 3)
    return SMBWarning("[CSMBSP_SelfSimilarities::SMBConvertImageFormat] - "
                      "Input image does not have three channels.",
                      SMBERROR_UNEXPECTED_PARAMETER);

  // Memory allocation for the three channels
  uint nBytes  =   in_imgSource.NumberOfColumns()
                 * in_imgSource.NumberOfRows()
                 * sizeof(SSImage);

  SSImage * R = NULL; R = new SSImage[nBytes];
  SSImage * G = NULL; G = new SSImage[nBytes];
  SSImage * B = NULL; B = new SSImage[nBytes];
  
  if (R == NULL || G == NULL || B == NULL)
  {
    delete R;
    delete G;
    delete B;
    *out_prgC1 = *out_prgC2 = *out_prgC3 = NULL;
    return SMBERROR_NOT_ENOUGH_MEMORY;
  }

  // Copy data
  SSImage *p1 = R;
  SSImage *p2 = G;
  SSImage *p3 = B;

  for (uint y = 0; y < in_imgSource.NumberOfRows(); y++)
    for (uint x = 0; x < in_imgSource.NumberOfColumns(); x++)
    {
      *p1++ = (SSImage) in_imgSource(x, y, 0);
      *p2++ = (SSImage) in_imgSource(x, y, 1);
      *p3++ = (SSImage) in_imgSource(x, y, 2);
    }
  _RedirectStdStreams();
  /*ExpandLevels(R, G, B,
               in_imgSource.NumberOfColumns() * in_imgSource.NumberOfRows(),
               in_imgSource.GetMaxVal());*/

  // Change colour space
  // TODO: convertRGB2Channel allocates memory...
  convertRGB2Channel(R, G, B,
                     out_prgC1, out_prgC2, out_prgC3,
                     in_imgSource.NumberOfColumns(), in_imgSource.NumberOfRows(), in_nColourSpace);
  _RestoreStdStreams();
  delete R;
  delete G;
  delete B;

  return SMBSUCCESS;
}


ErrorNum CSMBSP_SelfSimilarities::SMBConvertImageFormat(SSImage *      in_rgC1,
                                                        SSImage *      in_rgC2,
                                                        SSImage *      in_rgC3,
                                                        uint           in_nCols,
                                                        uint           in_nRows,
                                                        uint           in_nColourSpace,
                                                        CSMBImage & inout_imgTarget)
{
  if (in_rgC1 == NULL || in_rgC2 == NULL || in_rgC3 == NULL)
    return SMBWarning("[CSMBSP_SelfSimilarities::SMBConvertImageFormat] - "
                      "One ofthe input input channels is not valid.",
                      SMBERROR_INVALID_PARAMETER);

  // Memory allocation for temporary RGB channels
  // uint nBytes  =   in_nCols * in_nRows * sizeof(SSImage);

  SSImage * R = NULL;
  SSImage * G = NULL;
  SSImage * B = NULL;
  
  // Create new RGB image
  _RedirectStdStreams();
  convertChannel2RGB(in_rgC1, in_rgC2, in_rgC3,
                     &R, &G, &B, in_nCols, in_nRows, in_nColourSpace);
  _RestoreStdStreams();
 
  // No need to initialise inout_imgTarget as it is initialised by the
  // caller of the operator() function

  // Copy data
  SSImage *p1 = R;
  SSImage *p2 = G;
  SSImage *p3 = B;

  for (uint y = 0; y < in_nRows; y++)
  {
    for (uint x = 0; x < in_nCols; x++)
    {
      inout_imgTarget.SetPixel(x, y, 0, (*p1 > 255) ? 255 : ((*p1 < 0) ? 0 : (Gray)*p1));
      inout_imgTarget.SetPixel(x, y, 1, (*p2 > 255) ? 255 : ((*p2 < 0) ? 0 : (Gray)*p2));
      inout_imgTarget.SetPixel(x, y, 2, (*p3 > 255) ? 255 : ((*p3 < 0) ? 0 : (Gray)*p3));
      p1++;
      p2++;
      p3++;
    }
  }

  delete R;
  delete G;
  delete B;

  return SMBSUCCESS;
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

ErrorNum CSMBSP_SelfSimilarities::operator()(const CSMBImage  &in_imgWatermarked,
                                                   CSMBImage &out_imgAttacked)
{
  int i;
  long width  = in_imgWatermarked.NumberOfColumns();
  long height = in_imgWatermarked.NumberOfRows();
  uint nBytes = in_imgWatermarked.NumberOfColumns() * in_imgWatermarked.NumberOfRows() * sizeof(SSImage);

  SSImage *channel_water[3];
  SSImage *channel_sup[3];
  for (i = 0; i < 3; i++)
    channel_water[i] = channel_sup[i] = NULL;

  if ((SMBConvertImageFormat(in_imgWatermarked,
                             &channel_water[0],
                             &channel_water[1],
                             &channel_water[2],
                             m_nColourSpace) != SMBSUCCESS))
    goto CSMBSP_SelfSimilaritiesError;

    // TODO: Remove: WritePPM("SMB_TEST_DEBUG.ppm", width, height, 255, channel_water[0], channel_water[1], channel_water[2]);

#ifdef _DEBUG
  for (i = 0; i < 3; i++)
    assert(channel_water[i] != NULL);
#endif // _DEBUG

  // Set the attack parameters to be passed to the library functions
  optionsCmd commandLine;
  commandLine.colorSpace = m_nColourSpace;
  commandLine.c1_flag    = m_rgfC[0];
	commandLine.c2_flag    = m_rgfC[1];
	commandLine.c3_flag    = m_rgfC[2];
  commandLine.type       = m_nAttack;
  commandLine.percent    = m_nPercent;
  
  for (i = 0; i < 3; i++)
  {
    channel_sup[i] = new SSImage[nBytes];
    if (channel_sup[i] == NULL)
      goto CSMBSP_SelfSimilaritiesError;

    if (m_rgfC[i])
    {
      // The watermarked image is used both for the IFS book and as
      // image to be attacked
      _RedirectStdStreams();
      attackChannel(channel_water[i], channel_water[i], channel_sup[i], width, height, &commandLine);
      /*for (uint n = 0; n < width * height; n++)
        channel_sup[i][n] = channel_water[i][n] + 30 * (double)(rand() - RAND_MAX / 2) / (double)RAND_MAX;*/
      _RestoreStdStreams();
    }
    else
    {
      delete channel_sup[i];
      channel_sup[i]   = channel_water[i];
      channel_water[i] = NULL;
    }
  }

  SMBConvertImageFormat(channel_sup[0], channel_sup[1], channel_sup[2],
                        width, height, m_nColourSpace,
                        out_imgAttacked);
  
  for (i = 0; i < 3; i++)
  {
    delete channel_water[i]; channel_water[i] = NULL;
    delete channel_sup[i];   channel_sup[i]   = NULL;
  }

  return SMBSUCCESS;

CSMBSP_SelfSimilaritiesError:
  for (i = 0; i < 3; i++)
  {
    delete channel_water[i]; channel_water[i] = NULL;
    delete channel_sup[i];   channel_sup[i]   = NULL;
  }

  return SMBWarning("[CSMBSP_SelfSimilarities::operator()] - Attack failed.");
}


//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#define MY_FILE "tmp.err"

int SMBSP_SelfSimilarities_Test()
{
  CSMBImage img;
  CSMBException e;

  cout << " stdout redirection test" << endl;

  cout << "   this is not redirected" << endl;
  _RedirectStdStreams();
  cout << "   this should be redirected in " << SMB_NEW_OUT_NAME << endl;
  _RestoreStdStreams();
  cout << "   this is not redirected" << endl;
  cout.flush();

  return 0;

  cout << "  Reading image " << SMB_DEFAULT_SAMPLE_IMAGE_3 << endl;
  try
  {
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_3);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
    delete pException;
    return SMBFAILURE;
  }

  CSMBSP_SelfSimilarities attack;
  CSMBImage imgAttacked;
  attack(img, imgAttacked);
  
  try
  {
    imgAttacked.Save(SMB_DEFAULT_OUTPUT_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_3, SMB_DEFAULT_IMAGE_FORMAT);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
    delete pException;
    return SMBFAILURE;
  }

  return SMBSUCCESS;
}

#endif // SMB_CODE_TESTING
