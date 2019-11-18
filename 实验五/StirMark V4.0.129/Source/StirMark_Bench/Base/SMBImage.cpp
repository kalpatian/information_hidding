/////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBImage.cpp
//
// Contents: Implementation of the CSMBImage class.
//
// Purpose:  See SMBImage.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, March 2000
//
// Modified: Nazim Fatès, Microsoft Research
//           Frédéric Raynal, INRIA
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBImage.cpp,v 1.23 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



#if _MSC_VER > 1000
#pragma once
#pragma warning (push)
#pragma warning (disable: 4290 4100 4511 4514 4512 4710)
#endif // _MSC_VER > 1000

// STL headers

// Other standard headers
#include <assert.h>
#include <setjmp.h>   // for the JPEG functions
#ifdef WIN32
#include <stdio.h>
#define snprintf _snprintf
#endif // WIN32

// SMB Headers
#include "SMBImage.h"

// JPEGLib headers
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "../../JPEGLib/jpeglib.h"
#include "../../JPEGLib/cdjpeg.h"
#include "../../JPEGLib/jpegint.h"

#ifdef __cplusplus
}
#endif // __cplusplus






//////////////////////////////////////////////////////////////////////
// Construction / desctruction
//////////////////////////////////////////////////////////////////////

CSMBImage::CSMBImage()
{
  // The default constructor just creates an empty image
  m_imgValue.pgData = 0;
  Clear();
}

#ifdef _DEBUG
CSMBImage::CSMBImage(const CSMBImage& in_other)
{
  SMBWarning(TString("[CSMBImage::CSMBImage] - Copy contructor should not be used - ")
             + in_other.m_strBaseName);
} 
#endif


CSMBImage::~CSMBImage()
{
  Clear();
}


//////////////////////////////////////////////////////////////////////
// Initialisation and copy
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Reset the object by clearing the memory, setting size of the image
// to zero and using default values for other members.
void CSMBImage::Clear(void)
{
  delete []m_imgValue.pgData;
  if (m_imgValue.pgData)
    SMBInformation(TString("  > Image data cleared (") + TString(m_imgValue.pgData) + ")\n", 2);

  m_imgValue.pgData    = 0;
  m_imgValue.lSize     = 0;
  m_nSize              = 0;

  m_imgValue.nCols     = 0;
  m_imgValue.nRows     = 0;
  
  m_imgValue.nChannels = 3;
  m_imgValue.itType    = IT_RGB;
  m_imgValue.gBrdValue = 0;
  m_imgValue.gMaxVal   = 255;
  m_imgValue.bmMode    = SMB_DEFAULT_BORDER_MODE;  // Default mode for images
  m_strBaseName        = SMB_DEFAULT_IMAGE_NAME;
}


//////////////////////////////////////////////////////////////////////
// The Initialise function allocate the memory for an image of
// given size and type
void CSMBImage::Initialise(uint                     in_nCols,
                           uint                     in_nRows,
                           Gray                     in_gMaxVal,
                           ImageType                in_itType,
                           CSMBMemoryException & inout_exception)
                           throw (CSMBMemoryException *)
{
  Clear();

  m_imgValue.itType    = in_itType;
  m_imgValue.nChannels = (in_itType == IT_GRAY) ? 1 : 3;
  m_imgValue.gMaxVal   = in_gMaxVal;

  if ((in_nCols == 0) || (in_nRows == 0))
  {
    m_imgValue.nCols  = 0;
    m_imgValue.nRows  = 0;
  }
  else
  {
    m_imgValue.nCols = in_nCols;
    m_imgValue.nRows = in_nRows;

    if ((m_imgValue.nCols > SMB_DEFAULT_MAX_IMAGE_WIDTH) ||
        (m_imgValue.nRows > SMB_DEFAULT_MAX_IMAGE_HEIGHT))
    {
      Clear();
      inout_exception.Throw(CSMBMemoryException::imageTooLarge);
    }

    m_nSize = m_imgValue.nCols * m_imgValue.nRows * m_imgValue.nChannels;
    m_imgValue.lSize = m_nSize * sizeof(Gray);

    m_imgValue.pgData = new Gray[m_nSize];
    if (m_imgValue.pgData == 0)
    {
      Clear();
      inout_exception.Throw(CSMBMemoryException::outOfMemory);
    }

    SMBInformation(TString("  > Image data allocated (") + TString(m_imgValue.pgData) + ")\n", 2);
  }
}


