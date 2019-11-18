# Microsoft Developer Studio Project File - Name="LT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LT - Win32 Debug Testing
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LT.mak" CFG="LT - Win32 Debug Testing"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LT - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LT - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LT - Win32 Debug Testing" (based on "Win32 (x86) Static Library")
!MESSAGE "LT - Win32 Release Testing" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Lapped Transform", XCDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LT - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Za /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LT___Win32_Debug_Testing"
# PROP BASE Intermediate_Dir "LT___Win32_Debug_Testing"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Za /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /Za /W4 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LT___Win32_Release_Testing"
# PROP BASE Intermediate_Dir "LT___Win32_Release_Testing"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LT - Win32 Release"
# Name "LT - Win32 Debug"
# Name "LT - Win32 Debug Testing"
# Name "LT - Win32 Release Testing"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FDCT.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FDCTIV.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FDCTIV2.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FDHT.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FELT.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FELT2.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FLOT.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FLOT2.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RSFFT.C

!IF  "$(CFG)" == "LT - Win32 Release"

!ELSEIF  "$(CFG)" == "LT - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LT - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SRFFT.C
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
