/*----------------------------------------------------------------------------
// StirMark Benchmark - imgio.c
//
// Contents: Read write functions for PPM images
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/SignalProcessing/SelfSimilarities/imgio.c,v 1.2 2002/04/19 10:23:58 petitcolas Exp $ 
//----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "compil.h"
#include "imgio.h"
#define ERROR 0
#define SUCCESS 1


/******************************************************************/

image * readPGM(char *name,unsigned *width,unsigned *height)
{
  unsigned position;
  unsigned imageSize,levels;
  int  magic,number,currentCHAR;
  image *retimage;
  FILE *imageID;

  char Debugchar[5];
  
  if((imageID=fopen(name,"rb"))==0) 
  {
		fprintf(stderr,"Impossible d'ouvrir le fichier %s\n",name);
    exit(1);
  }
   
  if (((magic=getc(imageID))!='P') || ((number=getc(imageID))!= '5'))
		fprintf(stderr,"Version inconnue de fichier PPM");
        
	if ((currentCHAR=getc(imageID))!='\n')
		fprintf(stderr,"fichier deteriore\n");

  while ((currentCHAR=getc(imageID))=='#')
	while ((currentCHAR=getc(imageID))!='\n') {} 

  fseek(imageID,ftell(imageID)-1,SEEK_SET);
  fscanf(imageID,"%s",Debugchar);
  *width=atoi(Debugchar);
  currentCHAR=getc(imageID);
  fscanf(imageID,"%s",Debugchar);
  *height=atoi(Debugchar);

  /*fread(height,sizeof(unsigned),1,imageID);*/
  imageSize=(*width)*(*height);
   
  fscanf(imageID,"%s",Debugchar);
  levels=atoi(Debugchar);

  if((currentCHAR=getc(imageID))!='\n')
                fprintf(stderr,"fichier deteriore\n");

  position=ftell(imageID);

  retimage=(image *)(malloc(sizeof(image)*imageSize));
  fread(retimage,sizeof(image)*imageSize,1,imageID);
        return(retimage);
}


/*-----------------------------------------------------------------------*/

void writePGM(char *name,image *imageDATA,unsigned width,unsigned height)
{
        FILE *imageID;
        
  if((imageID=fopen(name,"wb"))==0)
  {
                fprintf(stderr,"Impossible d'ouvrir le fichier %s\n",name);
    exit(1);
  }

  fputs("P5\n",imageID);
  fputs("# Portable GrayMap file format\n",imageID);
  fputs("# IFS and SECURITY project\n",imageID);
  fputs("# S. ROCHE Eurecom Institute France\n",imageID);
  fputs("# Janv 97\n",imageID);

  fprintf(imageID,"%u %u\n255\n",width,height);
   
  fwrite(imageDATA,sizeof(image)*width*height,1,imageID);

  fclose(imageID);
}


/*-----------------------------------------------------------------------*/

image * readRAW(char *name,int data_type,unsigned width,unsigned height)
{
        unsigned imageSize;
  unsigned loop;
  image *retimage, *p_retimage;
  unsigned char  *imageUC;

  FILE *imageID;
  
  if((imageID=fopen(name,"rb"))==0) {
                fprintf(stderr,"Impossible d'ouvrir le fichier %s\n",name);
    exit(1);
        }
   
  imageSize = width * height;
  
  if((retimage =(image*)malloc(sizeof(image)*imageSize))==NULL)
                fprintf(stderr,"Probleme d'allocation memoire\n");

        switch (data_type) 
  {
                case sizeof(unsigned char) :
                                if((imageUC = (unsigned char *)malloc(sizeof(unsigned char)*imageSize))==NULL)
                                        fprintf(stderr,"Probleme d'allocation memoire\n");
          
        fread(imageUC,sizeof(unsigned char)*imageSize,1,imageID);
                        
        for(loop=0, p_retimage=retimage; loop < imageSize;loop++, p_retimage++, imageUC++){
                                        *p_retimage = (int)(*imageUC);
                                }
    /*    free(imageUC);*/
                                break;
                
                case sizeof(int) :
                                fread(retimage,sizeof(int)*imageSize,1,imageID);
        break;
        }     
  return(retimage);
}

/*-----------------------------------------------------------------------*/

