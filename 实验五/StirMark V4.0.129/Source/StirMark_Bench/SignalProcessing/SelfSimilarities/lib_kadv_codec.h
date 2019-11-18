/*----------------------------------------------------------------------------
// StirMark Benchmark - defines.h
//
// Contents: Slef similarities attack library functions prototypes
//
// Purpose:  
//
// Created:  C. Rey, G. Doërr, J.-L. Dugelay and G. Csurka, Eurécom, January 2002
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lib_kadv_codec.h,v 1.2 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#ifndef _KADV_CODEC_H_
#define _KADV_CODEC_H_

#include "compil.h"
#include "defines.h"



/* Prototypes associated with lgeom.c */

extern void(*pt_tfgeo[NB_GEOM_TRANS])(block *, int , block *);
void BlockIdent(block *block_in,int dim, block *block_out);
void BlockSymHor(block *block_in,int dim,block *block_out);
void BlockSymVert(block *block_in,int dim,block *block_out);
void BlockSymDiag1(block *block_in,int dim,block *block_out);
void BlockSymDiag2(block *block_in,int dim,block *block_out);

void BlockRot90(block *block_in,int dim,block *block_out);
void BlockRot180(block *block_in,int dim,block *block_out);
void BlockRot270(block *block_in,int dim,block *block_out);

void BlockSubSampling(block *d_block,int dim_d_h, int dim_d_v, int dim_r,block *r_block);
void BlockSubSampling_2(block *d_block,int dim_d,block *r_block);
void BlockSubSampling_4(block *d_block,int dim_d,block *r_block);



/* Prototypes associated with limgtoolkit.c */

short int RoundInt(double);
void ImageCopy(image *,int ,int ,image *);
void ImageNormalize(image *,int ,int );
double PSNR(image*, image*, int, int);
void ExpandLevels(image *, image *, image *, int,int);
void DCT(image* , int , int ,int , coefDct*);
void IDCT(coefDct* ,int ,int ,int ,	image*);
void DCT_Bloc(block* ,int , coefDct* );
void IDCT_Bloc(coefDct* ,int ,	block* );
void lectureZZ(int *, int);



/* Prototypes associated with lblocktoolkit.c */

block *BlockAlloc(int ,int );
void BlockGet(image *,int ,int ,int, int ,block *);
void BlockErrorGet(ERROR_TYPE *,int ,int ,int ,ERROR_TYPE *);
void BlockPut(block *,int ,int ,int ,image *);
void BlockAdd(double *,int ,int ,int ,double *);
void BlockPutMin(block *,block *, int ,int ,int,image *);
void BlockErrorPut(ERROR_TYPE *,int ,int ,int ,ERROR_TYPE*);
void BlockCopy(block *,int ,block *);
void BlockAddCst(block *, int , int );
void BlockErrorPutMin(ERROR_TYPE *,int ,int ,int ,ERROR_TYPE*);
void BlockBlur(block *, int, block *, int);
void BlockMasque(block *, int, double *); 
void BlockAddMasque(double *, int, int, int);
void BlockChoise(block *block_orig, block *block_spa, int dim_r, block *block_dct);
double BlockMean(block *block_in, int dim_r);
double BlockVar(block *block_in, int dim_r, double mean);
int BlockType(block *block_in, int dim_r , double *var);



/* Prototypes associated with lcolor.c */

void ConvertRGB2YUV(image *, image *, image *, image **, image **, image **, int, int);
void ConvertYUV2RGB(image *, image *, image *, image **, image **, image **, int, int);
void ConvertRGB2HSV(image *, image *, image *, image **, image **, image **, int, int);
void ConvertHSV2RGB(image *, image *, image *, image **, image **, image **, int, int);
void ConvertRGB2XYZ(image *, image *, image *, image **, image **, image **, int, int);
void ConvertXYZ2RGB(image *, image *, image *, image **, image **, image **, int, int);
void ConvertXYZ2Lab(image *, image *, image *, image **, image **, image **, int, int);
void ConvertLab2XYZ(image *, image *, image *, image **, image **, image **, int, int);
void ConvertRGB2Lab(image *, image *, image *, image **, image **, image **, int, int);
void ConvertLab2RGB(image *, image *, image *, image **, image **, image **, int, int);



/* Prototypes associated with lcollage_search.c */

char s_o_ss_compute(block *, block *, int, double, double, double, double,
					float *, float *, float *);
void simpleSearchIFS(image* , int, int, image*, image *, float**, long*); 
void collageSearchIFS(image* , int, int, image*, image *, int); 
float super_collage_spa(block *, int, int, int, float, float, image *, int, int, block*, int);
int findAdaptativeThreshold(float*, long, int);



/* Prototypes associates with lwavelet.c */

void haarWaveDecomposition(image*, int, int, image**, image**, image**, image**);
void haarWaveReconstruction(image*, int, int, image*, image*, image*, image*);

#endif /* _KADV_CODEC_H_ */