//////////////////////////////////////////////////////////////////////
// Initialise the current image with the same parameters as a source image
// but with a different size
void CSMBImage::InitialiseFrom(const CSMBImage &        in_imgSource,
                               CSMBMemoryException & inout_exception,
                               uint                     in_nCols,
                               uint                     in_nRows)
                               throw (CSMBMemoryException *)
{
  assert(IsValid());
  assert(in_imgSource.IsValid());

  Initialise(in_nCols,
             in_nRows, 
             in_imgSource.GetMaxVal(), 
             in_imgSource.GetImageType(),
             inout_exception);
  SetBaseName(in_imgSource.m_strBaseName);
}


//////////////////////////////////////////////////////////////////////
// Initialise the current image with the same parameters as a source image
void CSMBImage::InitialiseFrom(const CSMBImage &        in_imgSource,
                               CSMBMemoryException & inout_exception)
                               throw (CSMBMemoryException *)
{
  assert(IsValid());
  assert(in_imgSource.IsValid());

  Initialise(in_imgSource.NumberOfColumns(), 
             in_imgSource.NumberOfRows(), 
             in_imgSource.GetMaxVal(), 
             in_imgSource.GetImageType(),
             inout_exception);
  SetBaseName(in_imgSource.m_strBaseName);
} 


//////////////////////////////////////////////////////////////////////
// Copy method (the copy constructor is disabled)
void CSMBImage::CopyFrom(const CSMBImage &        in_imgSource,
                         CSMBMemoryException & inout_exception)
                         throw (CSMBMemoryException *)
{
  assert(IsValid());
  assert(in_imgSource.IsValid());

  // 'this' may already contain an image...
  delete []m_imgValue.pgData;
  if (m_imgValue.pgData)
    SMBInformation(TString("  > Image data cleared (") + TString(m_imgValue.pgData) + ")\n", 2);

  m_imgValue.pgData = 0;
  m_imgValue        = in_imgSource.m_imgValue;
  m_nSize = m_imgValue.nCols * m_imgValue.nRows * m_imgValue.nChannels;
  assert(m_imgValue.lSize == m_nSize * sizeof(Gray));
  if (m_nSize != 0)
  {
    m_imgValue.pgData = new Gray[m_nSize];
    if (m_imgValue.pgData == 0)
    {
      m_nSize = 0;
      m_imgValue.lSize = 0;
      inout_exception.Throw(CSMBMemoryException::outOfMemory);
    }
    SMBInformation(TString("  > Image data allocated (") + TString(m_imgValue.pgData) + ")\n", 2);
  }
  
  memcpy(m_imgValue.pgData,
         in_imgSource.m_imgValue.pgData,
         m_nSize * sizeof(Gray));
  
  // We also have to copy the name of the image
  SetBaseName(in_imgSource.m_strBaseName);
}


//////////////////////////////////////////////////////////////////////
// Special functions
//////////////////////////////////////////////////////////////////////

void CSMBImage::ExtractRegion(uint         in_xOrigin,
                              uint         in_yOrigin,
                              CSMBImage & out_region) const
{
  assert(out_region.IsValid());

  for (uint i = 0; i < out_region.NumberOfColumns(); i++)
    for (uint j = 0; j < out_region.NumberOfRows(); j++)
      for (uint k = 0; k < out_region.NumberOfChannels(); k++)
        out_region.SetPixel(i, j, k, GetPixel(i + in_xOrigin,
                                              j + in_yOrigin,
                                              k)
                            );
}


//////////////////////////////////////////////////////////////////////
// Member acces functions
//////////////////////////////////////////////////////////////////////


