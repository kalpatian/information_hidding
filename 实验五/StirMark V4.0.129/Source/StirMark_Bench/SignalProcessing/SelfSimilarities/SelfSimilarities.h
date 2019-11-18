/*----------------------------------------------------------------------------
// StirMark Benchmark - SelfSimilarities.h
//
// Contents: Interface to the SelfSimilarities attack library.
//
// Purpose:  This contains the definitions which are necessary to use
//           the SelSimilarities library.
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 29 March 2002
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/SelfSimilarities.h,v 1.3 2002/04/19 10:23:58 petitcolas Exp $
//----------------------------------------------------------------------------
*/

#if !defined(_SELFSIMILARITIES_H_)
#define      _SELFSIMILARITIES_H_

/* Colour spaces in which the self similarities attack can be performed */
#define SS_RGB (0)
#define SS_YUV (1)
#define SS_HSV (2)
#define SS_LAB (3)
#define	SS_XYZ	(4)

/* Flag used to indicate in which channel(s) the attack is done */
#define SS_NO_ATTACK (0)
#define SS_ATTACK    (1)

/* Types of attack */
#define SS_SWITCH  (0)
#define SS_SPATIAL (1)
#define SS_WAVELET (2)

typedef short int SSImage;

typedef struct
{
#if defined (SS_EXE)
  char* origFile;   /* Image file providing the IFS codebook       */
  char*	waterFile;  /* Image to be watermarked                     */
#endif /* !defined (SS_EXE) */
  int		colorSpace; /* Used colorspace                             */
  int		c1_flag;    /* Flag for channel 1                          */
  int		c2_flag;    /* Flag for channel 2                          */
  int		c3_flag;    /* Flag for channel 3                          */
  int		percent;    /* Percentage used for adaptative thresholding */
  int		type;       /* Type of attack                              */
} optionsCmd;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void convertRGB2Channel(SSImage *R, SSImage *G, SSImage *B,                         /* Input RGB channels */
                        SSImage **channel1,	SSImage **channel2,	SSImage **channel3, /* Output channels    */
                        int width, int height, int color_space);

void convertChannel2RGB(SSImage *channel1, SSImage *channel2, SSImage *channel3, /* Input channels      */
                        SSImage **R, SSImage **G, SSImage **B,                   /* Output RGB channels */
                        int width, int height, int color_space);

void ExpandLevels(SSImage *R, SSImage *G, SSImage *B, int size,int maxRGB);

void attackChannel(SSImage *orig, SSImage *water,           /* Input images   */
                   SSImage *sup,                            /* Attacked image */
				           int width, int height, optionsCmd *cmd);


int WritePPM ( char *fileout_name, int xsize, int ysize, int maxrgb,
        SSImage *rarray, SSImage *garray, SSImage *barray ) ;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined(_SELFSIMILARITIES_H_) */

