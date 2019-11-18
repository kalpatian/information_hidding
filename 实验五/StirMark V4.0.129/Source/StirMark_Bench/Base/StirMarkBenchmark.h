/*----------------------------------------------------------------------------
// StirMark Benchmark - StirMarkBenchmark.h
//
// Contents: The main header file of the StirMark Benchmark project
//
// Purpose:  This header file will be exported to watermarking providers.
//           It basically defines the interface between the StirMark server
//           and the marking scheme libraries.
//
//           Watermarking providers need only present 3 functions. Their
//           prototype is at the end of this header file:
//           - GetSchemeInfo
//           - Embed_Image_Lib
//           - Extract_Image_Lib
//
//           Support for other media will be added in the near future.
//
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research
//           Frédéric Raynal, INRIA
//           Matthieu Brunet, INRIA, 7 March 2000
//
// Modified: Nazim Fatès, Microsoft Research
//           Fabien A. P. Petitcolas, 6 April 2002
//
// History:  7 March 2000 - Created after meeting at INRIA Rocquencourt.
//           The general functional interface was defined.
//
//           6 April 2002 - Using bits for message length and key length
//           is better. Feedback from Cheryl Cramer (Digimarc) helped to
//           clarify documentation.
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/StirMarkBenchmark.h,v 1.22 2002/04/19 10:23:55 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/

#if !defined(_STIRMARKBENCHMARK_H_)
#define      _STIRMARKBENCHMARK_H_

#if !defined(WIN32)
#if !defined(__UNIX__)
#define __UNIX__
#endif
#endif

#if _MSC_VER > 1000
#pragma once
#endif /* _MSC_VER > 1000 */



/* Return code for Embed and Extract procedures */
#define SMBFAILURE  (-1)
#define SMBSUCCESS   (0) /* this code only means that   */
                         /* the operation went through  */
#define SMBERROR_KEY_TOO_LARGE             (1L)
#define SMBERROR_UNSUPPORTED_KEY           (2L)
#define SMBERROR_MSG_TOO_LARGE             (3L)
#define SMBERROR_UNSUPPORTED_MSG           (4L)
#define SMBERROR_BAD_FORMAT_IMAGE          (5L)
#define SMBERROR_UNSUPPORTED_IMAGE_SIZE    (6L)
#define SMBERROR_UNSUPPORTED_STRENGTH      (7L)
#define SMBERROR_NOT_ENOUGH_MEMORY         (8L)
#define SMBERROR_UNEXPECTED_PARAMETER      (9L)
#define SMBERROR_MORE_DATA_AVAILABLE       (10L)
#define SMBERROR_UNSUPPORTED_SCHEME_FAMILY (11L)
#define SMBERROR_INVALID_PARAMETER         (12L)


/* Basic type definitions */
typedef long ErrorNum;      /* See beginning of this file                    */
typedef char *  STR;        /* Character string                              */
typedef const char *  CSTR; /* Constant character string                     */
typedef unsigned char Gray; /* Grayscale value of a pixel in colour  plane   */
typedef unsigned int  uint;



/*----------------------------------------------------------------------------
// Image support
*/


/* Coding types for pixels in an image */
enum ImageType
{
  IT_GRAY = 0, /* 1 channel  - grayscale image           */
  IT_RGB,      /* 3 channels - standard RGB colour image */
  IT_LAST_INDEX
};


/* Many image processing functions need intensity values for pixels
// that lie outside the image. The following options can be used
// to specify how border pixels are handled.
*/
enum BorderMode
{
  BM_CONSTANT =0, /* A constant value is used for the border              */
  BM_REPLICATION, /* The last row or column is replicated for the border  */
  BM_REFLECTION,  /* The last row or column is reflected in reverse order */
  BM_WARPING,     /* The row or column of the opposite side is used       */
  BM_LAST_INDEX
};


/* Image information structure */
typedef struct
{

  uint   nChannels; /* Number of colour channels, e.g. 1 for IT_GRAY */
  Gray   gMaxVal;   /* Maximum pixel component value                 */
  uint   nCols;     /* Number of columns (width)                     */
  uint   nRows;     /* Number of rows (height)                       */
  Gray   gBrdValue; /* Constant value used for border if BM_CONSTANT */
  Gray * pgData;    /* Pointer to the grayscale value of all pixels  */
                    /* from top left pixel to bottom right pixel.    */
                    /* For RGB images it is assumed that, for each   */
                    /* pixel the values are  given in the following  */
                    /* order: R, G then B. So one have:              */
                    /* R1 G1 B1 R2 G2 B2 R3 G3 B3 ...                */
  uint   lSize;     /* Size (byte) of the allocated pgData buffer    */

  enum BorderMode bmMode;    /* Border handling mode                          */
  enum ImageType  itType;
} SMBImage;