void writeRAW(char *name,image *imageDATA, int data_type, unsigned width,\
              unsigned height)
{
  FILE *imageID;
  unsigned loop;
  unsigned char * p_imageDATA;
        
  if((imageID=fopen(name,"wb"))==0) {
                fprintf(stderr,"Impossible d'ouvrir le fichier %s\n",name);
    exit(1);
  }

  p_imageDATA = (unsigned char *)malloc(sizeof(unsigned char)*width*height);
  switch (data_type) {
                case sizeof(unsigned char) :
                         for(loop=0; loop < (width*height);loop++) 
       {
                                 if (imageDATA[loop] > 255)
                                         p_imageDATA[loop] = 255;
         else if (imageDATA[loop] < 0)
           p_imageDATA[loop] = 0;
         else
           p_imageDATA[loop] = (unsigned char)imageDATA[loop];
       }
       
                         fwrite(p_imageDATA,sizeof(unsigned char)*width*height,1,imageID);
       break;
       
                case sizeof(int) :
                         fwrite(imageDATA,sizeof(int)*width*height,1,imageID);
       break;
        }
  fclose(imageID);
}

/******************************************************************************/

int ReadPPM (char *filein_name, int *xsize, int *ysize, int *maxrgb,
        image **rarray, image **garray, image **barray ) 
{

  FILE *filein;
  int   numbytes;
  int   result;

  filein = fopen ( filein_name, "rb" );

  if ( filein == NULL ) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  Cannot open the input file %s.\n", filein_name );
    return ERROR;
  }

  /* Read the header.*/
  result = ppmb_read_header ( filein, xsize, ysize, maxrgb );

  if ( result == ERROR ) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  PPMB_READ_HEADER failed.\n" );
    return ERROR;
  }

/* Allocate storage for the data. */
  numbytes = (*xsize)*(*ysize)*sizeof (image);

  *rarray = (image*)malloc(numbytes);

  if ( *rarray == NULL ) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  Unable to allocate memory for data.\n" );
    printf ( "  Seeking %d bytes.\n", numbytes );
    return ERROR;
  }

  *garray = (image*)malloc(numbytes);

  if ( *garray == NULL ) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  Unable to allocate memory for data.\n" );
    printf ( "  Seeking %d bytes.\n", numbytes );
    return ERROR;
  }

  *barray = (image*)malloc(numbytes);

  if (*barray == NULL) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  Unable to allocate memory for data.\n" );
    printf ( "  Seeking %d bytes.\n", numbytes );
    return ERROR;
  }

/* Read the data. */
  result = ppmb_read_data ( filein, *xsize, *ysize, *rarray, *garray, *barray );

  if ( result == ERROR ) {
    printf ( "\n" );
    printf ( "PPMB_READ: Fatal error!\n" );
    printf ( "  PPMB_READ_DATA failed.\n" );
    return ERROR;
  }

/* Close the file. */
  fclose ( filein );

  return SUCCESS;
}

/******************************************************************************/

int ppmb_read_data ( FILE *filein, int xsize, int ysize, image *rarray, 
        image *garray, image *barray ) 
{
  int   i;
  int   int_val;
  image  *indexb;
  image  *indexg;
  image  *indexr;
  int   j;
  int   k;
  int   numval;

  indexr = rarray;
  indexg = garray;
  indexb = barray;
  numval = 0;

  for ( j = 0; j < ysize; j++ ) {
    for ( i = 0; i < xsize; i++ ) {

      for ( k = 0; k < 3; k++ ) {

        int_val = fgetc ( filein );

        if ( int_val == EOF ) {
          printf ( "\n" );
          printf ( "PPMB_READ_DATA: Failed reading data byte %d.\n", numval );
          return ERROR;
        }
        else {
          if ( k == 0 ) {
            *indexr = int_val;
            indexr = indexr + 1;
          }
          else if ( k == 1 ) {
            *indexg = int_val;
            indexg = indexg + 1;
          }
          else if ( k == 2 ) {
            *indexb = int_val;
            indexb = indexb + 1;
          }
        }
        numval = numval + 1;
      }
    }
  }
  return SUCCESS;
}
/******************************************************************************/