Gray CSMBImage::GetPixelLuminance(int in_x, int in_y) const
{
  if (m_imgValue.nChannels == 1)
    return GetPixel(in_x, in_y, 0);
  else
  {
    assert(m_imgValue.nChannels == 3);
    return (Gray)(0.299 * GetPixel(in_x, in_y, 0) + 
                  0.587 * GetPixel(in_x, in_y, 1) +
                  0.114 * GetPixel(in_x, in_y, 2));

  }
}


Gray CSMBImage::GetPixel(int in_x, int in_y, uint in_c /* = 0 */) const
{
  int x = in_x, y = in_y;

 
  assert(in_c < m_imgValue.nChannels);

  if (x < 0 || x >= (int)m_imgValue.nCols ||
      y < 0 || y >= (int)m_imgValue.nRows)
  {
    switch (m_imgValue.bmMode)
    {
    case (BM_CONSTANT): // A constant value is used for the border 
      return (m_imgValue.gBrdValue);

    case (BM_REPLICATION): // The last row or column is replicated for the border
      if (x < 0) x = 0;
      if (x >= (int)m_imgValue.nCols) x = (int)m_imgValue.nCols - 1;
      if (y < 0) y = 0;
      if (y >= (int)m_imgValue.nRows) y = (int)m_imgValue.nRows - 1;
      break;

    case (BM_WARPING): // The row or column of the opposite side is used
      if (x < 0) x = (x % (int)m_imgValue.nCols) + (int)m_imgValue.nCols;
      if (x >= (int)m_imgValue.nCols) x = x % m_imgValue.nCols;
      if (y < 0) y = (y % (int)m_imgValue.nRows) + (int)m_imgValue.nRows;
      if (y >= (int)m_imgValue.nRows) y = y % (int)m_imgValue.nRows;
      break;

    case (BM_REFLECTION): // Rows or columns are reflected in reverse order
      if (x < 0) x = 0 - (x % (int)m_imgValue.nCols);
      if (x >= (int)m_imgValue.nCols) x = m_imgValue.nCols - (x % (int)m_imgValue.nCols) - 1;
      if (y < 0) y = 0 - (y % (int)m_imgValue.nRows); 
      if (y >= (int)m_imgValue.nRows) y = (int)m_imgValue.nRows - (y % (int)m_imgValue.nRows) - 1;
      break;

    default:
      SMBThrowNewException("[CSMBImage::GetPixel] - Setting for border mode is incorrect.");
      break;
    }
  }

  // Change origin from bottom left to top left
  y = m_imgValue.nRows - y - 1;
  
  assert((x >= 0) && (x < (int)m_imgValue.nCols));
  assert((y >= 0) && (y < (int)m_imgValue.nRows));

  return (  m_imgValue.pgData[in_c
          + m_imgValue.nChannels * (y * m_imgValue.nCols + x)]);

}


Gray  CSMBImage::operator()(int in_x, int in_y, uint in_c /* = 0 */) const
{
  return GetPixel(in_x, in_y, in_c);
}


void CSMBImage::SetPixel(uint in_x, uint in_y, uint in_c, Gray in_val)
{
  if(!IsInBounds(in_x, in_y, in_c))
     SMBWarning("[CSMBImage::SetPixel] - Pixel coordinates outside the boundaries. No value set.");

  // Change origin from bottom left to top left
  uint x = in_x; 
  uint y = m_imgValue.nRows - in_y - 1;

  if (in_val > m_imgValue.gMaxVal)
    in_val = m_imgValue.gMaxVal;

  // Set the new value
  m_imgValue.pgData[in_c +
                    m_imgValue.nChannels * (y * m_imgValue.nCols + x)] = in_val;
}


void CSMBImage::SetBaseName(TCString &in_strImageName)
{
  if (in_strImageName.empty())
    m_strBaseName = SMB_DEFAULT_IMAGE_NAME;
  else
    m_strBaseName = in_strImageName;
}