#define SMB_NULL_IMAGE  {1, 255, 0, 0, 0, NULL, 0, BM_CONSTANT, IT_GRAY}



/*----------------------------------------------------------------------------
// Families of watermarking schemes
*/
#define SF_PRIVATE_1   (1) /* Non-blind type I   */
#define SF_PRIVATE_2   (2) /* Non-blind type II  */
#define SF_BLIND_1     (5) /* Blind type I       */
#define SF_BLIND_2     (6) /* Blind type II      */
/* #define SF_SEMIBLIND_1 (3) */ /* Semi-blind type I  */
/* #define SF_SEMIBLIND_2 (4) */ /* Semi-blind type II */

/*
// - Type I scheme: the output of the extractor is either the payload or
//   a symbol meaning the absence of mark in the signal to be tested;
// - Type II scheme: such schemes require knowledge of the embedded
//   watermark for detection in a signal. Such schemes are only able to
//   tell whether a given watermark is present or not;
// - Non-blind (private) scheme: the original non-watermarked
//   audio-visual signal, the watermarking key and the signal to be
//   tested are required for the detection;
// - Semi-blind scheme: the published watermarked audio-visual signal,
//   the watermarking key and the signal to be tested are required for
//   the detection;
// - Blind (public) scheme: only the watermarking-key and the signal to
//   be tested are required for the detection;



// Evaluation profile
//
// Evaluation profiles depends on the application. One can think of them
// as set of requirements. Right now it can only be specified via the
// command line (.ini file)
*/
enum EvaluationProfile
{
  /* TODO: we are working on this */
};


/* Assurance level
//
// This describes how thoroughly the evaluation is done
// how well the requirement are followed. This is not supported yet.
*/
enum AssuranceLevel
{
  /* TODO: we are working on this */
};



/*----------------------------------------------------------------------------
// Watermarking scheme parameters for embedding or extraction function
//
// See SMBMarkingScheme.cpp and SMBMarkingScheme.h for greater details
// about how the following definitions are used.
*/

typedef struct SMBSchemeParsTag
{
  double    in_dpStrength;  /* Strength for embedding/extraction   */
  STR       in_pszKey;      /* Key for extraction OR for Embedding */
  uint      in_nKeyLength;  /* Length of the key in bits           */
  STR    inout_pszMsg;      /* Message extracted OR to embed       */
  uint   inout_nMsgLength;  /* Length of the message in bits       */
  double    in_dpPSNR;      /* Minimal wished PSNR of output       */
  double   out_dpCertainty; /* Certainty of extraction             */
} SMBSchemePars;

/* in_pszKey is always provided by the calling function. It is a pointer to a
// null terminated string of '0' and '1' characters representing the binary
// watermarking key. The size in bytes of the block of memory allocated for
// this string is 1 plus the value provided by GetSchemeInfo_Lib when using the
// MS_KEYMAXSIZE selector. The extra byte is used for NULL terminating
// character of the string. The actual character-length of the string is
// in_nKeyLength. This excludes the terminal NULL. So in practice, a simplified
// version of a calling function that passes this structure to an embedding
// or extracting function may look like:
//
//   uint cMaxKeyLength;
//   uint cbcMaxKeyLength = sizeof(cMaxKeyLength);
//
//   GetSchemeInfo_Lib(MS_KEYMAXSIZE,
//                     (unsigned char *) & cMaxKeyLength,
//                     & cbcMaxKeyLength);
//
//   strncpy(in_pszKey, "001011", cMaxKeyLength);
//   in_nKeyLength = strlen(in_pszKey);
//
//
// inout_pszMsg is similar to in_pszKey but is use to pass or get the embedded
// message. The memory block to which it points is always allocated by the
// function which declared the structure, to typically StirMark Benchmark and
// not the watermarking library. The size in bytes of the memory allocated by
// the caller for this string is 1 plus the value provided by GetSchemeInfo_Lib
// when using the MS_MSGMAXSIZE selector. The extra byte is used for the NULL
// terminating character of the string. The actual length of the string is
// inout_nMsgLength. This excludes the terminal NULL. The string is either
// empty (typically for Type II schemes, in which case inout_nMsgLength is 0)
// or contains '0' and '1' characters representing the binary message that
// should be embedded or that was extracted.
//
// in_dpStrength is used to specify the embedding strength and is assumed to
// have the following properties:
// - in_dpStrength is a double precision number between 0.0 and 100.0;
// - the higher the value of in_dpStrength, the lower the quality of the
//   output image and the higher (hopefully) the 'robustness';
// - in_dpStrength = 0.0 corresponds to no watermarking (PSNR -> infinity);
// - in_dpStrength = 100.0 should correspond to a watermarked picture with
//   PSNR around 20 dB;
// - the distribution in_dpStrength should be 'harmonious'.
// - if in_dpStrength is set to -1 dpPSNR is used to adjust the strength of
//   the embedding
// So the expected PSNR is around 60 - 20 * log10(in_dpStrength);
//
// out_dpCertainty is used for extraction only. It's the probability (double
// precision number between 0.0 and 100.0) that the extracted information is
// correct. Mainly used by Type II schemes.
//
// in_dpPSNR is used for embedding when dpStrength is set to -1. in_dpPSNR is
// specified by the caller. It takes a PSNR value in dB and indicates to
// the embedder that it should use the best strength such that the PSNR
// of the output image is greater or equal to in_dpPSNR.
*/



