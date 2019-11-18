//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBImageList.cpp
//
// Contents: Implementation of the CSMBImageList class.
//
// Purpose:  See SMBImageList.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 14 September 2000
//           parts based on code by
//           Nazim Fatès, Microsoft Research, June 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBImageList.cpp,v 1.16 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers
#include <iostream>
#if _MSC_VER > 1020  // if later than VC++ 4.2
using namespace std; // the std C++ libs are in namespace std
#endif

// Other standard headers
#ifdef WIN32
#include <io.h>     // for _findfirst
#define snprintf _snprintf
#endif // WIN32
#ifdef __UNIX__
#include <glob.h>
#endif // __UNIX__

// SMB headers
#include "SMBConfig.h"
#include "SMBImageList.h"
#include "SMBTools.h"
#include "SMBError.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBImageList::CSMBImageList()
  : list<TString>()
{

}

CSMBImageList::~CSMBImageList()
{

}

//////////////////////////////////////////////////////////////////////
// Fill the list according to initialisation file settings

void CSMBImageList::Initialise(TCString &in_strIniFilePath)
{
  SMBInformation("  IMAGES >>", 0);

  clear();
    
  TString strFolderName;

  // for each folder
  int i = 1;
  while (ParseProfileString(SMB_DEFAULT_IMAGE_FOLDER_SECTION,
                            SMB_DEFAULT_IMAGE_FOLDER_KEY + CSMBString(i++),
                            "",
                            in_strIniFilePath,
                            strFolderName))
  {
    // Add all the images present in the input folders
    // to the list of images
    LoadFolderFiles(strFolderName, ".ppm");
    LoadFolderFiles(strFolderName, ".jpg");
    LoadFolderFiles(strFolderName, ".bmp");

    // Delete all the images present in the output folder
    DeleteFolderFiles(SMB_DEFAULT_OUTPUT_FOLDER + "/" + strFolderName, ".ppm");
    DeleteFolderFiles(SMB_DEFAULT_OUTPUT_FOLDER + "/" + strFolderName, ".jpg");
    DeleteFolderFiles(SMB_DEFAULT_OUTPUT_FOLDER + "/" + strFolderName, ".bmp");
  }
}

//////////////////////////////////////////////////////////////////////
// List of files in folders

// List all the files of a specified format in a folder
// and adds their names without extension to the list

void CSMBImageList::LoadFolderFiles(TCString &in_cstrDirPath,
                                       TCString &in_cstrExtension)
{
  TString strFilesToFind;
  strFilesToFind = SMB_DEFAULT_DATABASE_FOLDER + "/" + in_cstrDirPath +
                   "/*" + in_cstrExtension;

#ifdef WIN32
  long hFile;
  struct _finddata_t c_file;

  hFile = _findfirst(strFilesToFind, &c_file);
	if (hFile != -1L)
  {
    // Some files have been found
		do
    {
      SMBInformation(TString("    ") +
                     SMB_DEFAULT_DATABASE_FOLDER + TString("/") + 
                     in_cstrDirPath + TString("/") +
                     c_file.name, 0);
      push_back(in_cstrDirPath + "/" + c_file.name);
    }
    while(_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
  }
#endif // WIN32

#ifdef __UNIX__
  glob_t path;
  int error = glob(strFilesToFind, 0, NULL, &path);

  SMBInformation(TString("File : [") + strFilesToFind + "]");
  SMBInformation(TString("Path : [") + in_cstrDirPath + "]");

  // TODO: Use the exceptions
  switch(error) {
    case GLOB_NOMATCH :
      cerr << strFilesToFind << " : nothing matches." << endl;
      break;
    case GLOB_ABORTED :
      cerr << strFilesToFind << " : a read error occurs." << endl;
      break;
    case GLOB_NOSPACE :
      cerr << "Running out of memory while reading " << strFilesToFind << endl;
    default:
      for (uint i = 0; i < path.gl_pathc; i++) {
	      cout << "    Found " << path.gl_pathv[i] << endl;
	      push_back(strdup(path.gl_pathv[i] + strlen(SMB_DEFAULT_DATABASE_FOLDER)+1));
      }
  }
  globfree (&path);
#endif // __UNIX__
}


// deletes all the files of one type in a folder
// handle with care !
// DeleteFolderFiles ("IMAGES",".ppm") will delete
// is equivalent to "delete OUTPUT/IMAGES/*.ppm"
void CSMBImageList::DeleteFolderFiles(TCString &in_cstrDirPath, TCString &in_cstrExtension)
{

#ifdef WIN32

  long hFile;
  struct _finddata_t c_file;

  TString strFilesToFind, FileToDelete;
  strFilesToFind = in_cstrDirPath + "/*" + in_cstrExtension;

	if ((hFile = _findfirst(strFilesToFind , &c_file)) != -1L)
  {
    // we look all the files in the folder
    do
    {
      FileToDelete.assign(c_file.name);
      ::remove((in_cstrDirPath + "/" + FileToDelete).c_str());
    }
    while (_findnext( hFile, &c_file ) == 0);
    _findclose( hFile );
  }

#endif // WIN32

#ifdef __UNIX__
  /*
    The clearenv() call is here for security reasons ... 
    but could lead to troubles if another system() is called 
    somewhere else without having set the right variable before.
   */
  clearenv ();
  setenv ("IFS", " \t\n", 1);
  TString strCommand = "/bin/rm -f "+in_cstrDirPath + "/*" + in_cstrExtension;
  system(strCommand);
#endif // __UNIX__
}

//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>

int SMBImageList_Test()
{
  cout << "\n\nSMBImageList testing (begin)" << endl;

  CSMBImageList lstimgTest;
  CSMBImageList::iterator iterstrName;
 
  lstimgTest.Initialise(SMB_DEFAULT_SETTINGS_FOLDER + SMB_DEFAULT_SETTINGS_FILE);

  cout << "\nThe following images have been found:" << endl;
  for (iterstrName = lstimgTest.begin(); iterstrName != lstimgTest.end(); iterstrName++)
    cout << "\t" << *iterstrName << endl;
  lstimgTest.clear();

  cout << "\n\nSMBImageList testing (end)" << endl;
  return SMBSUCCESS;
}
#endif // SMB_CODE_TESTING
