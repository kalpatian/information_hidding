/*----------------------------------------------------------------------------
// StirMark Benchmark - main.c
//
// Contents: Program entry point for the self similarities attack
//
// Purpose:  This can be used to compile the self similarities attack as
//           a standalone progam
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/main.c,v 1.3 2002/04/19 10:23:59 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#define SS_EXE

#ifdef WIN32
/* Memory leak detection
// Technical article: Edward Wright, "Detecting and Isolating Memory Leaks
// Using Microsoft Visual C++", MSDN, Microsoft Corporation, May 1999
*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif /* WIN32 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "SelfSimilarities.h"
#include "compil.h"
#include "imgio.h"



/*--------------------------------------------------------------------------------*
 | This function displays on the screen the version info of the attack.           |
 *--------------------------------------------------------------------------------*/

void printVersion(){
	printf("*-----------------------------------------------------------------*\n");
	printf("| Attack for watermarked images using self-similarities.          |\n");
	printf("| Version 0.1 (released March 2002)                               |\n");
	printf("| Company: Eurecom Institute, France.                             |\n");
	printf("| Authors: G. Doerr, G. Csurka, C. Rey, J.-L. Dugelay,            |\n");
	printf("|          C. Mallauran, J.-P. Nguyen.                            |\n");
	printf("| Companion paper: Internal Report RR-02-60.                      |\n");
	printf("|                  Downloadable from http://www.eurecom.fr/~image |\n");
	printf("*-----------------------------------------------------------------*\n\n");
}


/*--------------------------------------------------------------------------------*
 | This function displays on the screen how to use the .exe                       |
 *--------------------------------------------------------------------------------*/

void printUsage(){
	printVersion();

	printf("Usage: ");
	printf("attack <origFilename> <waterFilename> <colorSpace>:<channels> <typeAttack> [<percent>]\n");
	printf("  <origFilename>: image for IFS codebook in Portable Pixelmap  \"*.ppm\"\n");
	printf("                  May be the same as <waterFilename> most of the time\n");
	printf("  <waterFilename>: watermarked image to be attacked in Portable Pixelmap  \"*.ppm\"\n");
	printf("  <colorSpace>: rgb, yuv, hsv or lab in lower case\n");
	printf("  <channels>: channels of the color space to be attacked in lower case\n");
	printf("  <typeAttack>: x for exchanging\n");
	printf("                s for spatial\n");
	printf("                h for Haar wavelets (not supported yet)\n");
	printf("  <percent>: percentage used for adaptative thresholding\n");
	printf("             Mandatory with the s or h option\n");
	printf("\nExample:\n");
	printf("   attack orig.ppm water.ppm hsv:v s (D*******)\n");
	printf("   attack orig.ppm water.ppm rgb:b s (S******)\n");
	printf("   attack orig.ppm water.ppm yuv:y s (S***S***)\n");
}


/*--------------------------------------------------------------------------------*
 | This function IFS analyze the command line.                                    |
 *--------------------------------------------------------------------------------*/

