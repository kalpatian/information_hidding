/*----------------------------------------------------------------------------
// StirMark Benchmark - lblocktoolkit.c
//
// Contents: Routines for block matching
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lblocktoolkit.c,v 1.2 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


block *BlockAlloc(int x_max,int y_max){ 
	block *blck;

	if((blck = (block *)malloc(x_max*y_max*sizeof(block))) == NULL){
		fprintf(stderr,"BlockAlloc: pb de place memoire\n");
		exit(1);
	}
	return blck;
}


void BlockGet(image *img_in,int x_max,int dim_b_h, int dim_b_v,int index,block *block_out){
/* block_out MUST be ALREADY allocated */
	int x;
	int y;

	for(y=0 ; y < dim_b_v; y++){
		for(x=0; x < dim_b_h; x++){ 
			block_out[x + y*dim_b_h] =(block) img_in[index + x + y*x_max];  
		}
	}    
}


void BlockErrorGet(ERROR_TYPE *img_in,int x_max,int dim_b,int index,ERROR_TYPE *block_out){
	/* block_out MUST be ALREADY allocated */
 
	int x;
	int y;

	for(y=0 ; y < dim_b; y++) {
		for(x=0; x < dim_b; x++) { 
			block_out[x + y*dim_b] =(block) img_in[index + x + y*x_max];  
    }
  }    
}


void BlockPut(block *block_in,int x_max,int dim_b,int index,image *img_inout){ 
	int x;
	int y;

	for(y=0; y < dim_b; y++){
		for(x=0; x < dim_b; x++){
			if (block_in[x+y*dim_b] != -1)
				img_inout[index +x +y*x_max] = block_in[x+y*dim_b];
		}
	}
	/*for (x = 0; x < 192; x++)
		img_inout[index+MASQUE[x]%16+MASQUE[x]/16*x_max] = block_in[MASQUE[x]];*/
}


void BlockAdd(double *block_in,int x_max,int dim_b,int index,double *img_inout){ 
	int x;
	int y;

	for(y=0; y < dim_b; y++){
		for(x=0; x < dim_b; x++){
			img_inout[index + x+y*x_max] += block_in[x+y*dim_b];
		}
	}
}


void BlockErrorPut(ERROR_TYPE *block_in,int x_max,int dim_b,int index,ERROR_TYPE *img_inout){ 
	int x;
	int y;   

	for(y=0; y < dim_b; y++){
		for(x=0; x < dim_b; x++){
			img_inout[index +x +y*x_max] = block_in[x+y*dim_b];
		}
	}
}


void BlockErrorPutMin(ERROR_TYPE *block_in,int x_max,int dim_b,int index,ERROR_TYPE *img_inout){ 
	int x;
	int y;
	/* int randnum; */

	for(y=0; y < dim_b; y++){
		for(x=0; x < dim_b; x++){
			/* randnum = rand()%2; */
			if (img_inout[index +x +y*x_max] == 0 || abs(img_inout[index +x +y*x_max]) > abs(block_in[x+y*dim_b]))
				img_inout[index +x +y*x_max] = block_in[x+y*dim_b];
			/*else
				img_inout[index +x +y*x_max] = (short int)((img_inout[index +x +y*x_max]+block_in[x+y*dim_b])/2);*/
		}
	}
}


void BlockCopy(block *block_in, int dim, block *block_out){ 
	int k;
	int maxlenght =dim*dim; 

	for(k=0; k < maxlenght; k++){
		block_out[k]=block_in[k];
	}
}


void BlockAddCst(block *block_data, int dim, int cste){ 
	int i;

	for(i=0; i < (dim * dim); i++)
		block_data[i] += cste;
}


void BlockPutMin(block *r,block *d_reduce, int w_orig,int dim_r,int index ,image * attracteur){
	int x;
	int y;
	
	/* attracteur[index +dim_r/2+dim_r/2*w_orig] = d_reduce[(dim_r*dim_r)/2]; */
	for(y=1; y < dim_r-1; y++) {
		for(x=1; x < dim_r-1; x++){
			if (attracteur[index +x +y*w_orig] == 0 || abs(r[x+y*dim_r]-attracteur[index +x +y*w_orig]) > abs(r[x+y*dim_r]-d_reduce[x+y*dim_r]))
				attracteur[index +x +y*w_orig] = d_reduce[x+y*dim_r];
			/*else
				img_inout[index +x +y*x_max] = (short int)((img_inout[index +x +y*x_max]+block_in[x+y*dim_b])/2);*/
		}
	}
}