//////////////////////////////////////////////////////////////////////
// I/O methods
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Load image from file. Supports only PPM, JPEG and BMP formats.
// Decision of the format is based on the file name extension.
void CSMBImage::Load(TCString in_strFilePath)
throw (CSMBException *)
{
  assert(IsValid());

  if (in_strFilePath.empty())
    throw new CSMBFileException(CSMBFileException::invalidFileName, in_strFilePath);

  TString strFileExtension = in_strFilePath.GetExtension();

  if ((strFileExtension.compare(".ppm") == 0) || // Portable pixel map
      (strFileExtension.compare(".pgm") == 0))   // Portable graymap
  {
    // Open file for reading
#ifdef WIN32
    ifstream inStream(in_strFilePath, ios::binary);
#else
    ifstream inStream(in_strFilePath);
#endif // WIN32

    if (!inStream.good())
      throw new CSMBFileException(CSMBFileException::fileNotFound, in_strFilePath);

    // This may throw a CSMBFileException or a CSMBMemoryException
    // Shoud be catched by the caller of CSMBImage::Load
    ReadPPM(inStream);
  }
  else if ((strFileExtension.compare(".jpeg") == 0) || // JPEG
           (strFileExtension.compare(".jpg")  == 0) ||
           (strFileExtension.compare(".bmp")  == 0))   // BMP
  {
    FILE* pinStream = fopen(in_strFilePath, "rb");

    if (pinStream == 0)
      throw new CSMBFileException(CSMBFileException::fileNotFound, in_strFilePath);
      
    if (strFileExtension.compare(".bmp") == 0) // BMP
      ReadBMP(pinStream);
    else  // JPEG
      ReadJPEG(pinStream);

    if (fclose(pinStream) == EOF)
      throw new CSMBFileException(CSMBFileException::closeError, in_strFilePath);
  }
  else
    throw new CSMBFileException(CSMBFileException::unsupportedFileFormat, in_strFilePath);

  SetBaseName(in_strFilePath.GetBaseName());
}


//////////////////////////////////////////////////////////////////////
// Save the image to file. Extension is automatically added to file name
// if missing. Extension is based on the format.
void CSMBImage::Save(TString  in_strFilePath,
                     TCString in_strFileFormat,
                     uint     in_JPEGQuality /* =90 */) const
                     throw (CSMBFileException *)
{
  assert(IsValid());
  if (m_imgValue.itType != IT_GRAY && m_imgValue.itType != IT_RGB)
    throw new CSMBFileException(CSMBFileException::unsupportedFileFormat, in_strFilePath);

  if (in_strFilePath.empty())
    throw new CSMBFileException(CSMBFileException::invalidFileName, in_strFilePath);

  // We check if the image is not empty
  if (m_imgValue.pgData == 0)
    SMBThrowNewException("[CSMBImage::Save] - You're trying to save an empty image.")
  
  TString strFileExtension = in_strFilePath.GetExtension();
  if (in_strFileFormat == "PPM")
  {
    // Add extension to file name if necessary
    if (NumberOfChannels() == 1)
      in_strFilePath.AddExtension(".pgm");
    else
      in_strFilePath.AddExtension(".ppm");

    // Open file for writing
#ifdef WIN32
    ofstream outStream(in_strFilePath, ios::binary);
#else
    ofstream outStream(in_strFilePath);
#endif // WIN32

    if (!outStream.good())
      throw new CSMBFileException(CSMBFileException::openError, in_strFilePath);

    // This may throw a CSMBFileException
    // Should be catched by caller of CSMBImage::Save
    WritePPM(outStream); 
  }
  else
  {
    if ((in_strFileFormat == "JPG") || (in_strFileFormat == "JPEG"))
      in_strFilePath.AddExtension(".jpg");
    else if (in_strFileFormat == "BMP")
      in_strFilePath.AddExtension(".bmp");
    else
      throw new CSMBFileException(CSMBFileException::unsupportedFileFormat, in_strFilePath);

    FILE* poutStream = fopen(in_strFilePath, "wb");
    if (poutStream == 0)
      throw new CSMBFileException(CSMBFileException::openError, in_strFilePath);
    
    if (in_strFileFormat == "BMP")
      WriteBMP(poutStream);
    else
      WriteJPEG(poutStream, in_JPEGQuality);

    if (fclose(poutStream) == EOF)
      throw new CSMBFileException(CSMBFileException::closeError, in_strFilePath);
  }

  SMBInformation(TString("  Saved to ") + in_strFilePath.c_str()
                 + TString(" (") + in_strFileFormat + ")");
}