int ppmb_read_header ( FILE *filein, int *xsize, int *ysize, int *maxrgb ) 
{
  int   c_val;
  int   count;
  int   flag;
  int   nchar;
  int   state;
  char  string[80];

  state = 0;
  nchar = 0;

  for ( ;; ) {

    c_val = fgetc ( filein );

    if ( c_val == EOF ) {
      return ERROR;
    }

    if (c_val == '#')
    {
                        while (c_val !='\n') c_val = fgetc ( filein );
      c_val = fgetc ( filein );
    }

/*  If not whitespace, add the character to the current string.*/

    flag = isspace ( c_val );

    if ( !flag ) {
      string[nchar] = c_val;
      nchar = nchar + 1;
    }

/* See if we have finished an old item, or begun a new one. */
    if ( state == 0 ) {
      if ( !flag ) {
        state = 1;
      }
      else {
        return ERROR;
      }
    }
    else if ( state == 1 ) {
      if ( flag ) {
        string[nchar] = 0;
        nchar = nchar + 1;
        if ( strcmp ( string, "P6" ) != 0 && strcmp ( string, "p6" ) != 0 ) {
          printf ( "\n" );
          printf ( "PPMB_READ_HEADER: Fatal error.\n" );
          printf ( "  Bad magic number = %s.\n", string );
          return ERROR;
        }
        nchar = 0;
        state = 2;
      }
    }
    else if ( state == 2 ) {
      if ( !flag ) {
        state = 3;
      }
    }
    else if ( state == 3 ) {
      if ( flag ) {
        string[nchar] = 0;
        nchar = nchar + 1;
        count = sscanf ( string, "%d", xsize );
        if ( count == EOF ) {
          return ERROR;
        }
        nchar = 0;
        state = 4;
      }
    }
    else if ( state == 4 ) {
      if ( !flag ) {
        state = 5;
      }
    }
    else if ( state == 5 ) {
      if ( flag ) {
        string[nchar] = 0;
        nchar = nchar + 1;
        count = sscanf ( string, "%d", ysize );
        if ( count == EOF ) {
          return ERROR;
        }
        nchar = 0;
        state = 6;
      }
    }
    else if ( state == 6 ) {
      if ( !flag ) {
        state = 7;
      }
    }
    else if ( state == 7 ) {
      if ( flag ) {
        string[nchar] = 0;
        nchar = nchar + 1;
        count = sscanf ( string, "%d", maxrgb );
        if ( count == EOF ) {
          return ERROR;
        }
        nchar = 0;
        return SUCCESS;
      }
    }
  }
}


/******************************************************************************/

int WritePPM ( char *fileout_name, int xsize, int ysize, int maxrgb,
        image *rarray, image *garray, image *barray ) 
{

  FILE *fileout;
  int   result;

/* Open the output file.*/
  fileout = fopen ( fileout_name, "wb" );

  if ( fileout == NULL ) {
    printf ( "\n" );
    printf ( "PPMB_WRITE: Fatal error!\n" );
    printf ( "  Cannot open the output file %s.\n", fileout_name );
    return ERROR;
  }

/* Write the header. */
  result = ppmb_write_header ( fileout, xsize, ysize, maxrgb );

  if ( result == ERROR ) {
    printf ( "\n" );
    printf ( "PPMB_WRITE: Fatal error!\n" );
    printf ( "  PPMB_WRITE_HEADER failed.\n" );
    return ERROR;
  }

/* Write the data. */
  result = ppmb_write_data ( fileout, xsize, ysize, rarray, garray, barray );

  if ( result == ERROR ) {
    printf ( "\n" );
    printf ( "PPMB_WRITE: Fatal error!\n" );
    printf ( "  PPMB_WRITE_DATA failed.\n" );
    return ERROR;
  }

/* Close the file. */
  fclose ( fileout );

  return SUCCESS;
}

/******************************************************************************/

int ppmb_write_data ( FILE *fileout, int xsize, int ysize, image *rarray, image *garray, image *barray ) 
{
  int  i;
  image *indexb;
  image *indexg;
  image *indexr;
  int  j;

  indexr = rarray;
  indexg = garray;
  indexb = barray;

  for ( j = 0; j < ysize; j++ ) {
    for ( i = 0; i < xsize; i++ ) {
      if (*indexr>255) fputc(255,fileout);
                        else if (*indexr<0) fputc(0,fileout);
      else fputc ( *indexr, fileout );
      
      if (*indexg>255) fputc(255,fileout);
      else if (*indexg<0) fputc(0,fileout);
      else fputc ( *indexg, fileout );
      
      if (*indexb>255) fputc(255,fileout);
      else if (*indexb<0) fputc(0,fileout);
      else fputc ( *indexb, fileout );
      
      indexr = indexr + 1;
      indexg = indexg + 1;
      indexb = indexb + 1;
    }
  }
  return SUCCESS;
}

/******************************************************************************/

int ppmb_write_header ( FILE *fileout, int xsize, int ysize, int maxrgb ) 
{

  fprintf ( fileout, "P6\n%d %d\n%d\n", xsize, ysize, maxrgb );
        return SUCCESS;
}
