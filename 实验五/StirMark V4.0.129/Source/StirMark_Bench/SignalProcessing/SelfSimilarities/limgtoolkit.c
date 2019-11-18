/*----------------------------------------------------------------------------
// StirMark Benchmark - lgeom.c
//
// Contents: Basic function to work with images including DCT
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/limgtoolkit.c,v 1.3 2002/04/19 10:23:59 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>
#include <math.h>
#include <stdio.h>

#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


short int RoundInt(double reel)
{
	short int entier;

  entier = (short int)reel;
  if ((double)(reel - entier) > 0.5)
		entier++;

  return entier;
}

void ImageCopy(image * image_in, int x_max,int y_max, image* image_out)
{ 
  int x;
  int y;
  
  /* image_out is ALREADY malloced */
  
  for(y=0;y<y_max;y++) {
		for(x=0; x < x_max; x++) {
			image_out[x+y*x_max] = image_in[x+y*x_max];
    }
  }
}



void ImageNormalize(image *img,int x_max,int y_max)
/* check that the image pixels are in range 0-255 */
{
  int  k;
  int  maxlenght  = x_max*y_max;
  int  neg        =  0;
  int  pos        =  0;
	
	
  for(k=0; k < maxlenght; k++) {
    if(img[k] > 255) {  
      pos++;
      img[k] = 255;
    }
    else if(img[k] < 0) { 
      neg++;  
      img[k]= 0;
    }
  }
	
  printf(" NORMALISATION %d <0 et %d >255 \n",neg,pos);
}




/*---------------------------------------------------------------------------*/

double PSNR(image *image1, image *image2, int width, int height)
{
	int i;
  int max = 255;
  long int N;
  double somme2 =0.0 ;
	
  N = width * height;
	
  for (i=0;i<N;i++)
		somme2 += (double)((image1[i] - image2[i]) * (image1[i] - image2[i]));
	
	return (20 * log10(max) + 10 * log10(N) - 10 * log10(somme2));
}

/*---------------------------------------------------------------------------*/

void ExpandLevels(image *R, image *G, image *B, int size,int maxRGB)
{
	int i;
	double ratio = (double)(255.0/(double)(maxRGB));
	
	for (i=0;i<size;i++)
	{
		R[i] = (image)((double)R[i]*ratio);
		G[i] = (image)((double)G[i]*ratio);
		B[i] = (image)((double)B[i]*ratio);
	}
}




/*-----------------DCT--------------*/

void DCT(image* img, int width, int height,int Nb, coefDct* coeffDct) {
	float *data_tmp;
	int i,j,k,n,h;
	float xk,ak;

	data_tmp = (float *)malloc(sizeof(float)*Nb*Nb);
	

	for (j = 0; j < height; j+=Nb) {
		for (i = 0; i < width; i+=Nb) {
			/* Horizontal DCT */
			for (h = 0; h < Nb; h++) {
				for (k = 0; k < Nb; k++) {
					xk=0;
					ak = 1.0;
					for (n = 0; n < Nb; n++) {
						xk+=(float)img[i+n+(h+j)*width]*(float)cos(PI*k*(2*n+1)/(2*Nb));
					}
					if (k == 0) 
						ak = 1/((float)sqrt(2));
					data_tmp[k+h*Nb]=ak*xk*2/Nb;
				}
			}

			/* Vertical DCT */
			for (h = 0; h < Nb; h++) {
				for (k = 0; k < Nb; k++) {
					xk=0;
					ak = 1.0;
					for (n = 0; n < Nb; n++) {
						xk+=data_tmp[h+n*Nb]*(float)cos(PI*k*(2*n+1)/(2*Nb));
					}
					if (k == 0) 
						ak = 1/((float)sqrt(2));
					coeffDct[i+h+(k+j)*width]=ak*xk*2/Nb;
					printf("%f\n", coeffDct[i+h+(k+j)*width]);
				}
			}
		}
	}
}

/*-----------------------DCT INV-----------------------------------*/

