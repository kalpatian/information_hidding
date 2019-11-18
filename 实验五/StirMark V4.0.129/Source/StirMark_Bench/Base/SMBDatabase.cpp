//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBDatabase.cpp
//
// Contents: Implementation of the CSMBDatabase class.
//
// Purpose:  See SMBDatabase.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, 6 October 2000
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
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBDatabase.cpp,v 1.12 2002/04/19 10:23:54 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// SMB headers
#include "SMBDatabase.h"
#include "SMBError.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBDatabase::CSMBDatabase()
{

}


CSMBDatabase::~CSMBDatabase()
{

}


//////////////////////////////////////////////////////////////////////
// Connect to a SQL server
//////////////////////////////////////////////////////////////////////

int CSMBDatabase::Open(TCString in_strServerName   /* = SMB_SQL_SERVER_NAME */,
                       TCString in_strLoginName    /* = SMB_SQL_LOGIN_NAME */,
                       TCString in_strPassword     /* = SMB_SQL_PASSWORD */,
                       TCString in_strDatabaseName /* = SMB_SQL_DATABASE_NAME */)
{
#ifdef WIN32
	RETCODE rcResultCode;
  LPCSTR  pszVersion; // Version of the database library

	// Forward declarations of the error handler and message handler.
  int _SQLErrorHandler(PDBPROCESS, int, int, int, char*, char*);
  int _SQLMessageHandler(PDBPROCESS, DBINT, int, int, char*);

  if ((pszVersion = dbinit()) == (char *)NULL) {
		SMBWarning("[CSMBDatabase::Open] Communications layer not loaded\n");
		return(SMBFAILURE);
	}
  else {
    SMBInformation(TString("Database library loaded ") + pszVersion);
  }
	
	// Install the error-handling	and message-handling routines.
  // Defined at the end of this file
	dberrhandle((DBERRHANDLE_PROC)_SQLErrorHandler);
	dbmsghandle((DBMSGHANDLE_PROC)_SQLMessageHandler);


	m_dbLogin = dblogin(); // Allocates a LOGINREC structure for use in dbopen.
  if (m_dbLogin == 0) {
    // TODO: error handling
  }

	rcResultCode = DBSETLUSER   (m_dbLogin, in_strLoginName)      | // Set the username
	               DBSETLAPP    (m_dbLogin, SMB_APPLICATION_NAME) | // set the application name
	               DBSETLPWD    (m_dbLogin, in_strPassword)       | // set the SQL Server password
	               DBSETLVERSION(m_dbLogin, DBVER60);
  if (rcResultCode != SUCCEED)
  {
    SMBWarning("[CSMBDatabase::Open] failed to initialise the longin structure");
    return (SMBFAILURE);
  }

	// Now attempt to create and initialize a DBPROCESS structure
	if ((m_dbProcess = dbopen(m_dbLogin, in_strServerName)) == NULL)
	{
    SMBWarning("[CSMBDatabase::Open] dbopen failed");
		return (SMBFAILURE);
	}

	rcResultCode = dbuse(m_dbProcess, in_strDatabaseName);
	if (rcResultCode != SUCCEED)
  {
    SMBWarning("[CSMBDatabase::Open] dbuse failed");
    return (SMBFAILURE);
  }
#endif // WIN32

#ifdef __UNIX__
	// TODO
#endif

  return (SMBSUCCESS);
}


//////////////////////////////////////////////////////////////////////
// Add a command in the command buffer to be sent to the database
//////////////////////////////////////////////////////////////////////

int CSMBDatabase::AddCommand(TCString in_strCommand)
{
#ifdef WIN32
  RETCODE rcResultCode;
  
  // Construct command buffer to be sent to the SQL server
	rcResultCode = dbcmd(m_dbProcess, in_strCommand);
  if (rcResultCode != SUCCEED)
    return (SMBFAILURE);
#endif // WIN32

#ifdef __UNIX__
  // TODO
#endif

  return (SMBSUCCESS);
}


//////////////////////////////////////////////////////////////////////
// Sen a command batch to the SQL server
//////////////////////////////////////////////////////////////////////