void analyzeCmd(int argNumber, char **arguments, optionsCmd *cmd){
	int i;

	/* Check good number of arguments */
	if (argNumber != 5 && argNumber != 6) {
		fprintf(stderr, "ERROR: Wrong number of arguments\n");
		printUsage();
		exit(-1);
	}

	/* Check first argument */
	cmd->origFile = (char *)malloc(sizeof(char)*(strlen(arguments[1])+1));
	strcpy(cmd->origFile, arguments[1]);

	/* Check second argument */
	cmd->waterFile = (char *)malloc(sizeof(char)*(strlen(arguments[2])+1));
	strcpy(cmd->waterFile, arguments[2]);

	/* Check the third argument */
	if (strlen(arguments[3])<5 || strlen(arguments[3])>7 || arguments[3][3]!=':'){
		fprintf(stderr,"ERROR: Wrong third argument\n");
		printUsage();
		exit(1);
	}
	else {
		/* Set the colorspace */
		if (strncmp(arguments[3],"rgb",3)==0)
			cmd->colorSpace = SS_RGB;
		else if (strncmp(arguments[3],"yuv",3)==0)
			cmd->colorSpace = SS_YUV;
		else if (strncmp(arguments[3],"hsv",3)==0)
			cmd->colorSpace = SS_HSV;
		else if (strncmp(arguments[3],"lab",3)==0)
			cmd->colorSpace = SS_LAB;
		else if (strncmp(arguments[3],"xyz",3)==0)
			cmd->colorSpace = SS_XYZ;
		else {
			fprintf(stderr,"ERROR: Color space not supported!\n");
			printUsage();
			exit(1);
		}
		/* Initialyze the attack with 0 */
		cmd->c1_flag = SS_NO_ATTACK;
		cmd->c2_flag = SS_NO_ATTACK;
		cmd->c3_flag = SS_NO_ATTACK;
		/* Looking for channels to attack */
		for (i=4;i<(int)strlen(arguments[3]);i++){
			if (cmd->colorSpace == SS_RGB){
				if (arguments[3][i]=='r')
					cmd->c1_flag = SS_ATTACK;
				else if (arguments[3][i]=='g')
					cmd->c2_flag = SS_ATTACK;
				else if (arguments[3][i]=='b')
					cmd->c3_flag = SS_ATTACK;
				else {
					fprintf(stderr,"ERROR: Channel %c does not belong to color space!\n",arguments[3][i]);
					printUsage();
					exit(1);
				}
			}
			else if (cmd->colorSpace == SS_YUV){
				if (arguments[3][i]=='y')
					cmd->c1_flag = SS_ATTACK;
				else if (arguments[3][i]=='u')
					cmd->c2_flag = SS_ATTACK;
				else if (arguments[3][i]=='v')
					cmd->c3_flag = SS_ATTACK;
				else {
					fprintf(stderr,"ERROR: Channel %c does not belong to color space!\n",arguments[3][i]);
					printUsage();
					exit(1);
				}
			}
			else if (cmd->colorSpace == SS_HSV) {
				if (arguments[3][i]=='h')
					cmd->c1_flag = SS_ATTACK;
				else if (arguments[3][i]=='s')
					cmd->c2_flag = SS_ATTACK;
				else if (arguments[3][i]=='v')
					cmd->c3_flag = SS_ATTACK;
				else {
					fprintf(stderr,"ERROR: Channel %c does not belong to color space!\n",arguments[3][i]);
					printUsage();
					exit(1);
				}
			}
			else if (cmd->colorSpace == SS_LAB) {
				if (arguments[3][i]=='l')
					cmd->c1_flag = SS_ATTACK;
				else if (arguments[3][i]=='a')
					cmd->c2_flag = SS_ATTACK;
				else if (arguments[3][i]=='b')
					cmd->c3_flag = SS_ATTACK;
				else {
					fprintf(stderr,"ERROR: Channel %c does not belong to color space!\n",arguments[3][i]);
					printUsage();
					exit(1);
				}
			}
			else if (cmd->colorSpace == SS_XYZ) {
				if (arguments[3][i]=='x')
					cmd->c1_flag = SS_ATTACK;
				else if (arguments[3][i]=='y')
					cmd->c2_flag = SS_ATTACK;
				else if (arguments[3][i]=='z')
					cmd->c3_flag = SS_ATTACK;
				else {
					fprintf(stderr,"ERROR: Channel %c does not belong to color space!\n",arguments[3][i]);
					printUsage();
					exit(1);
				}
			}
		}
	}

	/* Check the fourth argument */
	if (arguments[4][0]=='x')
		/* Exchange the colour channel of original and watermarked image */
		cmd->type = SS_SWITCH;
	else if (arguments[4][0]=='s')
		/* Dewatermarking by swappping in the spatial domain */
		cmd->type = SS_SPATIAL;
	else if (arguments[4][0]=='h'){
		/* Dewatermarking by swappping in the wavelet domain */
		/* To be implemented and tested                      */
		/* cmd->type = WAVELET;                              */
		fprintf(stderr,"ERROR: Wavelet not supported yet\n");
		printUsage();
		exit(1);
	}
	else {
		fprintf(stderr,"ERROR: Wrong fourth argument\n");
		printUsage();
		exit(1);
	}

	/* Check the fifth argument if necessary */
    if (cmd->type != SS_SWITCH){
		if (argNumber != 6){
			fprintf(stderr, "ERROR: Fifth argument mandatory in this mode\n");
			printUsage();
			exit(1);
		}
		cmd->percent = atoi(arguments[5]);
		if (cmd->percent>100 || cmd->percent<0){
			fprintf(stderr, "ERROR: Fifth argument should be between 0 and 100\n");
			printUsage();
			exit(1);
		}
	}
}


/*--------------------------------------------------------------------------------*
 | Main function.                                                                 |
 *--------------------------------------------------------------------------------*/