void IDCT(coefDct* coeffDct,int width,int height,int Nb,	image* img_out) {
	float *data_tmp;
	int i,j,k,n,h;
	float xn,ak;

	data_tmp = (float *)malloc(sizeof(float)*Nb*Nb);
	

	for (j = 0; j < height; j+=Nb) {
		for (i = 0; i < width; i+=Nb) {
			/* Vertical DCT */
			for (h = 0; h < Nb; h++) {
				for (n = 0; n < Nb; n++) {
					xn=0;
					for (k = 0; k < Nb; k++) {	
						if (k != 0) 
							ak = 1;
						else
							ak = 1/((float)sqrt(2));					
						xn+=ak*coeffDct[i+h+(k+j)*width]*(float)cos(PI*k*(2*n+1)/(2*Nb));
					}
					data_tmp[h+n*Nb]=xn;
				}
			}

			/* Horizontal DCT */
			for (h = 0; h < Nb; h++) {
				for (n = 0; n < Nb; n++) {
					xn=0;
					for (k = 0; k < Nb; k++) {
						if (k != 0) 
							ak = 1;
						else
							ak = 1/((float)sqrt(2));
						xn+=ak*data_tmp[k+h*Nb]*(float)cos(PI*k*(2*n+1)/(2*Nb));
					}
					img_out[i+n+(h+j)*width]=(short int)xn;
				}
			}
		}
	}
}



/*-----------------DCT Bloc--------------*/

void DCT_Bloc(block *bloc,int bloc_size, coefDct* coeffDct) {
	coefDct *data_tmp;
	int k,n,h;
	float xk,ak;
	
	data_tmp = (coefDct *)malloc(sizeof(float)*bloc_size*bloc_size);
	
		/* Horizontal DCT */
	for (h = 0; h < bloc_size; h++) {
				for (k = 0; k < bloc_size; k++) {
					xk=0;
					ak = 1.0;
					for (n = 0; n < bloc_size; n++) {
						xk+=(float)bloc[n+h*bloc_size]*(float)cos(PI*k*(2*n+1)/(2*bloc_size));
					}
					if (k == 0) 
						ak = 1/((float)sqrt(2));
					data_tmp[k+h*bloc_size]=ak*xk*2/bloc_size;
				}
	}
	
	/* Vertical DCT */
	for (h = 0; h < bloc_size; h++) {
				for (k = 0; k < bloc_size; k++) {
					xk=0;
					ak = 1.0;
					for (n = 0; n < bloc_size; n++) {
						xk+=data_tmp[h+n*bloc_size]*(float)cos(PI*k*(2*n+1)/(2*bloc_size));
					}
					if (k == 0) 
						ak = 1/((float)sqrt(2));
					coeffDct[h+k*bloc_size]=ak*xk*2/bloc_size;
				}
	}
	free(data_tmp);
	
}

/*-----------------------DCT BLOC INV-----------------------------------*/

void IDCT_Bloc(coefDct* coeffDct,int bloc_size,	block* bloc_out) {
	coefDct *data_tmp;
	int k,n,h;
	float xn,ak;
	
	data_tmp = (coefDct *)malloc(sizeof(float)*bloc_size*bloc_size);
	
	
	
	/* Vertical DCT */
	for (h = 0; h < bloc_size; h++) {
				for (n = 0; n < bloc_size; n++) {
					xn=0;
					for (k = 0; k < bloc_size; k++) {	
						if (k != 0) 
							ak = 1;
						else
							ak = 1/((float)sqrt(2));					
						xn+=ak*coeffDct[h+k*bloc_size]*(float)cos(PI*k*(2*n+1)/(2*bloc_size));
					}
					data_tmp[h+n*bloc_size]=xn;
				}
	}
	
	/* Horizontal DCT */
	for (h = 0; h < bloc_size; h++) {
				for (n = 0; n < bloc_size; n++) {
					xn=0;
					for (k = 0; k < bloc_size; k++) {
						if (k != 0) 
							ak = 1;
						else
							ak = 1/((float)sqrt(2));
						xn+=ak*data_tmp[k+h*bloc_size]*(float)cos(PI*k*(2*n+1)/(2*bloc_size));
					}
					bloc_out[n+h*bloc_size]=(short int)xn;
				}
				
	}

	free(data_tmp); 
}


void lectureZZ(int *zz, int dim_r)
{
	int i,j,xzz,yzz;
	int posi =0;
		
	/* Zigzag scan */
	for (i = 0; i < dim_r; i++){
		for (j = 0; j <= i; j++) {
			i%2 ? (xzz=i-j):(xzz=j);
			i%2 ? (yzz=j):(yzz=i-j);
			zz[posi] = xzz+yzz*dim_r;
			posi++;
		}
	}
	for (i = 1; i < dim_r; i++){
		for (j = dim_r-1; j >= i; j--) {
			i%2 ? (xzz=i+dim_r-1-j):(xzz=j);
			i%2 ? (yzz=j):(yzz=i+dim_r-1-j);
			zz[posi] = xzz+yzz*dim_r;
			posi++;
		}
	}
}

