/*----------------------------------------------------------------------------
// StirMark Benchmark - lcollage_search.c
//
// Contents: "Collage" within image
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lcollage_search.c,v 1.3 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


char s_o_ss_compute(block *red_d_block,block *r_block,int dim_r,
                    double som_d, double som_r,
                    double var_d, double var_r,
                    float *s, float *o, float *error){
	double sigmaW = 0.0;
	double accu;
	double pdr = 0.0;
	int i;

	/* Sum of the wights of the mask */
	for (i=0;i<DIM_MASK;i++)
		sigmaW += MASQUE[i];

	/* Determinant of the linear system */
	accu= sigmaW * var_d - som_d * som_d;
	/* If almost null: non stable system */
	if( fabs(accu) < 0.01 ){ 
		*s = 0.0; 
		*o =(float) som_r / (float) sigmaW; 
		/* Direct computation of the error   */
		*error = ((float)var_r
			     + (*o) * ( (*o)*(float)sigmaW - 2*(float)som_r )) 
				 / (float)sigmaW;
	}
	else {
		/* Sigma of (XiYi) */
		for (i=0;i<DIM_MASK;i++)
			pdr += MASQUE[i] * red_d_block[i] * r_block[i];
		/* Computation of the parameters of the photometric transformation */
		*s = ((float)(sigmaW*pdr) - (float)(som_d*som_r)) / (float) accu;
		*o = ((float)som_r - (*s)*(float)som_d) / (float) sigmaW;
		/* Direct computation of the error */
		*error = ((float)var_r
			     + (*s) * ( (*s)*(float)var_d - 2*(float)pdr + 2*(*o)*(float)som_d )
				 + (*o) * ( (*o)*(float)sigmaW - 2*(float)som_r ))
				 / (float)sigmaW;
	}		
	return 1;
}