extern int findAdaptativeThreshold(float *array, long numSample, int percent);
int main(int argc,char **argv)
{
	optionsCmd commandLine;
	char  *attackFile;
	int w_orig, h_orig;                                      /* Size of the original image          */
	int w_water, h_water;                                    /* Size of the watermarked image       */
	image *R_orig, *G_orig, *B_orig;                         /* RGB components of original image    */
	image *R_water, *G_water, *B_water;                      /* RGB components of watermarked image */
	image *channel1_orig, *channel2_orig, *channel3_orig;
	image *channel1_water, *channel2_water, *channel3_water;
	image *R_sup, *G_sup, *B_sup;                            /* RGB support */
	image *channel1_sup, *channel2_sup, *channel3_sup;
	int maxRGB, i;


	/* Analyze the command line */
	analyzeCmd(argc, argv, &commandLine);
	printVersion();

	/* Import original file */
	printf("Reading image providing IFS codebook...\n");
	if (ReadPPM(commandLine.origFile, &w_orig, &h_orig, &maxRGB, &R_orig, &G_orig, &B_orig)==0){
		fprintf(stderr,"ERROR: File reading error!\n");
		printUsage();
		exit(1);
	}
	if (maxRGB!=255)
		ExpandLevels(R_orig, G_orig, B_orig, w_orig*h_orig, maxRGB);

	/* Import watermarked image	*/
	printf("Reading watermarked image to be attacked...\n");
	if (ReadPPM(commandLine.waterFile, &w_water, &h_water, &maxRGB, &R_water, &G_water, &B_water)==0){
		fprintf(stderr,"ERROR: File reading error!\n");
		printUsage();
		exit(1);
	}
	if (maxRGB!=255)
		ExpandLevels(R_water, G_water, B_water, w_water*h_water,maxRGB);
		
	/* Check the size of the images */
	if (w_orig!=w_water || h_orig!=h_water){
		fprintf(stderr,"ERROR: Images with different sizes\n");
		exit(1);
	}


	/******************************************************************************/

	/* Colorspace conversion if necessary */
	convertRGB2Channel(R_orig, G_orig, B_orig, &channel1_orig, &channel2_orig,
					   &channel3_orig, w_orig, h_orig, commandLine.colorSpace);
	convertRGB2Channel(R_water, G_water, B_water, &channel1_water, &channel2_water,
					   &channel3_water, w_water, h_water, commandLine.colorSpace);
	/* Free memory */
	free(R_orig);free(B_orig);free(G_orig);
	free(R_water);free(G_water);free(B_water);

	/* Attack channel 1 if necessary */
	if((channel1_sup = (image *)malloc(sizeof(image) * w_orig * h_orig))==NULL) {
		fprintf(stderr,"ERROR: Memory allocation problem!\n");
		exit(1);
	}
	if (commandLine.c1_flag == SS_ATTACK){
		printf("Channel 1:\n");
		attackChannel(channel1_orig, channel1_water, channel1_sup, w_water, h_water, &commandLine);
	}
	else {
		printf("Channel 1: Untouched.\n");
		for (i=0;i<w_water*h_water;i++)
			channel1_sup[i] = channel1_water[i];
	}
	free(channel1_orig);free(channel1_water);

	/* Attack channel 2 if necessary */
	if((channel2_sup = (image *)malloc(sizeof(image) * w_orig * h_orig))==NULL) {
		fprintf(stderr,"ERROR: Memory allocation problem!\n");
		exit(1);
	}
	if (commandLine.c2_flag == SS_ATTACK){
		printf("Channel 2:\n");
		attackChannel(channel2_orig, channel2_water, channel2_sup, w_water, h_water, &commandLine);
	}
	else {
		printf("Channel 2: Untouched.\n");
		for (i=0;i<w_water*h_water;i++)
			channel2_sup[i] = channel2_water[i];
	}
	free(channel2_orig);free(channel2_water);

	/* Attack channel 3 if necessary */
	if((channel3_sup = (image *)malloc(sizeof(image) * w_orig * h_orig))==NULL) {
		fprintf(stderr,"ERROR: Memory allocation problem!\n");
		exit(1);
	}
	if (commandLine.c3_flag == SS_ATTACK){
		printf("Channel 3:\n");
		attackChannel(channel3_orig, channel3_water, channel3_sup, w_water, h_water, &commandLine);
	}
	else {
		printf("Channel 3: Untouched.\n");
		for (i=0;i<w_water*h_water;i++)
			channel3_sup[i] = channel3_water[i];
	}
	free(channel3_orig);free(channel3_water);

	/* Colorspace conversion if necessary */
	convertChannel2RGB(channel1_sup, channel2_sup, channel3_sup, &R_sup,
					   &G_sup, &B_sup, w_water, h_water, commandLine.colorSpace);
	/* Free memory */
	free(channel1_sup);free(channel2_sup);free(channel3_sup);

	/******************************************************************************/


	/* Save output */
	attackFile  = (char *)malloc(sizeof(char)*(strlen(commandLine.waterFile)+strlen("_attack")+1));
	strcpy(attackFile, commandLine.waterFile);
	attackFile[strlen(commandLine.waterFile)-4] = 0;
	strcat(attackFile, "_attack.ppm");
	printf("Saving attacked image in \"%s\"\n",attackFile);
	WritePPM(attackFile, w_orig, h_orig, 255, R_sup, G_sup, B_sup);		

	/* Fre memory */
	free(attackFile);
	free(R_sup);free(G_sup);free(B_sup);
  free(commandLine.origFile);
  free(commandLine.waterFile);
}