//////////////////////////////////////////////////////////////////////
// Save image to file with specific tag and parameter value
// added in file name.
TString CSMBImage::GetTaggedPath(TString in_Tag, double in_Par) const
{

  char chNum[10];
  TString strNum, strFilePath;

  chNum[0] = 0;

  if (snprintf(chNum, 10, "%g", in_Par) > 0)
    strNum.assign(chNum);

  strFilePath = SMB_DEFAULT_OUTPUT_FOLDER + "/" + m_strBaseName + "_" +
                in_Tag + "_" + strNum;

  return strFilePath;
}


void CSMBImage::SaveTaggedImage(TString in_Tag, double in_Par) const
  throw (CSMBFileException *)
{
  Save(GetTaggedPath(in_Tag, in_Par), SMB_DEFAULT_IMAGE_FORMAT);
}


//////////////////////////////////////////////////////////////////////
// Support for Portable Pixel/Gray Maps (PPM/PGM) images
//////////////////////////////////////////////////////////////////////

void CSMBImage::ReadPPM(ifstream &in_inStream)
throw (CSMBException *)
{
  // Check the magic numbers at the beginning of the file
  char strMagic[3], c;

  in_inStream >> strMagic; 
  in_inStream.get(c); // for the '\n'

  // Since unix and windows don't use the same "end of line" (\n\r vs. \r\n)
  // some files leads to error because they don't recognize the 'c' char
  if ((strMagic[0] != 'P') || (!isdigit(strMagic[1])) /*|| (c != '\n')*/)
  {
    // TODO: How can we get the filename from in_inStream?
    throw new CSMBFileException(CSMBFileException::invalidFileFormat, "TODO: Filename1");
  }

  unsigned  nChannels;
  ImageType itType;
  switch (strMagic[1])
  {
  case '5': // PGM binary 
      nChannels = 1;
      itType = IT_GRAY;
      break;
  
  case '6': // PPM binary 
      nChannels = 3;
      itType = IT_RGB;
      break;

  case '3': // PPM ASCII 
  case '2': // PGM ASCII 
    throw new CSMBFileException(CSMBFileException::invalidFileFormat, "(ASCII files are not supported)");
    break;

  default:
    throw new CSMBFileException(CSMBFileException::invalidFileFormat, "TODO: Filename2");
  }

     
  // Skeep the optional comment line
  while (isspace(in_inStream.peek())) in_inStream.get();
  while (in_inStream.peek() == '#')
    in_inStream.ignore(INT_MAX, '\n');

  // Get the number of columns
  long lCols;
  in_inStream >> lCols;
  // in_inStream.get(c); // for the '\n'

  // Get the number of rows
  while (isspace(in_inStream.peek())) in_inStream.get();
  long lRows;
  in_inStream >> lRows;
  // in_inStream.get(c); // for the '\n'

  // Get the maximum value
  while (isspace(in_inStream.peek())) in_inStream.get();
  int vmax;
  in_inStream >> vmax;
  in_inStream.get();

  if ( vmax > 255     || vmax  <= 0  ||
       lCols <= 1     || lRows <= 1   ||
       lCols > 350000 || lRows > 35000 ) {
    throw new CSMBFileException(CSMBFileException::invalidFileFormat, "TODO: Filename3");
  }
  
  CSMBMemoryException * pMemoryException = new CSMBMemoryException;
  Initialise(lCols, lRows, (Gray)vmax, /* TODO: Remove: nChannels,*/ itType, *pMemoryException);
  delete pMemoryException;
  
  switch (strMagic[1])
  {
  case '5': // PGM binary
  case '6': // PPM binary
    in_inStream.read((char *)m_imgValue.pgData, lCols * lRows * nChannels * sizeof(Gray));
    break;

  case '2': // PGM ASCII
  case '3': // PPM ASCII
  default:
    // This code should never be executed...
    throw new CSMBFileException(CSMBFileException::invalidFileFormat, "TODO: Filename4");
  }


  // Expand gray level so full range of values is used
  for (uint i = 0; i < m_nSize;)
    m_imgValue.pgData[i++] = (Gray)RoundClip((double)m_imgValue.pgData[i] * (double)255 / (double)vmax);
  m_imgValue.gMaxVal = 255;

}