/*----------------------------------------------------------------------------
// Headers of the functions exported by the library under test
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*----------------------------------------------------------------------------
// Information about the watermarking scheme implemented in the library
*/
#ifdef DLLEXPORT
DLLEXPORT
#endif /* DLLEXPORT */
ErrorNum GetSchemeInfo_Lib(uint      in_nInfo,
                           STR      out_pbData,
                           uint * inout_pcbData);

/* in_nInfo governs the nature of the query: */
#define MS_NAME           (1)  /* Name of the marking scheme                 */
#define MS_VERSION        (2)  /* Version of the scheme                      */  
#define MS_AUTHOR         (3)  /* Author(s), research group or company       */
#define MS_RELEASEDATE    (4)  /* Release date of the current version        */
#define MS_DESCRIPTION    (5)  /* Notes and comments regarding the scheme    */
#define MS_SOURCELOCATION (6)  /* URL of the sources                         */
#define MS_CONTACTADDRESS (7)  /* Email of the contact                       */
#define MS_MSGMAXSIZE     (8)  /* Maximum bit-length of the embedded message */
#define MS_KEYMAXSIZE     (9)  /* Maximum bit-length of the stego-key        */
#define MS_SCHEMEFAMILY   (10) /* Family of the watermarking scheme          */

/* pbData is a pointer to the location where the data will be returned,
// and pcbData is the size, in bytes, of the returned data. If the buffer
// specified by pbData parameter is not large enough to hold the returned
// data, the function returns SMBERROR_MORE_DATA_AVAILABLE and stores the
// required buffer size, in byte, into the variable pointed to by pcbData.
// If NULL is input for pbData and pcbData is non-NULL, no error is
// returned and the function returns the size of the needed memory buffer,
// in bytes, in the variable pointed to by pcbData.
// This lets the caller determine the size of, and the best way to
// allocate, a buffer for the returned data.
//
// For MS_MSGMAXSIZE, MS_KEYMAXSIZE and MS_SCHEMEFAMILY pcbData is casted
// to (uint) and *inout_pcbData = sizeof(uint). Schemes that do not allow
// the embedding of a payload should return 0 to the MS_MSGMAXSIZE query.
// Similarly, schemes that do not allowed the use of keys should return 0
// to the MS_KEYMAXSIZE query.
//
// Return value: SMBSUCCESS, SMBERROR_MORE_DATA_AVAILABLE or
//               SMBERROR_UNEXPECTED_PARAMETER
*/



/*----------------------------------------------------------------------------
// Embedding and extraction functions
//
// In our implementation we assumed that the module which allocates memory
// also releases the memory. Consequently out_pimgTarget is a pointer to
// an SMBImage structure which has already been initialised. In particular
// the pgData blob has been allocated but contains random data (not
// necessarily a copy of the original image). in_imgOriginal and out_pimgTarget
// images are assumed to have the same size. However the in_imgTest image
// may have a different size. Embedding will be done with payload and keys
// of maximal length (the ones provided by GetSchemeInfo_Lib).
*/

#ifdef DLLEXPORT
DLLEXPORT
#endif /* DLLEXPORT */
ErrorNum Embed_Image_Lib(
         const SMBImage        in_imgOriginal, /* Original image     */
               SMBImage *     out_pimgTarget,  /* Image  to mark     */
         const SMBSchemePars * in_pPars        /* Pars for embedding */
         );

#ifdef DLLEXPORT
DLLEXPORT
#endif /* DLLEXPORT */
ErrorNum Extract_Image_Lib(
         const SMBImage     in_imgTest,     /* Marked/attacked image        */
         const SMBImage     in_imgOriginal, /* Marked/unmarked image        */
                                            /* OR  SMB_NULL_IMAGE           */
         SMBSchemePars * inout_pPars        /* Pars for extraction & output */
         );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined(_STIRMARKBENCHMARK_H_) */

 

