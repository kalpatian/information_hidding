/*----------------------------------------------------------------------------
// StirMark Benchmark - lgeom.c
//
// Contents: Basic geometric transformations for blocks
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lgeom.c,v 1.2 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


/* The function array for the geometric transformations */
void (*pt_tfgeo[8])(block *, int , block *)={ BlockIdent,
                                          BlockSymHor,
                                          BlockSymVert,
                                          BlockSymDiag1,
                                          BlockSymDiag2,
                                          BlockRot90,
                                          BlockRot180,
                                          BlockRot270
                                          };
/* void (*pt_tfgeo[7])(block *, int , block *)={ BlockSymHor,
                                          BlockSymVert,
                                          BlockSymDiag1,
                                          BlockSymDiag2,
                                          BlockRot90,
                                          BlockRot180,
                                          BlockRot270
                                          }; */


void BlockIdent(block *block_in,int dim, block *block_out){
	/*  Identity */     
	int loop;
   
	for(loop=0; loop < (dim*dim); loop++)
		block_out[loop] = block_in[loop];
}


void BlockSymHor(block *block_in,int dim,block *block_out){
	/* Transfo Symetrie par rapport axe horizontal */
	int xr;
	int yr;
   
	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr + yr*dim] = block_in[xr + (dim-1-yr)*dim];
}


void BlockSymVert(block *block_in,int dim,block *block_out){
	/* transfo Symetrie par rapport axe vertical */
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr+ yr*dim] = block_in[(dim*yr)+dim-1-xr];
}



void BlockSymDiag1(block *block_in,int dim,block *block_out){
	/* Transfo Symetrie par rapport a la 1ere diagonale */
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr+ yr*dim] = block_in[xr*dim+yr];
}



void BlockSymDiag2(block *block_in,int dim,block *block_out){
	/* transfo Symetrie par rapport a la 2eme diagonale */
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr + yr*dim] = block_in[(dim-1-xr)*dim+(dim-1-yr)];
}



void BlockRot90(block *block_in,int dim,block *block_out){
	/* transfo Rotation 90 degres */     
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr +yr*dim] = block_in[xr*dim+dim-1-yr];
}



void BlockRot180(block *block_in,int dim,block *block_out){
	/* transfo Rotation 180 degres */     
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr +yr*dim] = block_in[(dim-1-yr)*dim+dim-1-xr];
}



void BlockRot270(block *block_in,int dim,block *block_out){
	/* Transfo Rotation 270 degres */
	int xr;
	int yr;

	for(yr=0; yr < dim; yr++)
		for(xr=0; xr < dim; xr++)
			block_out[xr +yr*dim] = block_in[(dim-1-xr)*dim+yr];
}



/* THE SUB SAMPLING FONCTIONS */

void BlockSubSampling(block *d_block,int dim_d_h,int dim_d_v,int dim_r,block *r_block){
	/* effectue un ratio du domain Block  jusqu'a obtention d'un block dim_r*dim_r */
	int x,i;
	int y,j;
	/* attention les dimensions du bloc rectangulaire du domain bloc doivent etre multiples de dim_r*/
	int ratio_x=dim_d_h/dim_r; 
	int ratio_y=dim_d_v/dim_r;
		
	for (y=0; y < dim_r; y++) {
		for(x=0; x < dim_r; x++){
			r_block[x+dim_r*y] = 0;
			for (j=0; j < ratio_y; j++) {
				for(i=0; i < ratio_x; i++){
					r_block[x+dim_r*y] += d_block[ratio_x*x+i + dim_d_h*(ratio_y*y+j)];
				}
			}
			r_block[x+dim_r*y]= (int)((float) (r_block[x+dim_r*y]/(ratio_x*ratio_y)));
		}
	}
}


void BlockSubSampling_2(block *d_block,int dim_d,block *r_block){
	/* sous echantillonage par moyennage simple */
    int x;
    int y;
    int dim_r=dim_d/2;

	for(y=0; y < dim_r; y++)
		for(x=0; x < dim_r; x++)
			r_block[x+dim_r*y] = 
			(int)( (float)( d_block[2*x + dim_d*2*y]
            + d_block[2*x+1 + dim_d*2*y    ]
            + d_block[2*x   + dim_d*(2*y+1)]
            + d_block[2*x+1 + dim_d*(2*y+1)] ) / 4.0);
}


void BlockSubSampling_4(block *d_block,int dim_d,block *r_block){
     /* sous echantillonage par moyennage simple */
    int x;
    int y;
    int dim_r=dim_d/4;

	for(y=0; y < dim_r; y++)
		for(x=0; x < dim_r; x++)
			r_block[x+dim_r*y] = 
			(int)( (float)  ( d_block[4*x   + dim_d*4*y    ]
							+ d_block[4*x+1 + dim_d*4*y    ]
							+ d_block[4*x+2 + dim_d*4*y    ]
							+ d_block[4*x+3 + dim_d*4*y    ]

							+ d_block[4*x   + dim_d*(4*y+1)]
							+ d_block[4*x+1 + dim_d*(4*y+1)]
							+ d_block[4*x+2 + dim_d*(4*y+1)]
							+ d_block[4*x+3 + dim_d*(4*y+1)]

							+ d_block[4*x   + dim_d*(4*y+2)]
							+ d_block[4*x+1 + dim_d*(4*y+2)]
							+ d_block[4*x+2 + dim_d*(4*y+2)]
							+ d_block[4*x+3 + dim_d*(4*y+2)]
            
							+ d_block[4*x   + dim_d*(4*y+3)]
							+ d_block[4*x+1 + dim_d*(4*y+3)]
							+ d_block[4*x+2 + dim_d*(4*y+3)]
							+ d_block[4*x+3 + dim_d*(4*y+3)] ) / 16.0);
}