void CSMBImage::WritePPM(ofstream &in_outStream) const
throw (CSMBException *)
{
  if (in_outStream.good())
  {
	  in_outStream << 'P';
    in_outStream << ((m_imgValue.nChannels == 1) ? 5 : 6);
    in_outStream << endl;
    in_outStream << m_imgValue.nCols;
    in_outStream << ' ';
    in_outStream << m_imgValue.nRows;
    in_outStream << endl;
    in_outStream << (int) m_imgValue.gMaxVal;
    in_outStream << endl;

    in_outStream.write((char *)m_imgValue.pgData, 
                       m_imgValue.nCols * m_imgValue.nRows * m_imgValue.nChannels * sizeof(Gray));
  }
  else
    throw new CSMBFileException(CSMBFileException::writeError, "TODO: Filename4");
}

//////////////////////////////////////////////////////////////////////
// Support for JPEG images
//////////////////////////////////////////////////////////////////////

// JPEG error handler
// Based on the "example.c" file provided with the JPEG library
// disptribution package

struct error_mgr {
  struct jpeg_error_mgr pub;  // "public" fields
  jmp_buf setjmp_buffer;      // for return to caller
};

typedef struct error_mgr * error_ptr;

static void _JPEGErrorExit (j_common_ptr cinfo)
{
  error_ptr err = (error_ptr) cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(err->setjmp_buffer, 1);
}


//////////////////////////////////////////////////////////////////////
// Write JPEG Files
void CSMBImage::WriteJPEG(FILE* in_poutStream, uint nQuality) const
throw (CSMBException *)
{
  struct jpeg_compress_struct cinfo;  // JPEG compression parameters and
                                      // pointers to working space
  struct jpeg_error_mgr jerr;         // JPEG error handler
                                      // not really used here
  JSAMPROW row_pointer[1]; // pointer to JSAMPLE row[s]
  int row_stride;          // physical row width in image buffer
  

  if (m_imgValue.pgData == NULL)
    SMBThrowNewException("[CSMBImage::WriteJPEG] - Could not write file");

  // Allocate and Initialise JPEG compression object
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  
  // Specify data destination (e.g., a file)
  jpeg_stdio_dest(&cinfo, in_poutStream);
  
  // Set parameters for compression
  cinfo.image_width = NumberOfColumns();      // image size in pixels 
  cinfo.image_height = NumberOfRows();
  cinfo.input_components = NumberOfChannels();  // # of color components per pixel 

  // colorspace of input image 
  if (NumberOfChannels() == 1)
      cinfo.in_color_space = JCS_GRAYSCALE;
  else if (NumberOfChannels() == 3)
      cinfo.in_color_space = JCS_RGB;
  else
      SMBThrowNewException("[CSMBImage::WriteJPEG] - Color depth not supported");
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, nQuality, TRUE /* limit to baseline-JPEG values */);
  
  // Compression 
  jpeg_start_compress(&cinfo, TRUE);
  row_stride = NumberOfColumns() * NumberOfChannels(); // JSAMPLEs per row in image_buffer 
  while (cinfo.next_scanline < cinfo.image_height)
  {
      row_pointer[0] = & m_imgValue.pgData[cinfo.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);

  // Release compressed object and file
  jpeg_destroy_compress(&cinfo);
}


