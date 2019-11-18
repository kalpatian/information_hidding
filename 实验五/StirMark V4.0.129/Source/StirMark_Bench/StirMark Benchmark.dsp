# Microsoft Developer Studio Project File - Name="StirMark Benchmark" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=StirMark Benchmark - Win32 Debug Testing
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StirMark Benchmark.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StirMark Benchmark.mak" CFG="StirMark Benchmark - Win32 Debug Testing"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StirMark Benchmark - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "StirMark Benchmark - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "StirMark Benchmark - Win32 Debug Testing" (based on "Win32 (x86) Console Application")
!MESSAGE "StirMark Benchmark - Win32 Release Testing" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/StirMark Benchmark", VFDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "release\StirMark Benchmark.exe" "..\..\Bin\Benchmark\StirMark Benchmark.exe"	copy "Profiles\SMBSettings.ini" "..\..\Profiles\SMBSettings.ini"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "StirMark_Benchmark___Win32_Debug_Testing"
# PROP BASE Intermediate_Dir "StirMark_Benchmark___Win32_Debug_Testing"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Testing"
# PROP Intermediate_Dir "Debug_Testing"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "SMB_CODE_TESTING" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "StirMark_Benchmark___Win32_Release_Testing"
# PROP BASE Intermediate_Dir "StirMark_Benchmark___Win32_Release_Testing"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Testing"
# PROP Intermediate_Dir "Release_Testing"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "SMB_CODE_TESTING" /FR /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ENDIF 

# Begin Target

# Name "StirMark Benchmark - Win32 Release"
# Name "StirMark Benchmark - Win32 Debug"
# Name "StirMark Benchmark - Win32 Debug Testing"
# Name "StirMark Benchmark - Win32 Release Testing"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Base"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Base\SMBBench.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBDatabase.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Base\SMBError.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBException.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBFileException.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBImage.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# ADD BASE CPP /W3
# ADD CPP /W4

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

# ADD CPP /W4

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Base\SMBImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMarkingScheme.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMatrix.cpp
# ADD CPP /W4
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMemoryException.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBProgramTesting.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Base\SMBQuality.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBRandomNumberGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBString.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\SMBTools.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\StirMarkBenchmark.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Tests"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Tests\SMBTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_AddNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Affine.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_ConvFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Cropping.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_EmbedTime.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_JPEG.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_MedianCut.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_PSNR.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RemoveLines.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Rescale.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Rotation.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RotationCrop.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RotationScale.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_SelfSimilarities.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_SmallRandomDistortions.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestGT.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestList.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestSP.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestST.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestTR.cpp
# End Source File
# End Group
# Begin Group "SignalProcessing"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SignalProcessing\SMBImageProcessing.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_AddDitherNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_AddNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_ConvFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_MedianCut.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_SelfSimilarities.cpp
# End Source File
# End Group
# Begin Group "GeometricTransforms"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GeometricTransforms\SMBDistortionMap.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# ADD BASE CPP /W3
# ADD CPP /W3

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Affine.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Rescale.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Rotation.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_SmallRandomDistortions.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecInterpolatingQuadratic.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecLinearInterpolation.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecNearestNeighbour.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBReconstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBResampler.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBSamPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_LatestSmallRandomDistortions.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBTransformer.cpp
# End Source File
# End Group
# Begin Group "SpecialTransforms"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_AFlip.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Cropping.cpp

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

# ADD BASE CPP /W3
# ADD CPP /W3

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_DFlip.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_HFlip.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Identity.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_RemoveLines.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot180.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot270.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot90.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Transposition.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_VFlip.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Base\StirMarkBenchmark.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Base_H"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Base\resource.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBBench.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBConfig.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBDatabase.h

!IF  "$(CFG)" == "StirMark Benchmark - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Debug Testing"

!ELSEIF  "$(CFG)" == "StirMark Benchmark - Win32 Release Testing"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Base\SMBError.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBException.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBFileException.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBImage.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBImageList.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBLog.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMarkingScheme.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMatrix.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBMemoryException.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBPtrWrapper.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBRandomNumberGenerator.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBString.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBTools.h
# End Source File
# Begin Source File

SOURCE=.\Base\SMBTypes.h
# End Source File
# Begin Source File

SOURCE=.\Base\StirMarkBenchmark.h
# End Source File
# End Group
# Begin Group "Tests_H"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Tests\SMBTest.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_AddNoise.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Affine.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_ConvFilter.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Cropping.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_EmbedTime.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_JPEG.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_MedianCut.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_PSNR.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RemoveLines.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Rescale.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_Rotation.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RotationCrop.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_RotationScale.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_SelfSimilarities.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_SmallRandomDistortions.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestGT.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestList.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestSP.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestST.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTestTR.h
# End Source File
# End Group
# Begin Group "SignalProcessing_H"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SignalProcessing\SMBImageProcessing.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_AddDitherNoise.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_AddNoise.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_ConvFilter.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_MedianCut.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcessing\SMBSP_SelfSimilarities.h
# End Source File
# End Group
# Begin Group "GeometricTransforms_H"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GeometricTransforms\SMBDistortionMap.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Affine.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Rescale.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_Rotation.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBGT_SmallRandomDistortions.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecInterpolatingQuadratic.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecLinearInterpolation.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBRecNearestNeighbour.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBReconstructor.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBResampler.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBSamPoint.h
# End Source File
# Begin Source File

SOURCE=.\Tests\SMBTest_LatestSmallRandomDistortions.h
# End Source File
# Begin Source File

SOURCE=.\GeometricTransforms\SMBTransformer.h
# End Source File
# End Group
# Begin Group "SpecialTransforms_H"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_AFlip.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Cropping.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_DFlip.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_HFlip.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Identity.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_RemoveLines.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot180.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot270.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Rot90.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_Transposition.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTransforms\SMBST_VFlip.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Profiles\Debug.ini
# End Source File
# Begin Source File

SOURCE=.\Profiles\SMBsettings.ini
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.doc"
# Begin Source File

SOURCE=.\Compilation.doc
# End Source File
# Begin Source File

SOURCE=".\Copyright notice.doc"
# End Source File
# Begin Source File

SOURCE=".\Project overview.doc"
# End Source File
# Begin Source File

SOURCE=".\SMB Manual.doc"
# End Source File
# End Group
# End Target
# End Project