float super_collage_spa(block *r, int  dim_r, int xr, int yr, float move_rate_x,
						float move_rate_y, image *r_image, int w_orig, int h_orig,
						block* d_reduce, int seuil){
	int xw = 0, yw = 0;               /* Coordinates of the top left corner of the sear window */
	int i, j;                         /* Indices */
	/* Least square computation variables */
	double tmp;
	double som_r, var_r;
	double som_dc, var_dc;
	int move_x, move_y;
		
		
	/* 
	 *const int dim_r2 = dim_r*dim_r;   // Area of a Range Block
	 *const int dim_r_2 = (int)dim_r/2;
	 */
		
	block *d;                         /* Domain Block */
	block **d_dictionnary;
					
	image *search_win;
		
	int xd, yd, m;
	float s,o;
	float err_codage;

	int min_xd = 0, min_yd = 0, min_m = 0;
	float min_s = 0.0, min_o = 0.0;
	float min_err = -1;

	int max_xd = 0, max_yd = 0, max_m = 0;
	float max_s = 0.0, max_o = 0.0;
	float max_err = -1;

	int best_xd, best_yd, best_m;
	float best_s, best_o;
	float best_err;

				
	d = BlockAlloc(IFS_DIM_D_H,IFS_DIM_D_V);
	search_win = BlockAlloc(IFS_WIN_D,IFS_WIN_D);
		
	/* Initialisation of the dictionnary which will contain
     the various geometric transformations
   */
	d_dictionnary=(block **)malloc (NB_GEOM_TRANS * sizeof(block *));
		
	for(m=0; m < NB_GEOM_TRANS ; m++)
		d_dictionnary[m]=(block *)BlockAlloc(dim_r,dim_r);
				
	/* Image scanning Range Block per Range Block. For each
     Range Block computation of the value of each pixel and the sume
     of the squared values 
   */
	som_r = 0.0;
	var_r = 0.0;
	for (i=0;i<DIM_MASK;i++){
		tmp = r[i]*MASQUE[i];
		som_r += tmp;
		var_r += tmp*r[i];
	}
	
	/* Compute the coordonate of the search window */
		
	/* Select search window randomly   */
	/* xw=rand()%(w_orig-IFS_WIN_D-1); */
	/* yw=rand()%(h_orig-IFS_WIN_D-1); */
		
	move_x = (int) (move_rate_x*(float)dim_r);
	move_y = (int) (move_rate_y*(float)dim_r);

	if (xr <= w_orig/2 && yr <= h_orig/2) {
		xw = xr+dim_r - move_x;
		yw = yr+dim_r - move_y;
	}
	else if (xr >= w_orig/2 && yr <= h_orig/2) {
		xw = xr - IFS_WIN_D + move_x;
		yw = yr + dim_r - move_y;
	}
	else if (xr <= w_orig/2 && yr >= h_orig/2) {  
		xw = xr + dim_r - move_x;
		yw = yr - IFS_WIN_D + move_y;
	}
	else if (xr >= w_orig/2 && yr >= h_orig/2){
		xw = xr  - IFS_WIN_D + move_x;
		yw = yr  - IFS_WIN_D + move_y;
	}
		
		
	/* Load the search window */
	BlockGet(r_image, w_orig, IFS_WIN_D,IFS_WIN_D, xw + w_orig* yw, search_win);
		
	/* Choose best solution in the search window */
	for( yd = 0; yd <= IFS_WIN_D-IFS_DIM_D_V; yd += IFS_STEP_D ) {
		for( xd = 0; xd <= IFS_WIN_D-IFS_DIM_D_H; xd += IFS_STEP_D ) {
			/* Domain block extraction */
			BlockGet(search_win, IFS_WIN_D, IFS_DIM_D_H, IFS_DIM_D_V, xd+IFS_WIN_D*yd,d_reduce);
		
			/* Sub Sampling */
			/* BlockSubSampling(d,IFS_DIM_D_H,IFS_DIM_D_V, dim_r,d_reduce); */
												
			/* Computation for the least square method */
			som_dc = 0.0;
			var_dc = 0.0;
			for (i=0;i<DIM_MASK;i++){
				tmp = d_reduce[i]*MASQUE[i];
				som_dc += tmp;
				var_dc += tmp*d_reduce[i];
			}
			
			/* Fill the dictionnary with the transformed Domain blocks
         Applies each allowed transformation  to the Domain Block
       */
			for( m=0 ; m < NB_GEOM_TRANS; m++ ){
				(*pt_tfgeo[m])(d_reduce,dim_r,d_dictionnary[m]); 											
				s_o_ss_compute(d_dictionnary[m],r,dim_r,som_dc,som_r,var_dc,var_r,&s,&o,&err_codage);
														
				/* We choose the "best" error
				   the FIRST value is used to init the error
         */

				if (err_codage < (float) seuil){
					if (err_codage >= max_err){
						max_err = err_codage;
						max_xd  = xd;
						max_yd  = yd;
						max_m   = m;
						max_s   = s;
						max_o   = o;
					}
				}
				else{
					if (err_codage < min_err || min_err == -1){
						min_err = err_codage;	
						min_xd  = xd;
						min_yd  = yd;
						min_m   = m;
						min_s   = s;
						min_o   = o;
					}
				}
			}  /* for m */
		}   /* for xd */
	} /* for yd */
	
	if (min_err == -1){
		best_err = max_err;	
		best_xd  = max_xd;
		best_yd  = max_yd;
		best_m   = max_m;
		best_s   = max_s;
		best_o   = max_o;
	}
	else{
		best_err = min_err;	
		best_xd  = min_xd;
		best_yd  = min_yd;
		best_m   = min_m;
		best_s   = min_s;
		best_o   = min_o;
	}

	BlockGet(search_win, IFS_WIN_D, IFS_DIM_D_H,IFS_DIM_D_V,best_xd+IFS_WIN_D*best_yd,d_reduce);								
	/* BlockSubSampling(d,IFS_DIM_D_H,IFS_DIM_D_V,dim_r,d_reduce); */

	(*pt_tfgeo[best_m])(d_reduce,dim_r,d_dictionnary[best_m]); 
		
	for (j = 0; j < dim_r; j++)
		for (i = 0; i < dim_r; i++)
			d_reduce[i+j*dim_r] = (image)(d_dictionnary[best_m][i+j*dim_r]*best_s+best_o);


	/* Free memory */
		
	free(d);
	free(search_win);
	for(m=0;m<NB_GEOM_TRANS;m++) {
		free(d_dictionnary[m]);
	}
	free(d_dictionnary);
	return(best_err);
}



/*--------------------------------------------------------------------------------*
 | This function performs a simple IFS iteration without thresholding.            |
 | It stores the errors in an array in order to build the cumulative histogram    |
 | later.                                                                         |
 *--------------------------------------------------------------------------------*/