//////////////////////////////////////////////////////////////////////
// Read JPEG files
void CSMBImage::ReadJPEG(FILE* in_pinStream)
throw (CSMBException *)
{
    struct jpeg_decompress_struct cinfo;  // decompression parameters and 
                                          // pointers to working space    
    struct error_mgr jerr;  // JPEG error handler   
                            // not really used here 

    JSAMPARRAY buffer;  // Output row buffer 
    int row_stride;     // physical row width in output buffer 

 
    // Allocate and Initialise JPEG decompression object 
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = _JPEGErrorExit;
    
    // Establish the setjmp return context for my_error_exit to use. 
    if (setjmp(jerr.setjmp_buffer))
    {
      // TODO: may be unsafe in C++
        jpeg_destroy_decompress(&cinfo);
        return;
    }
    jpeg_create_decompress(&cinfo);
    
    // Specify data source 
    jpeg_stdio_src(&cinfo, in_pinStream);
    
    // Read file parameters with jpeg_read_header() 
    (void) jpeg_read_header(&cinfo, TRUE);
    
    // Start decompressor 
    (void) jpeg_start_decompress(&cinfo);
    
    CSMBMemoryException * pMemoryException = new CSMBMemoryException;
    Initialise(cinfo.output_width, cinfo.output_height, 255,
               /* TODO: Remove: cinfo.output_components,*/ cinfo.output_components == 3 ? IT_RGB : IT_GRAY,*pMemoryException); 
    delete pMemoryException;

    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height)
    {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(&(m_imgValue.pgData[(cinfo.output_scanline - 1) * row_stride]), 
               buffer[0], row_stride);
    }
    (void) jpeg_finish_decompress(&cinfo);

    // Release JPEG decompression object 
    jpeg_destroy_decompress(&cinfo);
}


//////////////////////////////////////////////////////////////////////
// Support for BMP images (copied from StirMark 3.1)
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Read Windows bitmap images
void CSMBImage::ReadBMP(FILE* in_pinStream)
  throw (CSMBException *)
{
  struct jpeg_compress_struct cinfo;
  cjpeg_source_ptr source = NULL; // This is the source manager,
  // a pointer, allocated within
  // jinit_read_bmp
  struct jpeg_error_mgr jerr;  // JPEG error handler not really used here
  int row_stride;              // Physical row width in output buffer
  JDIMENSION current_row = (JDIMENSION) 0;
  
  
  // Allocate and Initialise JPEG compression object
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
	
  // Specify data source 
  source = jinit_read_bmp(&cinfo);
  source->input_file = in_pinStream;

  // Read the file header 
  (*source->start_input)(&cinfo, source);
    
  // We know the image size now, so allocate space for our image 
  CSMBMemoryException * pMemoryException = new CSMBMemoryException;
  switch (cinfo.input_components)
    {
      case 1:
	Initialise(cinfo.image_width, cinfo.image_height, 255,
		   /* TODO: Remove: 1,*/ IT_GRAY, *pMemoryException);
	break;
      case 3:
	Initialise(cinfo.image_width, cinfo.image_height, 255,
		   /* TODO: Remove: 3, */ IT_RGB, *pMemoryException); 
	break;
      default:
	SMBThrowNewException("[CSMBImage::ReadBMP] - Unexpected or unsupported color mode");
    }
  delete pMemoryException;	
	
  // Size of each row in bytes 
  row_stride = cinfo.image_width * cinfo.input_components;

  // Read in the image scanline by scanline 
  while (current_row < cinfo.image_height) {
    (*source->get_pixel_rows) (&cinfo, source);
    memcpy(&(m_imgValue.pgData[current_row * row_stride]),
	   (source->buffer)[0], row_stride);
    current_row++; 
  }
	
  // Finish off 
  (*source->finish_input)(&cinfo, source);
  jpeg_destroy_compress(&cinfo);
}


