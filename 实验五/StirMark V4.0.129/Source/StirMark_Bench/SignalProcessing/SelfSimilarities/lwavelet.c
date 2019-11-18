/*----------------------------------------------------------------------------
// StirMark Benchmark - lwavelet.c
//
// Contents: Haar wavelet decomposition and reconstruction functions
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lwavelet.c,v 1.2 2002/04/19 10:23:59 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


/* Haar wavelet decomposition */
void haarWaveDecomposition(image *spa, int width, int height, image **h00,
						   image **h01, image **h10, image **h11){
	int i, j;
	int pad_width = width;        /* Width of the image after padding           */
	int pad_height = height;      /* Height of the image after padding          */
	image *pad_spa;               /* Padded image                               */
	int w_width, w_height;        /* Dimension of a wavelet                     */
	image *a, *d;                 /* Temporary pointers for wavelet computation */

	/* Image padding (even dimensions) */
	if (width%2 == 1)
		pad_width++;
	if (height%2 == 1)
		pad_height++;
	if((pad_spa = (image *)malloc(sizeof(image) * pad_width * pad_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	for (j=0; j<pad_height; j++){
		for (i=0; i<pad_width; i++){
			if (i<width && j<height)
				pad_spa[i+j*pad_width]=spa[i+j*width];
			else { 
				if (i>=width && j<height)
					pad_spa[i+j*pad_width]=spa[2*width-i-1+j*width];
				else if (i<width && j>=height)
					pad_spa[i+j*pad_width]=spa[i+(2*height-j-1)*width];
				else if (i>=width && j>=height)
					pad_spa[i+j*pad_width]=spa[2*width-i-1+(2*height-j-1)*width];
			}
		}
	}


	/* Memory allocation for wavelets */
	w_width = pad_width / 2;
	w_height = pad_height / 2;
	if((a = (image *)malloc(sizeof(image) * w_width * pad_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	if((d = (image *)malloc(sizeof(image) * w_width * pad_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	if((*h00 = (image *)malloc(sizeof(image) * w_width * w_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	if((*h01 = (image *)malloc(sizeof(image) * w_width * w_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	if((*h10 = (image *)malloc(sizeof(image) * w_width * w_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	if((*h11 = (image *)malloc(sizeof(image) * w_width * w_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}


	/* Horizontal wavelets decomposition */
	for (j=0;j<pad_height;j++){
		for (i=0;i<w_width;i++){
			a[i+j*w_width] = pad_spa[2*i + j*pad_width]
				             + pad_spa[2*i+1 + j*pad_width];
			d[i+j*w_width] = pad_spa[2*i + j*pad_width]
				             - pad_spa[2*i+1 + j*pad_width];
		}
	}

	/* Vertical wavelets decomposition */
	for (i=0;i<w_width;i++){
		for(j=0;j<w_height;j++){
			(*h00)[i+j*w_width] = (image)( (a[i + 2*j*w_width]
				                          + a[i + (2*j+1)*w_width]) / 2 );
			(*h01)[i+j*w_width] = (image)( (d[i + 2*j*w_width]
				                          + d[i + (2*j+1)*w_width]) / 2 );
			(*h10)[i+j*w_width] = (image)( (a[i + 2*j*w_width]
				                          - a[i + (2*j+1)*w_width]) / 2 );
			(*h11)[i+j*w_width] = (image)( (d[i + 2*j*w_width]
				                          - d[i + (2*j+1)*w_width]) / 2 );
		}
	}

	/* Free memory */
	free(a);free(d);
	free(pad_spa);
}




void haarWaveReconstruction(image *spa, int width, int height, image *h00,
							image *h01, image *h10, image *h11){
	int i, j;
	int pad_width = width;        /* Width of the image after padding  */
	int pad_height = height;      /* Height of the image after padding */
	image *pad_spa;               /* Padded image                      */
	int w_width, w_height;        /* Dimension of a wavelet            */

	/* Image padding (even dimentsions) */
	if (width%2 == 1)
		pad_width++;
	if (height%2 == 1)
		pad_height++;
	if((pad_spa = (image *)malloc(sizeof(image) * pad_width * pad_height))==NULL) {
		fprintf(stderr,"Probleme d'allocation memoire\n");
		exit(1);
	}
	w_width = pad_width / 2;
	w_height = pad_height / 2;
	
	/* Reconstruction */
	for (j=0;j<w_height;j++){
		for (i=0;i<w_width;i++){
			pad_spa[2*i + 2*j*pad_width] = (image) (( h00[i + j*w_width]
													+ h01[i + j*w_width]
													+ h10[i + j*w_width]
													+ h11[i + j*w_width]) / 2);
			pad_spa[2*i + (2*j+1)*pad_width] = (image) (( h00[i + j*w_width]
													    + h01[i + j*w_width]
													    - h10[i + j*w_width]
													    - h11[i + j*w_width]) / 2);
			pad_spa[2*i+1 + 2*j*pad_width] = (image) (( h00[i + j*w_width]
										 			  - h01[i + j*w_width]
													  + h10[i + j*w_width]
													  - h11[i + j*w_width]) / 2);
			pad_spa[2*i+1 + (2*j+1)*pad_width] = (image) (( h00[i + j*w_width]
													      - h01[i + j*w_width]
													      - h10[i + j*w_width]
													      + h11[i + j*w_width]) / 2);
		}
	}

	for (j=0;j<height;j++){
		for (i=0;i<width;i++){
			spa[i+j*width] = pad_spa[i+j*pad_width];
		}
	}

	free(pad_spa);
}