void BlockBlur(block *orig, int dim, block *blur, int size){
	int i, j;
	int x, y;
	int tmp;
	int currentX;
	int currentY;

	int offsetX = (size-1) / 2;
	int offsetY = (size-1) / 2;

	for (i=0;i<dim;i++){
		for (j=0;j<dim;j++){
			tmp = 0;
			for (x=0;x<size;x++){
				currentX = i + x - offsetX;
				if (currentX < 0)
					currentX = -currentX;
				else if (currentX >= dim)
					currentX = 2*dim - currentX - 2;

				for (y=0;y<size;y++){
					currentY = j + y - offsetY;
					if (currentY < 0)
						currentY = -currentY;
					else if (currentY >= dim)
						currentY = 2*dim - currentY - 2;

					tmp += orig[currentX*dim + currentY];
				}
			}
			blur[i*dim+j] = (block)(tmp/(size*size));
		}
	}
}


void BlockMasque(block *block_in, int dim_r,double *block_out){
	int i;

	for(i = 0; i < DIM_MASK; i++)
		block_out[i] = (double)block_in[i] * MASQUE[i];
} 


void BlockAddMasque(double *mask,int x_max,int dim_b,int index){ 
	int x;
	int y;

	for(y=0; y < dim_b; y++){
		for(x=0; x < dim_b; x++){
			mask[index +x+y*x_max] += MASQUE[x+y*dim_b];
		}
	}
}


void BlockChoise(block *block_orig, block *block_spa, int dim_r,block *block_dct){
	int i;
	int err_moy_spa, err_moy_dct;

	err_moy_spa	=0;
	err_moy_dct =0;

	for (i = 0; i <dim_r*dim_r; i++) {
		err_moy_spa	+=	abs(block_orig[i]-block_spa[i]);
		err_moy_dct	+=	abs(block_orig[i]-block_dct[i]);
	}
		
	if (err_moy_spa < err_moy_dct) 
		for (i = 0; i <dim_r*dim_r; i++) {
			block_dct[i]=block_spa[i];
		}	
} 


double BlockMean(block *block_in, int dim_r){
	int i, somme=0;
	
	for (i = 0; i <dim_r*dim_r; i++)
		somme+=block_in[i];

	return((double)somme/(dim_r*dim_r));
}


double BlockVar(block *block_in, int dim_r, double mean){
	int i, somme=0;
	
	for (i = 0; i <dim_r*dim_r; i++)
		somme+=block_in[i]*block_in[i];

	return(sqrt((double)somme/(dim_r*dim_r)-mean*mean));
}


int BlockType(block *block_in, int dim_r, double *var){
	int dims2,somme=0, tip;
	double mean, smean, svar;
	block     *  sous_block;
	
	mean=BlockMean(block_in,dim_r);
	*var=BlockVar(block_in, dim_r, mean);

	dims2=dim_r/2;
	sous_block = BlockAlloc(dims2 ,dims2);
	BlockGet(block_in,dim_r ,dims2,dims2,0,sous_block);
	smean=BlockMean(sous_block,dims2);
	svar=BlockVar(sous_block, dims2, smean);
	if (svar < 15) somme++;

	sous_block = BlockAlloc(dims2 ,dims2);
	BlockGet(block_in,dim_r ,dims2,dims2,dims2,sous_block);
	smean=BlockMean(sous_block,dims2);
	svar=BlockVar(sous_block, dims2, smean);
	if (svar < 15) somme++;

	sous_block = BlockAlloc(dims2 ,dims2);
	BlockGet(block_in,dim_r ,dims2,dims2,dims2*dim_r,sous_block);
	smean=BlockMean(sous_block,dims2);
	svar=BlockVar(sous_block, dims2, smean);
	if (svar < 15) somme++;

	sous_block = BlockAlloc(dims2 ,dims2);
	BlockGet(block_in,dim_r ,dims2,dims2,dims2+dims2*dim_r,sous_block);
	smean=BlockMean(sous_block,dims2);
	svar=BlockVar(sous_block, dims2, smean);
	if (svar < 15) somme++;

	if (*var < 15) tip= 1;		/* smooth region */
	else if (somme >=2)
		tip =2;					/* contour with smooth region */
	else 
		tip =3;					/* texture */

	return(tip);
}




