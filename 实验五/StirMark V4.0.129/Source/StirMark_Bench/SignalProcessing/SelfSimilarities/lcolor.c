/*----------------------------------------------------------------------------
// StirMark Benchmark - lcolor.c
//
// Contents: Colour space conversion routines
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/lcolor.c,v 1.2 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "SelfSimilarities.h"
#include "lib_kadv_codec.h"


/*--------------------------------------------------------------------------------*
 | This function converts the image from the RBG to the specified color space.    |
 *--------------------------------------------------------------------------------*/

void convertRGB2Channel(image *R, image *G, image *B, image **channel1,	image **channel2,
						image **channel3, int width, int height, int color_space){
	int i;

	if (color_space == SS_RGB){
		if((*channel1 = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((*channel2 = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((*channel3 = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		for (i=0;i<width*height;i++){
			(*channel1)[i] = R[i];
			(*channel2)[i] = G[i];
			(*channel3)[i] = B[i];
		}
	}

	else if (color_space == SS_YUV){
		printf("Color space mapping: RGB -> YUV\n");
		ConvertRGB2YUV(R, G, B, channel1, channel2, channel3, width, height);
	}

	else if (color_space == SS_HSV) {
		printf("Color space mapping: RGB -> HSV\n");
		ConvertRGB2HSV(R, G, B, channel1, channel2, channel3, width, height);
	}

	else if (color_space == SS_LAB) {
		printf("Color space mapping: RGB -> Lab\n");
		ConvertRGB2Lab(R, G, B, channel1, channel2, channel3, width, height);
	}

	else if (color_space == SS_XYZ) {
		printf("Color space mapping: RGB -> XYZ\n");
		ConvertRGB2XYZ(R, G, B, channel1, channel2, channel3, width, height);
	}
}


/*--------------------------------------------------------------------------------*
 | This function converts the image from the specified to the RGB color space.    |
 *--------------------------------------------------------------------------------*/

void convertChannel2RGB(image *channel1, image *channel2, image *channel3, image **R,
						image **G, image **B, int width, int height, int color_space){
	int i;

	if (color_space == SS_RGB){
		if((*R = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((*G = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		if((*B = (image *)malloc(sizeof(image) * width * height))==NULL) {
			fprintf(stderr,"ERROR: Memory allocation problem!\n");
			exit(1);
		}
		for (i=0;i<width*height;i++){
			(*R)[i] = channel1[i];
			(*G)[i] = channel2[i];
			(*B)[i] = channel3[i];
		}
	}

	else if (color_space == SS_YUV){
		printf("Color space mapping: YUV -> RGB\n");
		ConvertYUV2RGB(channel1, channel2, channel3, R, G, B, width, height);
	}

	else if (color_space == SS_HSV){
		printf("Color space mapping: HSV -> RGB\n");
		ConvertHSV2RGB(channel1, channel2, channel3, R, G, B, width, height);
	}

	else if (color_space == SS_LAB){
		printf("Color space mapping: Lab -> RGB\n");
		ConvertLab2RGB(channel1, channel2, channel3, R, G, B, width, height);
	}

	else if (color_space == SS_XYZ){
		printf("Color space mapping: XYZ -> RGB\n");
		ConvertXYZ2RGB(channel1, channel2, channel3, R, G, B, width, height);
	}
}


/*---------------------------------------------------------------------------
// RGB <=> YUV transform
*/

void ConvertRGB2YUV(image *R, image *G, image *B, image **Y, image **U, image **V, int width, int height){
	int i;

	(*Y) = (image *) malloc(sizeof(image)*width*height);
	(*U) = (image *) malloc(sizeof(image)*width*height);
	(*V) = (image *) malloc(sizeof(image)*width*height);

	for (i=0;i<width*height;i++){
		(*Y)[i] = (image) RoundInt( (double)(RGB_TO_YUV_MATRIX[0][0] * R[i])
								  + (double)(RGB_TO_YUV_MATRIX[0][1] * G[i])
								  + (double)(RGB_TO_YUV_MATRIX[0][2] * B[i]) );

		(*U)[i] = (image) RoundInt( (double)(RGB_TO_YUV_MATRIX[1][0] * R[i])
								  + (double)(RGB_TO_YUV_MATRIX[1][1] * G[i])
								  + (double)(RGB_TO_YUV_MATRIX[1][2] * B[i]) );

		(*V)[i] = (image) RoundInt( (double)(RGB_TO_YUV_MATRIX[2][0] * R[i])
								  + (double)(RGB_TO_YUV_MATRIX[2][1] * G[i])
								  + (double)(RGB_TO_YUV_MATRIX[2][2] * B[i]) );
	}
}


void ConvertYUV2RGB(image *Y, image *U, image *V, image **R, image **G, image **B, int width, int height){
	int i;

	(*R) = (image *) malloc(sizeof(image)*width*height);
	(*G) = (image *) malloc(sizeof(image)*width*height);
	(*B) = (image *) malloc(sizeof(image)*width*height);

	for (i=0;i<width*height;i++){
		(*R)[i] = (image) RoundInt( (double)(YUV_TO_RGB_MATRIX[0][0] * Y[i])
								  + (double)(YUV_TO_RGB_MATRIX[0][1] * U[i])
								  + (double)(YUV_TO_RGB_MATRIX[0][2] * V[i]) );

		(*G)[i] = (image) RoundInt( (double)(YUV_TO_RGB_MATRIX[1][0] * Y[i])
								  + (double)(YUV_TO_RGB_MATRIX[1][1] * U[i])
								  + (double)(YUV_TO_RGB_MATRIX[1][2] * V[i]) );

		(*B)[i] = (image) RoundInt( (double)(YUV_TO_RGB_MATRIX[2][0] * Y[i])
								  + (double)(YUV_TO_RGB_MATRIX[2][1] * U[i])
								  + (double)(YUV_TO_RGB_MATRIX[2][2] * V[i]) );
	}
}



/*---------------------------------------------------------------------------
// RGB <=> HSV transform
// From Alvy Ray Smith, Color Gamut Transform
*/

void ConvertRGB2HSV(image *R, image *G, image *B, image **H, image **S, image **V, int width, int height){
	int i;
	image min, max, s;
	float r, g, b;
	float h = 0.0;

	(*H)=(image *)malloc(sizeof(image)*width*height);
	(*V)=(image *)malloc(sizeof(image)*width*height);
	(*S)=(image *)malloc(sizeof(image)*width*height);


	for (i=0;i<width*height;i++){
		max = R[i];
		min = R[i];
		if (G[i] > max)
			max = G[i];
		else if (G[i] < min)
			min = G[i];
		if (B[i] > max)
			max = B[i];
		else if (B[i] < min)
			min = B[i];

		(*V)[i] = max;

		if (max == 0)
			s = 0;
		else
			s = (image) RoundInt((double)(255 * (float)(max - min) / (float)max));
		(*S)[i] = s;

		if (s == 0)
			(*H)[i] = (image) (255*h/6);
		else {
			r = (float)(max-R[i]) / (float)(max-min);
			g = (float)(max-G[i]) / (float)(max-min);
			b = (float)(max-B[i]) / (float)(max-min);
			if (R[i] == max)
				if (G[i] == min)
					h = 5+b;
				else
					h = 1-g;
			else if (G[i] == max)
				if (B[i] == min)
					h = 1+r;
				else
					h = 3-b;
			else
				if (R[i] == min)
					h = 3+g;
				else
					h= 5-r;
			(*H)[i] = (image)RoundInt((double)(255*h/6));
		}
	}
}


void ConvertHSV2RGB(image *H, image *S, image *V, image **R, image **G, image **B, int width, int height){
	int i, g;
	float f, h, s;
	image m, n, k;

	(*R)=(image *)malloc(sizeof(image)*width*height);
	(*G)=(image *)malloc(sizeof(image)*width*height);
	(*B)=(image *)malloc(sizeof(image)*width*height);

	for (i=0;i<width*height;i++){
		s = (float)(S[i]) / 255;
		h = (float)(H[i]) / 255 * 6 ;
		g = (int)floor(h);
		if (g==6)
			g=5;
		f = h - g;

		m = (image) RoundInt( (double)( (float)(V[i]) * (1-s)) );
		n = (image) RoundInt( (double)( (float)(V[i]) * (1-s*f)) );
		k = (image) RoundInt( (double)( (float)(V[i]) * (1-s*(1-f))) );

		switch (g){
			case 0:
				(*R)[i] = V[i];
				(*G)[i] = k;
				(*B)[i] = m;
				break;
			case 1:
				(*R)[i] = n;
				(*G)[i] = V[i];
				(*B)[i] = m;
				break;
			case 2:
				(*R)[i] = m;
				(*G)[i] = V[i];
				(*B)[i] = k;
				break;
			case 3:
				(*R)[i] = m;
				(*G)[i] = n;
				(*B)[i] = V[i];
				break;
			case 4:
				(*R)[i] = k;
				(*G)[i] = m;
				(*B)[i] = V[i];
				break;
			case 5:
				(*R)[i] = V[i];
				(*G)[i] = m;
				(*B)[i] = n;
				break;
		}
	}
}


/*---------------------------------------------------------------------------
// RGB <=> XYZ transform
*/

void ConvertRGB2XYZ(image *R, image *G, image *B, image **X, image **Y, image **Z, int width, int height){
	int i;

	(*X) = (image *) malloc(sizeof(image)*width*height);
	(*Y) = (image *) malloc(sizeof(image)*width*height);
	(*Z) = (image *) malloc(sizeof(image)*width*height);

	for (i=0;i<width*height;i++){
		(*X)[i] = (image) RoundInt( (double)(RGB_TO_XYZ_MATRIX[0][0] * R[i])
								  + (double)(RGB_TO_XYZ_MATRIX[0][1] * G[i])
								  + (double)(RGB_TO_XYZ_MATRIX[0][2] * B[i]) );

		(*Y)[i] = (image) RoundInt( (double)(RGB_TO_XYZ_MATRIX[1][0] * R[i])
								  + (double)(RGB_TO_XYZ_MATRIX[1][1] * G[i])
								  + (double)(RGB_TO_XYZ_MATRIX[1][2] * B[i]) );

		(*Z)[i] = (image) RoundInt( (double)(RGB_TO_XYZ_MATRIX[2][0] * R[i])
								  + (double)(RGB_TO_XYZ_MATRIX[2][1] * G[i])
								  + (double)(RGB_TO_XYZ_MATRIX[2][2] * B[i]) );
	}
}


void ConvertXYZ2RGB(image *X, image *Y, image *Z, image **R, image **G, image **B, int width, int height){
	int i;

	(*R) = (image *) malloc(sizeof(image)*width*height);
	(*G) = (image *) malloc(sizeof(image)*width*height);
	(*B) = (image *) malloc(sizeof(image)*width*height);

	for (i=0;i<width*height;i++){
		(*R)[i] = (image) RoundInt( (double)(XYZ_TO_RGB_MATRIX[0][0] * X[i])
								  + (double)(XYZ_TO_RGB_MATRIX[0][1] * Y[i])
								  + (double)(XYZ_TO_RGB_MATRIX[0][2] * Z[i]) );

		(*G)[i] = (image) RoundInt( (double)(XYZ_TO_RGB_MATRIX[1][0] * X[i])
								  + (double)(XYZ_TO_RGB_MATRIX[1][1] * Y[i])
								  + (double)(XYZ_TO_RGB_MATRIX[1][2] * Z[i]) );

		(*B)[i] = (image) RoundInt( (double)(XYZ_TO_RGB_MATRIX[2][0] * X[i])
								  + (double)(XYZ_TO_RGB_MATRIX[2][1] * Y[i])
								  + (double)(XYZ_TO_RGB_MATRIX[2][2] * Z[i]) );
	}
}


/*---------------------------------------------------------------------------
// XYZ <=> Lab transform
*/

void ConvertXYZ2Lab(image *X, image *Y, image *Z, image **L, image **a, image **b, int width, int height){
	int i;
	double Xn, Yn, Zn;
  double tx, ty, tz;
  double ftx, fty, ftz;
	double L_tmp, a_tmp, b_tmp;
	short k = 10;
	
	
	/*image max_L = 0;
	image max_a = 0;
	image max_b = 0;*/

	(*L) = (image *) malloc(sizeof(image)*width*height);
	(*a) = (image *) malloc(sizeof(image)*width*height);
	(*b) = (image *) malloc(sizeof(image)*width*height);


	Xn = ( RGB_TO_XYZ_MATRIX[0][0] + RGB_TO_XYZ_MATRIX[0][1] + RGB_TO_XYZ_MATRIX[0][2] ) * 255;
	Yn = ( RGB_TO_XYZ_MATRIX[1][0] + RGB_TO_XYZ_MATRIX[1][1] + RGB_TO_XYZ_MATRIX[1][2] ) * 255;
	Zn = ( RGB_TO_XYZ_MATRIX[2][0] + RGB_TO_XYZ_MATRIX[2][1] + RGB_TO_XYZ_MATRIX[2][2] ) * 255;

	for (i=0;i<width*height;i++)
  {
		tx = (double)(X[i]) / Xn;
		ty = (double)(Y[i]) / Yn;
		tz = (double)(Z[i]) / Zn;

		if (tx > 0.008856)
			ftx = pow(tx, 0.3333333);
		else
			ftx = 7.7787*tx + 16/116;

		if (ty > 0.008856){
			fty = pow(ty, 0.3333333);
			L_tmp = 116*pow(ty, 0.3333333) - 16;
		}
		else {
			fty = 7.7787*ty + 16/116;
			L_tmp = 903.3*ty;
		}

		if (tz > 0.008856)
			ftz = pow(tz, 0.3333333);
		else
			ftz = 7.7787*tz + 16/116;

		a_tmp = 500*(ftx-fty);
		b_tmp = 200*(fty-ftz);

		(*L)[i] = (image) RoundInt(L_tmp*k);
		(*a)[i] = (image) RoundInt(a_tmp*k);
		(*b)[i] = (image) RoundInt(b_tmp*k);
	}
}

void ConvertLab2XYZ(image *L, image *a, image *b, image **X, image **Y, image **Z, int width, int height){
	int i;
	double Xn, Yn, Zn;
	double tx, tz;
	double ftx, ftz;
	double L_tmp, a_tmp, b_tmp;
	double X_tmp, Y_tmp, Z_tmp;
	short k = 10;

	(*X) = (image *) malloc(sizeof(image)*width*height);
	(*Y) = (image *) malloc(sizeof(image)*width*height);
	(*Z) = (image *) malloc(sizeof(image)*width*height);


	Xn = ( RGB_TO_XYZ_MATRIX[0][0] + RGB_TO_XYZ_MATRIX[0][1] + RGB_TO_XYZ_MATRIX[0][2] ) * 255;
	Yn = ( RGB_TO_XYZ_MATRIX[1][0] + RGB_TO_XYZ_MATRIX[1][1] + RGB_TO_XYZ_MATRIX[1][2] ) * 255;
	Zn = ( RGB_TO_XYZ_MATRIX[2][0] + RGB_TO_XYZ_MATRIX[2][1] + RGB_TO_XYZ_MATRIX[2][2] ) * 255;

	for (i=0;i<width*height;i++){
		L_tmp = (double)(L[i]) / k;
		a_tmp = (double)(a[i]) / k;
		b_tmp = (double)(b[i]) / k;

		tx = a_tmp/500 + (L_tmp+16)/116;
		tz = (L_tmp+16)/116 - b_tmp/200;

		if (tx > 0.207)
			ftx = pow(tx, 3);
		else
			ftx = (116*tx-16) / 903.3;

		if (tz > 0.207)
			ftz = pow(tz, 3);
		else
			ftz = (116*tz-16) / 903.3;

		X_tmp = Xn*ftx;
		if (L_tmp > 8)
			Y_tmp = Yn*pow((L_tmp+16)/116, 3);
		else
			Y_tmp = Yn*L_tmp / 903.3;
		Z_tmp = Zn*ftz;

		(*X)[i] = (image) RoundInt(X_tmp);
		(*Y)[i] = (image) RoundInt(Y_tmp);
		(*Z)[i] = (image) RoundInt(Z_tmp);
	}
}

/*---------------------------------------------------------------------------
// RGB <=> Lab transform
*/

void ConvertRGB2Lab(image *R, image *G, image *B, image **L, image **a, image **b, int width, int height){
	image *X, *Y, *Z;

	ConvertRGB2XYZ(R, G, B, &X, &Y, &Z, width,height);
	ConvertXYZ2Lab(X, Y, Z, L, a, b, width, height);
	free(X); free(Y); free(Z);
}

void ConvertLab2RGB(image *L, image *a, image *b, image **R, image **G, image **B, int width, int height){
	image *X, *Y, *Z;

	ConvertLab2XYZ(L, a, b, &X, &Y, &Z, width, height);
	ConvertXYZ2RGB(X, Y, Z, R, G, B, width, height);
	free(X); free(Y); free(Z);
}