//////////////////////////////////////////////////////////////////////
// Write Windows bitmap images
void CSMBImage::WriteBMP(FILE* in_pinStream) const
  throw (CSMBException *)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  djpeg_dest_ptr dest = NULL; // This is the destination manager, 
  // a pointer, allocated within      
  // jinit_write_bmp                
  int row_stride;  // physical row width in output buffer 
  JDIMENSION current_row = (JDIMENSION) 0;

  if (m_imgValue.pgData == NULL)
    SMBThrowNewException("[CSMBImage::WriteBMP] - Could not write file");

  // Initialise the JPEG decompression object with default error handling. 
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

  // Fill in the rest of the fields for the decompressor object
  cinfo.output_components = NumberOfChannels();
  cinfo.num_components = NumberOfChannels();
  cinfo.image_width = NumberOfColumns();
  cinfo.image_height = NumberOfRows();
  cinfo.actual_number_of_colors = 256;
  cinfo.colormap = NULL; // We let wrbmp.c generate the colour map 
  cinfo.out_color_space = (NumberOfChannels() == 1)? JCS_GRAYSCALE : JCS_RGB;
  cinfo.quantize_colors = 0;   // We do not write 256 colour BMP files,  
  // so files are either 8-bit gray or      
  // 24-bit colour                          
  cinfo.global_state = DSTATE_READY; // A Hack - stop the jpeg processor 
  // module from complaining 
  cinfo.scale_num   = 1;    // No scaling 
  cinfo.scale_denom = 1;    // No scaling 
  cinfo.comp_info   = NULL; // The JDMASTER  needs to know this image is 
  // NOT in jpeg domain, hence it has no DCT   
  // components                                

  dest = jinit_write_bmp(&cinfo, FALSE);
  dest->output_file = in_pinStream;
	
  (*dest->start_output) (&cinfo, dest);

  row_stride = cinfo.output_width * cinfo.output_components;

  while(current_row < cinfo.output_height){
    memcpy((dest->buffer)[0], &(m_imgValue.pgData[current_row*row_stride]),row_stride);
    (*dest->put_pixel_rows) (&cinfo, dest, 1);
    current_row++;
  }
	
  // Finish off 
  (*dest->finish_output)(&cinfo, dest);
  jpeg_destroy_decompress(&cinfo);	
}



//////////////////////////////////////////////////////////////////////
// Sanity checks
//////////////////////////////////////////////////////////////////////

// This function says if a point is inside the image or not
int CSMBImage::IsInBounds(uint in_x, uint in_y, uint in_c) const
{
  return ((in_x < m_imgValue.nCols) &&
          (in_y < m_imgValue.nRows) &&
          (in_c < m_imgValue.nChannels) ?
	  TRUE :
	  FALSE);
}


// This function makes a basic sanity check of the object
int CSMBImage::IsValid() const
{
  return
    (
      (
        ((m_imgValue.itType == IT_GRAY) && (m_imgValue.nChannels == 1))
        ||
        (m_imgValue.nChannels == 3)
      )
      &&
      (
        (m_imgValue.pgData == 0 &&
         m_imgValue.nCols  == 0 &&
         m_imgValue.nRows  == 0 &&
         m_imgValue.lSize  == 0 &&
         m_nSize           == 0
        )
        ||
        (m_imgValue.pgData != 0    &&
         m_imgValue.nCols   > 0    &&
         m_imgValue.nRows   > 0    &&
         m_imgValue.nCols   < SMB_DEFAULT_MAX_IMAGE_WIDTH &&
         m_imgValue.nRows   < SMB_DEFAULT_MAX_IMAGE_HEIGHT &&
         m_nSize           == m_imgValue.nCols * m_imgValue.nRows * m_imgValue.nChannels
         && m_imgValue.lSize  == m_nSize * sizeof(Gray)
        )
      )
    );
}

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>

int SMBImage_Test()
{
  CSMBImage img;
  CSMBException e;

  cout << "  Reading image " << SMB_DEFAULT_SAMPLE_IMAGE_3 << endl;
  try
  {
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_3);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
    delete pException;
    return SMBFAILURE;
  }
  
  try
  {
    img.Save(SMB_DEFAULT_OUTPUT_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_3, SMB_DEFAULT_IMAGE_FORMAT);
  }
  catch (CSMBException *pException)
  {
    pException->PrintMsg();
    delete pException;
    return SMBFAILURE;
  }
  
  cout << "  Reading unsupported image " << SMB_DEFAULT_SAMPLE_IMAGE_2 << endl;
  try {
    // ASCII image are not accepted so this
    // will raise an exception
    img.Load(SMB_DEFAULT_DATABASE_FOLDER + SMB_DEFAULT_SAMPLE_IMAGE_2);
  }
  catch (CSMBException *pException) {
    pException->PrintMsg();
    delete pException;
  }

  return SMBSUCCESS;
}

#if _MSC_VER > 1000
#pragma warning (push)
#pragma warning (disable: 4290)
#endif // _MSC_VER > 1000

#endif // SMB_CODE_TESTING
