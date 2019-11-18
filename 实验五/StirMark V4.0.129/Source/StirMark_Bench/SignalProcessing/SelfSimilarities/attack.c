/*----------------------------------------------------------------------------
// StirMark Benchmark - attack.c
//
// Contents: Main function implementing the self similarities attack
//
// Purpose:  This is the self similarities attack as described in:
//           C. Rey, G. Doërr, J.-L. Dugelay and G. Csurka, "Toward generic
//           image dewatermarking?", to be presented at ICIP 2002
//           Also available as Eurécom technical report RR-02-060
//           http://www.eurecom.fr/~dugelay/WM/RR_02_060.pdf
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/attack.c,v 1.3 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "compil.h"
#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"



/*--------------------------------------------------------------------------------*
 | This function IFS attacks a given channel.                                     |
 *--------------------------------------------------------------------------------*/

void attackChannel(image *orig, image *water, image *sup,
                   int width, int height, optionsCmd *cmd)
{
	int i, threshold;
	long numSample;
	int w_wave, h_wave;                                      /* Size of a wavelet                              */
	image *h00_orig, *h01_orig, *h10_orig, *h11_orig;        /* Wavelet decomposition of the original image    */
	image *h00_water, *h01_water, *h10_water, *h11_water;    /* Wavelet decomposition of the watermarked image */
	image *h00_sup, *h01_sup, *h10_sup, *h11_sup;            /* Wavelet support                                */
	float *hist;

  /* Switching depending on the type of attack */
	if (cmd->type == SS_SWITCH){		/* Exchanging channels */
		printf("   Exchanging channels.\n");
		for (i=0;i<width*height;i++)
			sup[i] = orig[i];
	}

	if (cmd->type == SS_SPATIAL){		/* Attack in spatial domain */
		printf("   First IFS iteration...\n");
		simpleSearchIFS(orig, width, height, water, sup, &hist, &numSample);
		printf("   Adaptative threshold computation...");
		threshold = findAdaptativeThreshold(hist, numSample, cmd->percent);
		printf("T=%d\n", threshold);
		free(hist);
		printf("   Second IFS iteration...\n");
		collageSearchIFS(orig, width, height, water, sup, threshold);
	}

	else if (cmd->type == SS_WAVELET){  /* Attack in wavelet domaine */
		/* Memory allocation for wavelet support */
		if (width%2 == 0)
			w_wave = width/2;
		else
			w_wave = (width + 1)/2;
		if (height%2 == 0)
			h_wave = height/2;
		else
			h_wave = (height + 1)/2;

		if((h00_sup = (image *) malloc(sizeof(image) * w_wave * h_wave))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((h01_sup = (image *) malloc(sizeof(image) * w_wave * h_wave))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((h10_sup = (image *) malloc(sizeof(image) * w_wave * h_wave))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((h11_sup = (image *) malloc(sizeof(image) * w_wave * h_wave))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}

		/* Wavelet decomposition of the channels */
		printf("   Wavelet decomposition.\n");
		haarWaveDecomposition(orig, width, height, &h00_orig, &h01_orig, &h10_orig, &h11_orig);
		haarWaveDecomposition(water, width, height, &h00_water, &h01_water, &h10_water, &h11_water);

		/* 00 band */
		printf("   Band 00: First IFS iteration...\n");
		simpleSearchIFS(h00_orig, w_wave, h_wave, h00_water, h00_sup, &hist, &numSample);
		printf("   Band 00: Adaptative threshold computation...");
		threshold = findAdaptativeThreshold(hist, numSample, cmd->percent);
		printf("T=%d\n", threshold);
		free(hist);
		printf("   Band 00: Second IFS iteration...\n");
		collageSearchIFS(h00_orig, w_wave, h_wave, h00_water, h00_sup, threshold);

		/* 01 band */
		printf("   Band 01: First IFS iteration...\n");
		simpleSearchIFS(h01_orig, w_wave, h_wave, h01_water, h01_sup, &hist, &numSample);
		printf("   Band 01: Adaptative threshold computation...");
		threshold = findAdaptativeThreshold(hist, numSample, cmd->percent);
		printf("T=%d\n", threshold);
		free(hist);
		printf("   Band 01: Second IFS iteration...\n");
		collageSearchIFS(h01_orig, w_wave, h_wave, h01_water, h01_sup, threshold);

		/* 10 band */
		printf("   Band 10: First IFS iteration...\n");
		simpleSearchIFS(h10_orig, w_wave, h_wave, h10_water, h10_sup, &hist, &numSample);
		printf("   Band 10: Adaptative threshold computation...");
		threshold = findAdaptativeThreshold(hist, numSample, cmd->percent);
		printf("T=%d\n", threshold);
		free(hist);
		printf("   Band 10: Second IFS iteration...\n");
		collageSearchIFS(h10_orig, w_wave, h_wave, h10_water, h10_sup, threshold);

		/* 11 band */
		printf("   Band 11: First IFS iteration...\n");
		simpleSearchIFS(h11_orig, w_wave, h_wave, h11_water, h11_sup, &hist, &numSample);
		printf("   Band 11: Adaptative threshold computation...");
		threshold = findAdaptativeThreshold(hist, numSample, cmd->percent);
		printf("T=%d\n", threshold);
		free(hist);
		printf("   Band 11: Second IFS iteration...\n");
		collageSearchIFS(h11_orig, w_wave, h_wave, h11_water, h11_sup, threshold);

		free(h00_orig);free(h01_orig);free(h10_orig);free(h11_orig);
		free(h00_water);free(h01_water);free(h10_water);free(h11_water);
		
		printf("   Wavelet reconstruction.\n");
		haarWaveReconstruction(sup, width, height, h00_sup, h01_sup, h10_sup, h11_sup);
		
		free(h00_sup);free(h01_sup);free(h10_sup);free(h11_sup);
	}
}

