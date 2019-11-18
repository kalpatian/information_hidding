# Microsoft Developer Studio Project File - Name="JPEGLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=JPEGLib - Win32 Debug Testing
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JPEGLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JPEGLib.mak" CFG="JPEGLib - Win32 Debug Testing"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JPEGLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "JPEGLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "JPEGLib - Win32 Debug Testing" (based on "Win32 (x86) Static Library")
!MESSAGE "JPEGLib - Win32 Release Testing" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/JPEGLib", OFAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JPEGLib_"
# PROP BASE Intermediate_Dir "JPEGLib_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "JPEGLib___Win32_Debug_Testing"
# PROP BASE Intermediate_Dir "JPEGLib___Win32_Debug_Testing"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JPEGLib___Win32_Release_Testing"
# PROP BASE Intermediate_Dir "JPEGLib___Win32_Release_Testing"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "JPEGLib - Win32 Release"
# Name "JPEGLib - Win32 Debug"
# Name "JPEGLib - Win32 Debug Testing"
# Name "JPEGLib - Win32 Release Testing"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ansi2knr.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cdjpeg.c
# End Source File
# Begin Source File

SOURCE=.\cjpeg.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ckconfig.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\djpeg.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\example.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jcapimin.c
# End Source File
# Begin Source File

SOURCE=.\jcapistd.c
# End Source File
# Begin Source File

SOURCE=.\jccoefct.c
# End Source File
# Begin Source File

SOURCE=.\jccolor.c
# End Source File
# Begin Source File

SOURCE=.\jcdctmgr.c
# End Source File
# Begin Source File

SOURCE=.\jchuff.c
# End Source File
# Begin Source File

SOURCE=.\jcinit.c
# End Source File
# Begin Source File

SOURCE=.\jcmainct.c
# End Source File
# Begin Source File

SOURCE=.\jcmarker.c
# End Source File
# Begin Source File

SOURCE=.\jcmaster.c
# End Source File
# Begin Source File

SOURCE=.\jcomapi.c
# End Source File
# Begin Source File

SOURCE=.\jcparam.c
# End Source File
# Begin Source File

SOURCE=.\jcphuff.c
# End Source File
# Begin Source File

SOURCE=.\jcprepct.c
# End Source File
# Begin Source File

SOURCE=.\jcsample.c
# End Source File
# Begin Source File

SOURCE=.\jctrans.c
# End Source File
# Begin Source File

SOURCE=.\jdapimin.c
# End Source File
# Begin Source File

SOURCE=.\jdapistd.c
# End Source File
# Begin Source File

SOURCE=.\jdatadst.c
# End Source File
# Begin Source File

SOURCE=.\jdatasrc.c
# End Source File
# Begin Source File

SOURCE=.\jdcoefct.c
# End Source File
# Begin Source File

SOURCE=.\jdcolor.c
# End Source File
# Begin Source File

SOURCE=.\jddctmgr.c
# End Source File
# Begin Source File

SOURCE=.\jdhuff.c
# End Source File
# Begin Source File

SOURCE=.\jdinput.c
# End Source File
# Begin Source File

SOURCE=.\jdmainct.c
# End Source File
# Begin Source File

SOURCE=.\jdmarker.c
# End Source File
# Begin Source File

SOURCE=.\jdmaster.c
# End Source File
# Begin Source File

SOURCE=.\jdmerge.c
# End Source File
# Begin Source File

SOURCE=.\jdphuff.c
# End Source File
# Begin Source File

SOURCE=.\jdpostct.c
# End Source File
# Begin Source File

SOURCE=.\jdsample.c
# End Source File
# Begin Source File

SOURCE=.\jdtrans.c
# End Source File
# Begin Source File

SOURCE=.\jerror.c
# End Source File
# Begin Source File

SOURCE=.\jfdctflt.c
# End Source File
# Begin Source File

SOURCE=.\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=.\jfdctint.c
# End Source File
# Begin Source File

SOURCE=.\jidctflt.c
# End Source File
# Begin Source File

SOURCE=.\jidctfst.c
# End Source File
# Begin Source File

SOURCE=.\jidctint.c
# End Source File
# Begin Source File

SOURCE=.\jidctred.c
# End Source File
# Begin Source File

SOURCE=.\jmemansi.c
# End Source File
# Begin Source File

SOURCE=.\jmemdos.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jmemmac.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jmemmgr.c
# End Source File
# Begin Source File

SOURCE=.\jmemname.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jmemnobs.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jpegtran.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jquant1.c
# End Source File
# Begin Source File

SOURCE=.\jquant2.c
# End Source File
# Begin Source File

SOURCE=.\jutils.c
# End Source File
# Begin Source File

SOURCE=.\rdbmp.c
# End Source File
# Begin Source File

SOURCE=.\rdcolmap.c
# End Source File
# Begin Source File

SOURCE=.\rdgif.c
# End Source File
# Begin Source File

SOURCE=.\rdjpgcom.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rdppm.c
# End Source File
# Begin Source File

SOURCE=.\rdrle.c
# End Source File
# Begin Source File

SOURCE=.\rdswitch.c
# End Source File
# Begin Source File

SOURCE=.\rdtarga.c
# End Source File
# Begin Source File

SOURCE=.\transupp.c
# End Source File
# Begin Source File

SOURCE=.\wrbmp.c
# End Source File
# Begin Source File