void simpleSearchIFS(image* image_orig, int width, int height, image* image_water,
					 image * attracteur, float **hist, long *numSample) {
	int xr,yr;
	const int dim_r = IFS_DIM_R;
	int dim_r2;
				
	block *range;          /* Range block                     */
	block *domain;         /* Domain block reduced to Ri size */
	float min_err, min_err2;

	dim_r2=dim_r*dim_r;

	(*hist) = (float *) calloc(width*height,sizeof(float));

	range = BlockAlloc(dim_r ,dim_r);
	domain = BlockAlloc(dim_r ,dim_r);

	/* Image scanning Range Block per Range Block. For each
     Range Block computation of the value of each pixel and the sume
     of the squared values 
   */
	(*numSample) = 0;
	for(  yr = 0; yr <= height-dim_r; yr += IFS_STEP_R ) {
		for( xr = 0; xr <= width-dim_r; xr += IFS_STEP_R ) {
			/* Range block extraction  */
			BlockGet(image_water, width, dim_r, dim_r, xr+yr*width, range);

			/* Domain block association */
			min_err = super_collage_spa(range, dim_r, xr, yr, 0,0, image_orig,
										width, height, domain, NO_THRESHOLD);
			if (min_err > dim_r2) {
				min_err2=super_collage_spa(range, dim_r, xr, yr, 0.75, 0.75, image_orig,
										   width, height, domain, NO_THRESHOLD);
				if (min_err2 > min_err) {
					min_err=super_collage_spa(range, dim_r, xr, yr, 0,0, image_orig,
											  width, height, domain, NO_THRESHOLD);
				}
				else
					min_err=min_err2;
			}

			/* Memorize the error */
			(*hist)[*numSample] = min_err;
			(*numSample)++;
		} /* for xr */
	} /* for yr */

	/* Free memory */
	free(range);
	free(domain);
}


/*--------------------------------------------------------------------------------*
 | This function performs an IFS iteration with thresholding and collate the      |
 | different parts of the attacked image.                                         |
 *--------------------------------------------------------------------------------*/

void collageSearchIFS(image* image_orig, int width, int height,
			 		  image* image_water, image * attracteur, int seuil) {
	int xr,yr;
	int i;
	const int dim_r = IFS_DIM_R;
	int dim_r2;
				
	block *range;          /* Range block                     */
	block *domain;         /* Domain block reduced to Ri size */
	float min_err, min_err2;

	double *image_tmp;
	double *masque_global;
	double *block_mask;
	
	dim_r2=dim_r*dim_r;

	image_tmp = (double *) calloc(width*height,sizeof(double));
	masque_global = (double *) calloc(width*height,sizeof(double));
	block_mask = (double *) calloc(dim_r*dim_r,sizeof(double));

	range = BlockAlloc(dim_r ,dim_r);
	domain = BlockAlloc(dim_r ,dim_r);

	/* Image scanning Range Block per Range Block. For each
     Range Block computation of the value of each pixel and the sume
     of the squared values 
   */
	for(  yr = 0; yr <= height-dim_r; yr += IFS_STEP_R ) {
		for( xr = 0; xr <= width-dim_r; xr += IFS_STEP_R ) {
			/* Range block extraction  */
			BlockGet(image_water, width, dim_r, dim_r, xr+yr*width, range);

			/* Domain block association */
			min_err = super_collage_spa(range, dim_r, xr, yr, 0,0, image_orig,
										width, height, domain, seuil);
			if (min_err > dim_r2) {
				min_err2=super_collage_spa(range, dim_r, xr, yr, 0.75, 0.75, image_orig,
										   width, height, domain, seuil);
				if (min_err2 > min_err) {
					min_err=super_collage_spa(range, dim_r, xr, yr, 0,0, image_orig,
											  width, height,  domain, seuil);
				}
				else
					min_err=min_err2;
			}

			/* Block copy */
			BlockMasque(domain, dim_r, block_mask);
			BlockAdd(block_mask, width, dim_r, xr+yr*width, image_tmp);						
			BlockAddMasque(masque_global, width, dim_r, xr+yr*width);
		} /* for xr */
	} /* for yr */

	/* Free memory */
	free(range);
	free(domain);
	free(block_mask);

	/* Normalisation after masking */
	for (i =0; i < width*height; i++){
		if (masque_global[i]<1)
			attracteur[i] = (block) ( (1-masque_global[i])*((double)image_water[i]) + image_tmp[i] + .5);
		else
			attracteur[i] = (block) ( image_tmp[i]/masque_global[i] + .5);
	}
				
	/* Free memory */
	free(masque_global);
	free(image_tmp);
}


/*--------------------------------------------------------------------------------*
 | This function builds the cumulative histogram of an array given in input and   |
 | returns an adaptative threshold.                                               |
 *--------------------------------------------------------------------------------*/

int _compare( const void *arg1, const void *arg2 )
{
  float v1 = *(float *) arg1, v2 = *(float *)arg2;
  if (v1 < v2) return -1;
  if (v2 < v1) return 1;
  return 0;
}


int findAdaptativeThreshold(float *array, long numSample, int percent){
	long index;
	int threshold;

  qsort(array, numSample, sizeof(float),_compare);
	index = (long)(numSample*percent/100) + 1;
	threshold = (int)(array[index]) + 1;

	return threshold;
}