int CSMBDatabase::ExecuteCommandStack(void)
{
#ifdef WIN32
  RETCODE rcResultCode;

  // Send command buffer to SQL server
  rcResultCode = dbsqlexec(m_dbProcess);
  if (rcResultCode != SUCCEED)
    return (SMBFAILURE);
  
  // Get ready to process the results of the query
  while ((rcResultCode = dbresults(m_dbProcess)) != NO_MORE_RESULTS)
  {
    if (rcResultCode == SUCCEED)
    {
      // TODO: binding and processing should be done outside
      //       this function. Not sure yet how the best interface looks like though
      // DBINT n1, n2;
			// dbbind (m_dbProcess,	1, INTBIND, (DBINT) 0, (BYTE *) &n1);
			// dbbind (m_dbProcess,	2, INTBIND, (DBINT) 0, (BYTE *) &n2);

			// Now process the rows
			while (dbnextrow(m_dbProcess) != NO_MORE_ROWS)
			{
				// printf ("ID:  %d\n",	n1);
				// printf ("Value:  %d\n",	n2);
				// printf ("\n");
			}
		}
		else
		{
			// printf ("Results Failed\n");
			break;
		}
  }

  if (rcResultCode == NO_MORE_RESULTS)
    return (SMBSUCCESS);
  else
    return (SMBFAILURE);

#endif // WIN32

#ifdef __UNIX__
  //TODO
#endif

  return (SMBSUCCESS);
}


//////////////////////////////////////////////////////////////////////
// Close the connection with the SQL server
//////////////////////////////////////////////////////////////////////

int CSMBDatabase::Close(void)
{
#ifdef WIN32
	RETCODE rcResultCode;
  rcResultCode = dbclose(m_dbProcess);
  if (rcResultCode != SUCCEED)
  {
    SMBWarning("[CSMBDatabase::Open] failed to initialise the longin structure");
    return (SMBFAILURE);
  }
#endif // WIN32

  return (SMBSUCCESS);
}


#ifdef WIN32

int _SQLErrorHandler(PDBPROCESS dbproc, int severity, int dberr, int oserr, char * dberrstr, char * oserrstr)
{
  // TODO: better error handling
	if (dberrstr != NULL)
		printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);

	if ((dbproc == NULL) ||	(DBDEAD(dbproc)))
		return(INT_EXIT);
	else
		return(INT_CANCEL);
}


int _SQLMessageHandler(PDBPROCESS dbproc, DBINT msgno, int msgstate, int severity, char * msgtext)
{
  // TODO: better error handling
	printf("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
			msgno, msgstate, severity, msgtext);
	return(0);
}
#endif /* WIN32 */  


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef SMB_CODE_TESTING

#include <assert.h>
#include <string.h>

int SMBDatabase_Test()
{
  int nResult;

  // Default constructors
  CSMBDatabase dbTest;

  nResult = dbTest.Open(/* Use default parameters */);

  nResult = dbTest.AddCommand("IF EXISTS(SELECT TABLE_NAME\n"
                              "          FROM INFORMATION_SCHEMA.TABLES\n"
                              "          WHERE TABLE_NAME = 'SMB_TEST_TABLE')\n"
                              "   DROP TABLE SMB_TEST_TABLE\n"
                              "CREATE TABLE SMB_TEST_TABLE\n"
                              "   ( column_1 int identity,\n"
                              "     column_2 int\n"
                              "   )\n"
                              "INSERT INTO SMB_TEST_TABLE (column_2) VALUES (0)\n"
                              "INSERT INTO SMB_TEST_TABLE (column_2) VALUES (2)\n"
                              "INSERT INTO SMB_TEST_TABLE (column_2) VALUES (4)\n"
                              "INSERT INTO SMB_TEST_TABLE (column_2) VALUES (6)\n"
                              "SELECT * FROM SMB_TEST_TABLE\n");
  nResult = dbTest.ExecuteCommandStack();

  return (nResult);
}
#endif // SMB_CODE_TESTING