SOURCE=.\wrgif.c
# End Source File
# Begin Source File

SOURCE=.\wrjpgcom.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wrppm.c
# End Source File
# Begin Source File

SOURCE=.\wrrle.c
# End Source File
# Begin Source File

SOURCE=.\wrtarga.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\jchuff.h
# End Source File
# Begin Source File

SOURCE=.\jconfig.h
# End Source File
# Begin Source File

SOURCE=.\jdct.h
# End Source File
# Begin Source File

SOURCE=.\jdhuff.h
# End Source File
# Begin Source File

SOURCE=.\jerror.h
# End Source File
# Begin Source File

SOURCE=.\jinclude.h
# End Source File
# Begin Source File

SOURCE=.\jmemsys.h
# End Source File
# Begin Source File

SOURCE=.\jmorecfg.h
# End Source File
# Begin Source File

SOURCE=.\jpegint.h
# End Source File
# Begin Source File

SOURCE=.\jpeglib.h
# End Source File
# Begin Source File

SOURCE=.\jversion.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Other files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ansi2knr.1
# End Source File
# Begin Source File

SOURCE=.\change.log
# End Source File
# Begin Source File

SOURCE=.\cjpeg.1
# End Source File
# Begin Source File

SOURCE=.\coderules.doc
# End Source File
# Begin Source File

SOURCE=.\config.guess
# End Source File
# Begin Source File

SOURCE=.\config.sub
# End Source File
# Begin Source File

SOURCE=.\configure
# End Source File
# Begin Source File

SOURCE=.\djpeg.1
# End Source File
# Begin Source File

SOURCE=.\filelist.doc
# End Source File
# Begin Source File

SOURCE=".\install-sh"
# End Source File
# Begin Source File

SOURCE=.\install.doc
# End Source File
# Begin Source File

SOURCE=.\jconfig.bcc
# End Source File
# Begin Source File

SOURCE=.\jconfig.cfg
# End Source File
# Begin Source File

SOURCE=.\jconfig.dj
# End Source File
# Begin Source File

SOURCE=.\jconfig.doc
# End Source File
# Begin Source File

SOURCE=.\jconfig.mac
# End Source File
# Begin Source File

SOURCE=.\jconfig.manx
# End Source File
# Begin Source File

SOURCE=.\jconfig.mc6
# End Source File
# Begin Source File

SOURCE=.\jconfig.sas
# End Source File
# Begin Source File

SOURCE=.\jconfig.st
# End Source File
# Begin Source File

SOURCE=.\jconfig.vc
# End Source File
# Begin Source File

SOURCE=.\jconfig.vms
# End Source File
# Begin Source File

SOURCE=.\jconfig.wat
# End Source File
# Begin Source File

SOURCE=.\jmemdosa.asm
# End Source File
# Begin Source File

SOURCE=.\jpegtran.1
# End Source File
# Begin Source File

SOURCE=.\ltconfig
# End Source File
# Begin Source File

SOURCE=.\ltmain.sh
# End Source File
# Begin Source File

SOURCE=.\makcjpeg.st
# End Source File
# Begin Source File

SOURCE=.\makdjpeg.st
# End Source File
# Begin Source File

SOURCE=.\makeapps.ds
# End Source File
# Begin Source File

SOURCE=.\makefile.ansi
# End Source File
# Begin Source File

SOURCE=.\makefile.bcc
# End Source File
# Begin Source File

SOURCE=.\makefile.cfg
# End Source File
# Begin Source File

SOURCE=.\makefile.dj
# End Source File
# Begin Source File

SOURCE=.\makefile.manx
# End Source File
# Begin Source File

SOURCE=.\makefile.mc6
# End Source File
# Begin Source File

SOURCE=.\makefile.mms
# End Source File
# Begin Source File

SOURCE=.\makefile.sas
# End Source File
# Begin Source File

SOURCE=.\makefile.unix
# End Source File
# Begin Source File

SOURCE=.\makefile.vc
# End Source File
# Begin Source File

SOURCE=.\makefile.vms
# End Source File
# Begin Source File

SOURCE=.\makefile.wat
# End Source File
# Begin Source File

SOURCE=.\makelib.ds
# End Source File
# Begin Source File

SOURCE=.\makeproj.mac
# End Source File
# Begin Source File

SOURCE=.\makljpeg.st
# End Source File
# Begin Source File

SOURCE=.\maktjpeg.st
# End Source File
# Begin Source File

SOURCE=.\makvms.opt
# End Source File
# Begin Source File

SOURCE=.\rdjpgcom.1
# End Source File
# Begin Source File

SOURCE=.\README
# End Source File
# Begin Source File

SOURCE=.\structure.doc
# End Source File
# Begin Source File

SOURCE=.\testimg.bmp
# End Source File
# Begin Source File

SOURCE=.\testimg.jpg
# End Source File
# Begin Source File

SOURCE=.\testimg.ppm
# End Source File
# Begin Source File

SOURCE=.\testimgp.jpg
# End Source File
# Begin Source File

SOURCE=.\testorig.jpg
# End Source File
# Begin Source File

SOURCE=.\testprog.jpg
# End Source File
# Begin Source File

SOURCE=.\usage.doc
# End Source File
# Begin Source File

SOURCE=.\wizard.doc
# End Source File
# Begin Source File

SOURCE=.\wrjpgcom.1
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
