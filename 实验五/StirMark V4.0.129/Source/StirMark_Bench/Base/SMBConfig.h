//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBConfig.h
//
// Contents: Default types and constants definitions
//
// Purpose:  This header file is used as a complement to the StirMarkBenchmark.h
//           header file to define the main private settings of the
//           implementation of the StirMark Benchmark evaluation server.
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBConfig.h,v 1.31 2002/04/19 10:23:54 petitcolas Exp $
//////////////////////////////////////////////////////////////////////


#if !defined(_SMBCONFIG_H_)
#define      _SMBCONFIG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SMB_APPLICATION_NAME ("StirMark_Benchmark")
#define SMB_VERSION          ("4.0.129") // Version of StirMark Benchmark

#ifndef PI
#define PI    (3.14159265358979323846)
#endif

#ifndef ONE_MINUS_EPSILON
#define ONE_MINUS_EPSILON   (0.99999999999)
#endif

#define SMB_MAX_DOUBLE (1.5E300)

#ifndef TRUE
#define TRUE    (1)
#endif // TRUE
#ifndef FALSE
#define FALSE   (0)
#endif // FALSE

#ifndef NULL
#define NULL  (0)
#endif

// Result SQL-database parameters
// #define SMB_SQL_IS_ENABLED
#define SMB_SQL_SERVER_NAME   ("")
#define SMB_SQL_LOGIN_NAME    ("SMBTool")
#define SMB_SQL_PASSWORD      ("")
#define SMB_SQL_DATABASE_NAME ("StirMark_Bench")

// Provides more feedback on standard output
//#define VERBOSE
//#define VERBOSE2
//#define VERBOSE3

// When compilig for a simpler application testing compatibility of a library
#define WMKLIB_TESTING

// Default program parameters
#define SMB_DEFAULT_LIBRARY_FOLDER (TCString("../Libraries/"))
#ifdef WIN32
#define SMB_DEFAULT_LIBRARY_FILE   (TCString("EmbedDLL.dll"))
#endif
#ifdef __UNIX__
#define SMB_DEFAULT_LIBRARY_FILE  (TCString("libembed.so"))
#endif 
#define SMB_DEFAULT_REPORT_FILE     (TCString("SMBReport"))
#define SMB_DEFAULT_REPORT_FILE_EXT (TCString(".log"))
#define SMB_DEFAULT_SETTINGS_FOLDER (TCString("../../Profiles/"))
#define SMB_DEFAULT_SETTINGS_FILE   (TCString("SMBSettings.ini"))

// Initialisation file
#define SMB_DEFAULT_IMAGE_FOLDER_SECTION (TCString("ImageFolders")) // [ImageFolders] section
#define SMB_DEFAULT_TEST_LIST_SECTION    (TCString("Tests"))        // [Tests] section
#define SMB_DEFAULT_IMAGE_FOLDER_KEY     (TCString("Folder"))       // Folder1, Folder2, etc.
#define SMB_DEFAULT_TEST_LIST_KEY        (TCString("Test"))         // Test1, Test2, etc.

// Audio-visual signal database
#define SMB_DEFAULT_DATABASE_FOLDER (TCString("../../Media/Input"))  // Root folder where are stored the images
#define SMB_DEFAULT_OUTPUT_FOLDER   (TCString("../../Media/Output")) // Root folder where are stored the attacked images

// Default minimu PSNR after watermarking
// See CSMBMarkingScheme::SetPSNR
#define SMB_DEFAULT_MINIMUM_PSNR       (30)

// Default parameters for marking scheme
#define SMB_DEFAULT_MARKING_STRENGTH   (50)

// Default parameters for streaming support
#define SMB_DEFAULT_AUDIO_BUFFER_SIZE  (4096)

// Defines how to deal with the border of images -see StirMarkBenchmark.h
#define SMB_DEFAULT_BORDER_MODE (BM_CONSTANT)

// Defines the maximum width and height of an image
#define SMB_DEFAULT_MAX_IMAGE_HEIGHT   (10000)
#define SMB_DEFAULT_MAX_IMAGE_WIDTH    (10000)
#define SMB_DEFAULT_MAX_CHANNEL_NUMBER (3) // Maximum number of channels

// Defines how geometric trnasformationa are done
#define SMB_REC_INTERPOLATING_QUADRATIC (1)
#define SMB_REC_LINEAR_INTERPOLATION    (2)
#define SMB_REC_NEAREST_NEIGHBOUR       (3)
#define SMB_SAM_POINT                   (1)
#define SMB_DEFAULT_REC                 (SMB_REC_INTERPOLATING_QUADRATIC)
#define SMB_DEFAULT_SAM                 (SMB_SAM_POINT)

// Other default settings
#define SMB_DEFAULT_SAMPLE_IMAGE_1       (TCString("/Images/Set1/Sample.ppm"))
#define SMB_DEFAULT_SAMPLE_IMAGE_2       (TCString("/Images/Set1/Sample_ASCII.ppm"))
#define SMB_DEFAULT_SAMPLE_IMAGE_3       (TCString("/Images/Set1/Lena.bmp"))
#define SMB_DEFAULT_IMAGE_NAME           (TCString("NONAME"))
#define SMB_DEFAULT_IMAGE_FILE_EXTENSION (TCString(".bmp"))
#define SMB_DEFAULT_IMAGE_FORMAT         (TCString("BMP"))

// Define how are saved the random distortion maps
#ifdef VERBOSE
#define SMB_DEFAULT_MAP_IMAGE_FORMAT   (TCString("BMP"))
#define SMB_DEFAULT_MAPX_IMAGE         (TCString("RndMapX"))
#define SMB_DEFAULT_MAPY_IMAGE         (TCString("RndMapY"))
#endif // VERBOSE

// Default reconstructor and resampler for geometric transformation
// tests are defined in SMBTestGT.cpp

// Output format
#define SMB_DISP_TEST_SEPARATOR (TCString("---------------------------------------------------"))

#define SMB_LOG_TEST_SEPARATOR  (TCString("---------------------------------------------------\n"))
#define SMB_LOG_SEPARATOR       (TCString("\t"))

#endif // !defined(_SMBCONFIG_H_)
