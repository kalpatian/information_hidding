# Microsoft Developer Studio Generated NMAKE File, Based on JPEGLib.dsp
!IF "$(CFG)" == ""
CFG=JPEGLib - Win32 Debug Testing
!MESSAGE No configuration specified. Defaulting to JPEGLib - Win32 Debug Testing.
!ENDIF 

!IF "$(CFG)" != "JPEGLib - Win32 Release" && "$(CFG)" != "JPEGLib - Win32 Debug" && "$(CFG)" != "JPEGLib - Win32 Debug Testing"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "JPEGLib - Win32 Release"

OUTDIR=.\JPEGLib_
INTDIR=.\JPEGLib_
# Begin Custom Macros
OutDir=.\JPEGLib_
# End Custom Macros

ALL : "$(OUTDIR)\JPEGLib.lib" "$(OUTDIR)\JPEGLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\cdjpeg.obj"
	-@erase "$(INTDIR)\cdjpeg.sbr"
	-@erase "$(INTDIR)\jcapimin.obj"
	-@erase "$(INTDIR)\jcapimin.sbr"
	-@erase "$(INTDIR)\jcapistd.obj"
	-@erase "$(INTDIR)\jcapistd.sbr"
	-@erase "$(INTDIR)\jccoefct.obj"
	-@erase "$(INTDIR)\jccoefct.sbr"
	-@erase "$(INTDIR)\jccolor.obj"
	-@erase "$(INTDIR)\jccolor.sbr"
	-@erase "$(INTDIR)\jcdctmgr.obj"
	-@erase "$(INTDIR)\jcdctmgr.sbr"
	-@erase "$(INTDIR)\jchuff.obj"
	-@erase "$(INTDIR)\jchuff.sbr"
	-@erase "$(INTDIR)\jcinit.obj"
	-@erase "$(INTDIR)\jcinit.sbr"
	-@erase "$(INTDIR)\jcmainct.obj"
	-@erase "$(INTDIR)\jcmainct.sbr"
	-@erase "$(INTDIR)\jcmarker.obj"
	-@erase "$(INTDIR)\jcmarker.sbr"
	-@erase "$(INTDIR)\jcmaster.obj"
	-@erase "$(INTDIR)\jcmaster.sbr"
	-@erase "$(INTDIR)\jcomapi.obj"
	-@erase "$(INTDIR)\jcomapi.sbr"
	-@erase "$(INTDIR)\jcparam.obj"
	-@erase "$(INTDIR)\jcparam.sbr"
	-@erase "$(INTDIR)\jcphuff.obj"
	-@erase "$(INTDIR)\jcphuff.sbr"
	-@erase "$(INTDIR)\jcprepct.obj"
	-@erase "$(INTDIR)\jcprepct.sbr"
	-@erase "$(INTDIR)\jcsample.obj"
	-@erase "$(INTDIR)\jcsample.sbr"
	-@erase "$(INTDIR)\jctrans.obj"
	-@erase "$(INTDIR)\jctrans.sbr"
	-@erase "$(INTDIR)\jdapimin.obj"
	-@erase "$(INTDIR)\jdapimin.sbr"
	-@erase "$(INTDIR)\jdapistd.obj"
	-@erase "$(INTDIR)\jdapistd.sbr"
	-@erase "$(INTDIR)\jdatadst.obj"
	-@erase "$(INTDIR)\jdatadst.sbr"
	-@erase "$(INTDIR)\jdatasrc.obj"
	-@erase "$(INTDIR)\jdatasrc.sbr"
	-@erase "$(INTDIR)\jdcoefct.obj"
	-@erase "$(INTDIR)\jdcoefct.sbr"
	-@erase "$(INTDIR)\jdcolor.obj"
	-@erase "$(INTDIR)\jdcolor.sbr"
	-@erase "$(INTDIR)\jddctmgr.obj"
	-@erase "$(INTDIR)\jddctmgr.sbr"
	-@erase "$(INTDIR)\jdhuff.obj"
	-@erase "$(INTDIR)\jdhuff.sbr"
	-@erase "$(INTDIR)\jdinput.obj"
	-@erase "$(INTDIR)\jdinput.sbr"
	-@erase "$(INTDIR)\jdmainct.obj"
	-@erase "$(INTDIR)\jdmainct.sbr"
	-@erase "$(INTDIR)\jdmarker.obj"
	-@erase "$(INTDIR)\jdmarker.sbr"
	-@erase "$(INTDIR)\jdmaster.obj"
	-@erase "$(INTDIR)\jdmaster.sbr"
	-@erase "$(INTDIR)\jdmerge.obj"
	-@erase "$(INTDIR)\jdmerge.sbr"
	-@erase "$(INTDIR)\jdphuff.obj"
	-@erase "$(INTDIR)\jdphuff.sbr"
	-@erase "$(INTDIR)\jdpostct.obj"
	-@erase "$(INTDIR)\jdpostct.sbr"
	-@erase "$(INTDIR)\jdsample.obj"
	-@erase "$(INTDIR)\jdsample.sbr"
	-@erase "$(INTDIR)\jdtrans.obj"
	-@erase "$(INTDIR)\jdtrans.sbr"
	-@erase "$(INTDIR)\jerror.obj"
	-@erase "$(INTDIR)\jerror.sbr"
	-@erase "$(INTDIR)\jfdctflt.obj"
	-@erase "$(INTDIR)\jfdctflt.sbr"
	-@erase "$(INTDIR)\jfdctfst.obj"
	-@erase "$(INTDIR)\jfdctfst.sbr"
	-@erase "$(INTDIR)\jfdctint.obj"
	-@erase "$(INTDIR)\jfdctint.sbr"
	-@erase "$(INTDIR)\jidctflt.obj"
	-@erase "$(INTDIR)\jidctflt.sbr"
	-@erase "$(INTDIR)\jidctfst.obj"
	-@erase "$(INTDIR)\jidctfst.sbr"
	-@erase "$(INTDIR)\jidctint.obj"
	-@erase "$(INTDIR)\jidctint.sbr"
	-@erase "$(INTDIR)\jidctred.obj"
	-@erase "$(INTDIR)\jidctred.sbr"
	-@erase "$(INTDIR)\jmemansi.obj"
	-@erase "$(INTDIR)\jmemansi.sbr"
	-@erase "$(INTDIR)\jmemmgr.obj"
	-@erase "$(INTDIR)\jmemmgr.sbr"
	-@erase "$(INTDIR)\jquant1.obj"
	-@erase "$(INTDIR)\jquant1.sbr"
	-@erase "$(INTDIR)\jquant2.obj"
	-@erase "$(INTDIR)\jquant2.sbr"
	-@erase "$(INTDIR)\jutils.obj"
	-@erase "$(INTDIR)\jutils.sbr"
	-@erase "$(INTDIR)\rdbmp.obj"
	-@erase "$(INTDIR)\rdbmp.sbr"
	-@erase "$(INTDIR)\rdcolmap.obj"
	-@erase "$(INTDIR)\rdcolmap.sbr"
	-@erase "$(INTDIR)\rdgif.obj"
	-@erase "$(INTDIR)\rdgif.sbr"
	-@erase "$(INTDIR)\rdppm.obj"
	-@erase "$(INTDIR)\rdppm.sbr"
	-@erase "$(INTDIR)\rdrle.obj"
	-@erase "$(INTDIR)\rdrle.sbr"
	-@erase "$(INTDIR)\rdswitch.obj"
	-@erase "$(INTDIR)\rdswitch.sbr"
	-@erase "$(INTDIR)\rdtarga.obj"
	-@erase "$(INTDIR)\rdtarga.sbr"
	-@erase "$(INTDIR)\transupp.obj"
	-@erase "$(INTDIR)\transupp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wrbmp.obj"
	-@erase "$(INTDIR)\wrbmp.sbr"
	-@erase "$(INTDIR)\wrgif.obj"
	-@erase "$(INTDIR)\wrgif.sbr"
	-@erase "$(INTDIR)\wrjpgcom.obj"
	-@erase "$(INTDIR)\wrjpgcom.sbr"
	-@erase "$(INTDIR)\wrppm.obj"
	-@erase "$(INTDIR)\wrppm.sbr"
	-@erase "$(INTDIR)\wrrle.obj"
	-@erase "$(INTDIR)\wrrle.sbr"
	-@erase "$(INTDIR)\wrtarga.obj"
	-@erase "$(INTDIR)\wrtarga.sbr"
	-@erase "$(OUTDIR)\JPEGLib.bsc"
	-@erase "$(OUTDIR)\JPEGLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\JPEGLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\JPEGLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cdjpeg.sbr" \
	"$(INTDIR)\jcapimin.sbr" \
	"$(INTDIR)\jcapistd.sbr" \
	"$(INTDIR)\jccoefct.sbr" \
	"$(INTDIR)\jccolor.sbr" \
	"$(INTDIR)\jcdctmgr.sbr" \
	"$(INTDIR)\jchuff.sbr" \
	"$(INTDIR)\jcinit.sbr" \
	"$(INTDIR)\jcmainct.sbr" \
	"$(INTDIR)\jcmarker.sbr" \
	"$(INTDIR)\jcmaster.sbr" \
	"$(INTDIR)\jcomapi.sbr" \
	"$(INTDIR)\jcparam.sbr" \
	"$(INTDIR)\jcphuff.sbr" \
	"$(INTDIR)\jcprepct.sbr" \
	"$(INTDIR)\jcsample.sbr" \
	"$(INTDIR)\jctrans.sbr" \
	"$(INTDIR)\jdapimin.sbr" \
	"$(INTDIR)\jdapistd.sbr" \
	"$(INTDIR)\jdatadst.sbr" \
	"$(INTDIR)\jdatasrc.sbr" \
	"$(INTDIR)\jdcoefct.sbr" \
	"$(INTDIR)\jdcolor.sbr" \
	"$(INTDIR)\jddctmgr.sbr" \
	"$(INTDIR)\jdhuff.sbr" \
	"$(INTDIR)\jdinput.sbr" \
	"$(INTDIR)\jdmainct.sbr" \
	"$(INTDIR)\jdmarker.sbr" \
	"$(INTDIR)\jdmaster.sbr" \
	"$(INTDIR)\jdmerge.sbr" \
	"$(INTDIR)\jdphuff.sbr" \
	"$(INTDIR)\jdpostct.sbr" \
	"$(INTDIR)\jdsample.sbr" \
	"$(INTDIR)\jdtrans.sbr" \
	"$(INTDIR)\jerror.sbr" \
	"$(INTDIR)\jfdctflt.sbr" \
	"$(INTDIR)\jfdctfst.sbr" \
	"$(INTDIR)\jfdctint.sbr" \
	"$(INTDIR)\jidctflt.sbr" \
	"$(INTDIR)\jidctfst.sbr" \
	"$(INTDIR)\jidctint.sbr" \
	"$(INTDIR)\jidctred.sbr" \
	"$(INTDIR)\jmemansi.sbr" \
	"$(INTDIR)\jmemmgr.sbr" \
	"$(INTDIR)\jquant1.sbr" \
	"$(INTDIR)\jquant2.sbr" \
	"$(INTDIR)\jutils.sbr" \
	"$(INTDIR)\rdbmp.sbr" \
	"$(INTDIR)\rdcolmap.sbr" \
	"$(INTDIR)\rdgif.sbr" \
	"$(INTDIR)\rdppm.sbr" \
	"$(INTDIR)\rdrle.sbr" \
	"$(INTDIR)\rdswitch.sbr" \
	"$(INTDIR)\rdtarga.sbr" \
	"$(INTDIR)\transupp.sbr" \
	"$(INTDIR)\wrbmp.sbr" \
	"$(INTDIR)\wrgif.sbr" \
	"$(INTDIR)\wrjpgcom.sbr" \
	"$(INTDIR)\wrppm.sbr" \
	"$(INTDIR)\wrrle.sbr" \
	"$(INTDIR)\wrtarga.sbr"

"$(OUTDIR)\JPEGLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\JPEGLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cdjpeg.obj" \
	"$(INTDIR)\jcapimin.obj" \
	"$(INTDIR)\jcapistd.obj" \
	"$(INTDIR)\jccoefct.obj" \
	"$(INTDIR)\jccolor.obj" \
	"$(INTDIR)\jcdctmgr.obj" \
	"$(INTDIR)\jchuff.obj" \
	"$(INTDIR)\jcinit.obj" \
	"$(INTDIR)\jcmainct.obj" \
	"$(INTDIR)\jcmarker.obj" \
	"$(INTDIR)\jcmaster.obj" \
	"$(INTDIR)\jcomapi.obj" \
	"$(INTDIR)\jcparam.obj" \
	"$(INTDIR)\jcphuff.obj" \
	"$(INTDIR)\jcprepct.obj" \
	"$(INTDIR)\jcsample.obj" \
	"$(INTDIR)\jctrans.obj" \
	"$(INTDIR)\jdapimin.obj" \
	"$(INTDIR)\jdapistd.obj" \
	"$(INTDIR)\jdatadst.obj" \
	"$(INTDIR)\jdatasrc.obj" \
	"$(INTDIR)\jdcoefct.obj" \
	"$(INTDIR)\jdcolor.obj" \
	"$(INTDIR)\jddctmgr.obj" \
	"$(INTDIR)\jdhuff.obj" \
	"$(INTDIR)\jdinput.obj" \
	"$(INTDIR)\jdmainct.obj" \
	"$(INTDIR)\jdmarker.obj" \
	"$(INTDIR)\jdmaster.obj" \
	"$(INTDIR)\jdmerge.obj" \
	"$(INTDIR)\jdphuff.obj" \
	"$(INTDIR)\jdpostct.obj" \
	"$(INTDIR)\jdsample.obj" \
	"$(INTDIR)\jdtrans.obj" \
	"$(INTDIR)\jerror.obj" \
	"$(INTDIR)\jfdctflt.obj" \
	"$(INTDIR)\jfdctfst.obj" \
	"$(INTDIR)\jfdctint.obj" \
	"$(INTDIR)\jidctflt.obj" \
	"$(INTDIR)\jidctfst.obj" \
	"$(INTDIR)\jidctint.obj" \
	"$(INTDIR)\jidctred.obj" \
	"$(INTDIR)\jmemansi.obj" \
	"$(INTDIR)\jmemmgr.obj" \
	"$(INTDIR)\jquant1.obj" \
	"$(INTDIR)\jquant2.obj" \
	"$(INTDIR)\jutils.obj" \
	"$(INTDIR)\rdbmp.obj" \
	"$(INTDIR)\rdcolmap.obj" \
	"$(INTDIR)\rdgif.obj" \
	"$(INTDIR)\rdppm.obj" \
	"$(INTDIR)\rdrle.obj" \
	"$(INTDIR)\rdswitch.obj" \
	"$(INTDIR)\rdtarga.obj" \
	"$(INTDIR)\transupp.obj" \
	"$(INTDIR)\wrbmp.obj" \
	"$(INTDIR)\wrgif.obj" \
	"$(INTDIR)\wrjpgcom.obj" \
	"$(INTDIR)\wrppm.obj" \
	"$(INTDIR)\wrrle.obj" \
	"$(INTDIR)\wrtarga.obj"

"$(OUTDIR)\JPEGLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\JPEGLib.lib" "$(OUTDIR)\JPEGLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\cdjpeg.obj"
	-@erase "$(INTDIR)\cdjpeg.sbr"
	-@erase "$(INTDIR)\jcapimin.obj"
	-@erase "$(INTDIR)\jcapimin.sbr"
	-@erase "$(INTDIR)\jcapistd.obj"
	-@erase "$(INTDIR)\jcapistd.sbr"
	-@erase "$(INTDIR)\jccoefct.obj"
	-@erase "$(INTDIR)\jccoefct.sbr"
	-@erase "$(INTDIR)\jccolor.obj"
	-@erase "$(INTDIR)\jccolor.sbr"
	-@erase "$(INTDIR)\jcdctmgr.obj"
	-@erase "$(INTDIR)\jcdctmgr.sbr"
	-@erase "$(INTDIR)\jchuff.obj"
	-@erase "$(INTDIR)\jchuff.sbr"
	-@erase "$(INTDIR)\jcinit.obj"
	-@erase "$(INTDIR)\jcinit.sbr"
	-@erase "$(INTDIR)\jcmainct.obj"
	-@erase "$(INTDIR)\jcmainct.sbr"
	-@erase "$(INTDIR)\jcmarker.obj"
	-@erase "$(INTDIR)\jcmarker.sbr"
	-@erase "$(INTDIR)\jcmaster.obj"
	-@erase "$(INTDIR)\jcmaster.sbr"
	-@erase "$(INTDIR)\jcomapi.obj"
	-@erase "$(INTDIR)\jcomapi.sbr"
	-@erase "$(INTDIR)\jcparam.obj"
	-@erase "$(INTDIR)\jcparam.sbr"
	-@erase "$(INTDIR)\jcphuff.obj"
	-@erase "$(INTDIR)\jcphuff.sbr"
	-@erase "$(INTDIR)\jcprepct.obj"
	-@erase "$(INTDIR)\jcprepct.sbr"
	-@erase "$(INTDIR)\jcsample.obj"
	-@erase "$(INTDIR)\jcsample.sbr"
	-@erase "$(INTDIR)\jctrans.obj"
	-@erase "$(INTDIR)\jctrans.sbr"
	-@erase "$(INTDIR)\jdapimin.obj"
	-@erase "$(INTDIR)\jdapimin.sbr"
	-@erase "$(INTDIR)\jdapistd.obj"
	-@erase "$(INTDIR)\jdapistd.sbr"
	-@erase "$(INTDIR)\jdatadst.obj"
	-@erase "$(INTDIR)\jdatadst.sbr"
	-@erase "$(INTDIR)\jdatasrc.obj"
	-@erase "$(INTDIR)\jdatasrc.sbr"
	-@erase "$(INTDIR)\jdcoefct.obj"
	-@erase "$(INTDIR)\jdcoefct.sbr"
	-@erase "$(INTDIR)\jdcolor.obj"
	-@erase "$(INTDIR)\jdcolor.sbr"
	-@erase "$(INTDIR)\jddctmgr.obj"
	-@erase "$(INTDIR)\jddctmgr.sbr"
	-@erase "$(INTDIR)\jdhuff.obj"
	-@erase "$(INTDIR)\jdhuff.sbr"
	-@erase "$(INTDIR)\jdinput.obj"
	-@erase "$(INTDIR)\jdinput.sbr"
	-@erase "$(INTDIR)\jdmainct.obj"
	-@erase "$(INTDIR)\jdmainct.sbr"
	-@erase "$(INTDIR)\jdmarker.obj"
	-@erase "$(INTDIR)\jdmarker.sbr"
	-@erase "$(INTDIR)\jdmaster.obj"
	-@erase "$(INTDIR)\jdmaster.sbr"
	-@erase "$(INTDIR)\jdmerge.obj"
	-@erase "$(INTDIR)\jdmerge.sbr"
	-@erase "$(INTDIR)\jdphuff.obj"
	-@erase "$(INTDIR)\jdphuff.sbr"
	-@erase "$(INTDIR)\jdpostct.obj"
	-@erase "$(INTDIR)\jdpostct.sbr"
	-@erase "$(INTDIR)\jdsample.obj"
	-@erase "$(INTDIR)\jdsample.sbr"
	-@erase "$(INTDIR)\jdtrans.obj"
	-@erase "$(INTDIR)\jdtrans.sbr"
	-@erase "$(INTDIR)\jerror.obj"
	-@erase "$(INTDIR)\jerror.sbr"
	-@erase "$(INTDIR)\jfdctflt.obj"
	-@erase "$(INTDIR)\jfdctflt.sbr"
	-@erase "$(INTDIR)\jfdctfst.obj"
	-@erase "$(INTDIR)\jfdctfst.sbr"
	-@erase "$(INTDIR)\jfdctint.obj"
	-@erase "$(INTDIR)\jfdctint.sbr"
	-@erase "$(INTDIR)\jidctflt.obj"
	-@erase "$(INTDIR)\jidctflt.sbr"
	-@erase "$(INTDIR)\jidctfst.obj"
	-@erase "$(INTDIR)\jidctfst.sbr"
	-@erase "$(INTDIR)\jidctint.obj"
	-@erase "$(INTDIR)\jidctint.sbr"
	-@erase "$(INTDIR)\jidctred.obj"
	-@erase "$(INTDIR)\jidctred.sbr"
	-@erase "$(INTDIR)\jmemansi.obj"
	-@erase "$(INTDIR)\jmemansi.sbr"
	-@erase "$(INTDIR)\jmemmgr.obj"
	-@erase "$(INTDIR)\jmemmgr.sbr"
	-@erase "$(INTDIR)\jquant1.obj"
	-@erase "$(INTDIR)\jquant1.sbr"
	-@erase "$(INTDIR)\jquant2.obj"
	-@erase "$(INTDIR)\jquant2.sbr"
	-@erase "$(INTDIR)\jutils.obj"
	-@erase "$(INTDIR)\jutils.sbr"
	-@erase "$(INTDIR)\rdbmp.obj"
	-@erase "$(INTDIR)\rdbmp.sbr"
	-@erase "$(INTDIR)\rdcolmap.obj"
	-@erase "$(INTDIR)\rdcolmap.sbr"
	-@erase "$(INTDIR)\rdgif.obj"
	-@erase "$(INTDIR)\rdgif.sbr"
	-@erase "$(INTDIR)\rdppm.obj"
	-@erase "$(INTDIR)\rdppm.sbr"
	-@erase "$(INTDIR)\rdrle.obj"
	-@erase "$(INTDIR)\rdrle.sbr"
	-@erase "$(INTDIR)\rdswitch.obj"
	-@erase "$(INTDIR)\rdswitch.sbr"
	-@erase "$(INTDIR)\rdtarga.obj"
	-@erase "$(INTDIR)\rdtarga.sbr"
	-@erase "$(INTDIR)\transupp.obj"
	-@erase "$(INTDIR)\transupp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wrbmp.obj"
	-@erase "$(INTDIR)\wrbmp.sbr"
	-@erase "$(INTDIR)\wrgif.obj"
	-@erase "$(INTDIR)\wrgif.sbr"
	-@erase "$(INTDIR)\wrppm.obj"
	-@erase "$(INTDIR)\wrppm.sbr"
	-@erase "$(INTDIR)\wrrle.obj"
	-@erase "$(INTDIR)\wrrle.sbr"
	-@erase "$(INTDIR)\wrtarga.obj"
	-@erase "$(INTDIR)\wrtarga.sbr"
	-@erase "$(OUTDIR)\JPEGLib.bsc"
	-@erase "$(OUTDIR)\JPEGLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\JPEGLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\JPEGLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cdjpeg.sbr" \
	"$(INTDIR)\jcapimin.sbr" \
	"$(INTDIR)\jcapistd.sbr" \
	"$(INTDIR)\jccoefct.sbr" \
	"$(INTDIR)\jccolor.sbr" \
	"$(INTDIR)\jcdctmgr.sbr" \
	"$(INTDIR)\jchuff.sbr" \
	"$(INTDIR)\jcinit.sbr" \
	"$(INTDIR)\jcmainct.sbr" \
	"$(INTDIR)\jcmarker.sbr" \
	"$(INTDIR)\jcmaster.sbr" \
	"$(INTDIR)\jcomapi.sbr" \
	"$(INTDIR)\jcparam.sbr" \
	"$(INTDIR)\jcphuff.sbr" \
	"$(INTDIR)\jcprepct.sbr" \
	"$(INTDIR)\jcsample.sbr" \
	"$(INTDIR)\jctrans.sbr" \
	"$(INTDIR)\jdapimin.sbr" \
	"$(INTDIR)\jdapistd.sbr" \
	"$(INTDIR)\jdatadst.sbr" \
	"$(INTDIR)\jdatasrc.sbr" \
	"$(INTDIR)\jdcoefct.sbr" \
	"$(INTDIR)\jdcolor.sbr" \
	"$(INTDIR)\jddctmgr.sbr" \
	"$(INTDIR)\jdhuff.sbr" \
	"$(INTDIR)\jdinput.sbr" \
	"$(INTDIR)\jdmainct.sbr" \
	"$(INTDIR)\jdmarker.sbr" \
	"$(INTDIR)\jdmaster.sbr" \
	"$(INTDIR)\jdmerge.sbr" \
	"$(INTDIR)\jdphuff.sbr" \
	"$(INTDIR)\jdpostct.sbr" \
	"$(INTDIR)\jdsample.sbr" \
	"$(INTDIR)\jdtrans.sbr" \
	"$(INTDIR)\jerror.sbr" \
	"$(INTDIR)\jfdctflt.sbr" \
	"$(INTDIR)\jfdctfst.sbr" \
	"$(INTDIR)\jfdctint.sbr" \
	"$(INTDIR)\jidctflt.sbr" \
	"$(INTDIR)\jidctfst.sbr" \
	"$(INTDIR)\jidctint.sbr" \
	"$(INTDIR)\jidctred.sbr" \
	"$(INTDIR)\jmemansi.sbr" \
	"$(INTDIR)\jmemmgr.sbr" \
	"$(INTDIR)\jquant1.sbr" \
	"$(INTDIR)\jquant2.sbr" \
	"$(INTDIR)\jutils.sbr" \
	"$(INTDIR)\rdbmp.sbr" \
	"$(INTDIR)\rdcolmap.sbr" \
	"$(INTDIR)\rdgif.sbr" \
	"$(INTDIR)\rdppm.sbr" \
	"$(INTDIR)\rdrle.sbr" \
	"$(INTDIR)\rdswitch.sbr" \
	"$(INTDIR)\rdtarga.sbr" \
	"$(INTDIR)\transupp.sbr" \
	"$(INTDIR)\wrbmp.sbr" \
	"$(INTDIR)\wrgif.sbr" \
	"$(INTDIR)\wrppm.sbr" \
	"$(INTDIR)\wrrle.sbr" \
	"$(INTDIR)\wrtarga.sbr"

"$(OUTDIR)\JPEGLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\JPEGLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cdjpeg.obj" \
	"$(INTDIR)\jcapimin.obj" \
	"$(INTDIR)\jcapistd.obj" \
	"$(INTDIR)\jccoefct.obj" \
	"$(INTDIR)\jccolor.obj" \
	"$(INTDIR)\jcdctmgr.obj" \
	"$(INTDIR)\jchuff.obj" \
	"$(INTDIR)\jcinit.obj" \
	"$(INTDIR)\jcmainct.obj" \
	"$(INTDIR)\jcmarker.obj" \
	"$(INTDIR)\jcmaster.obj" \
	"$(INTDIR)\jcomapi.obj" \
	"$(INTDIR)\jcparam.obj" \
	"$(INTDIR)\jcphuff.obj" \
	"$(INTDIR)\jcprepct.obj" \
	"$(INTDIR)\jcsample.obj" \
	"$(INTDIR)\jctrans.obj" \
	"$(INTDIR)\jdapimin.obj" \
	"$(INTDIR)\jdapistd.obj" \
	"$(INTDIR)\jdatadst.obj" \
	"$(INTDIR)\jdatasrc.obj" \
	"$(INTDIR)\jdcoefct.obj" \
	"$(INTDIR)\jdcolor.obj" \
	"$(INTDIR)\jddctmgr.obj" \
	"$(INTDIR)\jdhuff.obj" \
	"$(INTDIR)\jdinput.obj" \
	"$(INTDIR)\jdmainct.obj" \
	"$(INTDIR)\jdmarker.obj" \
	"$(INTDIR)\jdmaster.obj" \
	"$(INTDIR)\jdmerge.obj" \
	"$(INTDIR)\jdphuff.obj" \
	"$(INTDIR)\jdpostct.obj" \
	"$(INTDIR)\jdsample.obj" \
	"$(INTDIR)\jdtrans.obj" \
	"$(INTDIR)\jerror.obj" \
	"$(INTDIR)\jfdctflt.obj" \
	"$(INTDIR)\jfdctfst.obj" \
	"$(INTDIR)\jfdctint.obj" \
	"$(INTDIR)\jidctflt.obj" \
	"$(INTDIR)\jidctfst.obj" \
	"$(INTDIR)\jidctint.obj" \
	"$(INTDIR)\jidctred.obj" \
	"$(INTDIR)\jmemansi.obj" \
	"$(INTDIR)\jmemmgr.obj" \
	"$(INTDIR)\jquant1.obj" \
	"$(INTDIR)\jquant2.obj" \
	"$(INTDIR)\jutils.obj" \
	"$(INTDIR)\rdbmp.obj" \
	"$(INTDIR)\rdcolmap.obj" \
	"$(INTDIR)\rdgif.obj" \
	"$(INTDIR)\rdppm.obj" \
	"$(INTDIR)\rdrle.obj" \
	"$(INTDIR)\rdswitch.obj" \
	"$(INTDIR)\rdtarga.obj" \
	"$(INTDIR)\transupp.obj" \
	"$(INTDIR)\wrbmp.obj" \
	"$(INTDIR)\wrgif.obj" \
	"$(INTDIR)\wrppm.obj" \
	"$(INTDIR)\wrrle.obj" \
	"$(INTDIR)\wrtarga.obj"

"$(OUTDIR)\JPEGLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

OUTDIR=.\JPEGLib___Win32_Debug_Testing
INTDIR=.\JPEGLib___Win32_Debug_Testing
# Begin Custom Macros
OutDir=.\JPEGLib___Win32_Debug_Testing
# End Custom Macros

ALL : "$(OUTDIR)\JPEGLib.lib" "$(OUTDIR)\JPEGLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\cdjpeg.obj"
	-@erase "$(INTDIR)\cdjpeg.sbr"
	-@erase "$(INTDIR)\jcapimin.obj"
	-@erase "$(INTDIR)\jcapimin.sbr"
	-@erase "$(INTDIR)\jcapistd.obj"
	-@erase "$(INTDIR)\jcapistd.sbr"
	-@erase "$(INTDIR)\jccoefct.obj"
	-@erase "$(INTDIR)\jccoefct.sbr"
	-@erase "$(INTDIR)\jccolor.obj"
	-@erase "$(INTDIR)\jccolor.sbr"
	-@erase "$(INTDIR)\jcdctmgr.obj"
	-@erase "$(INTDIR)\jcdctmgr.sbr"
	-@erase "$(INTDIR)\jchuff.obj"
	-@erase "$(INTDIR)\jchuff.sbr"
	-@erase "$(INTDIR)\jcinit.obj"
	-@erase "$(INTDIR)\jcinit.sbr"
	-@erase "$(INTDIR)\jcmainct.obj"
	-@erase "$(INTDIR)\jcmainct.sbr"
	-@erase "$(INTDIR)\jcmarker.obj"
	-@erase "$(INTDIR)\jcmarker.sbr"
	-@erase "$(INTDIR)\jcmaster.obj"
	-@erase "$(INTDIR)\jcmaster.sbr"
	-@erase "$(INTDIR)\jcomapi.obj"
	-@erase "$(INTDIR)\jcomapi.sbr"
	-@erase "$(INTDIR)\jcparam.obj"
	-@erase "$(INTDIR)\jcparam.sbr"
	-@erase "$(INTDIR)\jcphuff.obj"
	-@erase "$(INTDIR)\jcphuff.sbr"
	-@erase "$(INTDIR)\jcprepct.obj"
	-@erase "$(INTDIR)\jcprepct.sbr"
	-@erase "$(INTDIR)\jcsample.obj"
	-@erase "$(INTDIR)\jcsample.sbr"
	-@erase "$(INTDIR)\jctrans.obj"
	-@erase "$(INTDIR)\jctrans.sbr"
	-@erase "$(INTDIR)\jdapimin.obj"
	-@erase "$(INTDIR)\jdapimin.sbr"
	-@erase "$(INTDIR)\jdapistd.obj"
	-@erase "$(INTDIR)\jdapistd.sbr"
	-@erase "$(INTDIR)\jdatadst.obj"
	-@erase "$(INTDIR)\jdatadst.sbr"
	-@erase "$(INTDIR)\jdatasrc.obj"
	-@erase "$(INTDIR)\jdatasrc.sbr"
	-@erase "$(INTDIR)\jdcoefct.obj"
	-@erase "$(INTDIR)\jdcoefct.sbr"
	-@erase "$(INTDIR)\jdcolor.obj"
	-@erase "$(INTDIR)\jdcolor.sbr"
	-@erase "$(INTDIR)\jddctmgr.obj"
	-@erase "$(INTDIR)\jddctmgr.sbr"
	-@erase "$(INTDIR)\jdhuff.obj"
	-@erase "$(INTDIR)\jdhuff.sbr"
	-@erase "$(INTDIR)\jdinput.obj"
	-@erase "$(INTDIR)\jdinput.sbr"
	-@erase "$(INTDIR)\jdmainct.obj"
	-@erase "$(INTDIR)\jdmainct.sbr"
	-@erase "$(INTDIR)\jdmarker.obj"
	-@erase "$(INTDIR)\jdmarker.sbr"
	-@erase "$(INTDIR)\jdmaster.obj"
	-@erase "$(INTDIR)\jdmaster.sbr"
	-@erase "$(INTDIR)\jdmerge.obj"
	-@erase "$(INTDIR)\jdmerge.sbr"
	-@erase "$(INTDIR)\jdphuff.obj"
	-@erase "$(INTDIR)\jdphuff.sbr"
	-@erase "$(INTDIR)\jdpostct.obj"
	-@erase "$(INTDIR)\jdpostct.sbr"
	-@erase "$(INTDIR)\jdsample.obj"
	-@erase "$(INTDIR)\jdsample.sbr"
	-@erase "$(INTDIR)\jdtrans.obj"
	-@erase "$(INTDIR)\jdtrans.sbr"
	-@erase "$(INTDIR)\jerror.obj"
	-@erase "$(INTDIR)\jerror.sbr"
	-@erase "$(INTDIR)\jfdctflt.obj"
	-@erase "$(INTDIR)\jfdctflt.sbr"
	-@erase "$(INTDIR)\jfdctfst.obj"
	-@erase "$(INTDIR)\jfdctfst.sbr"
	-@erase "$(INTDIR)\jfdctint.obj"
	-@erase "$(INTDIR)\jfdctint.sbr"
	-@erase "$(INTDIR)\jidctflt.obj"
	-@erase "$(INTDIR)\jidctflt.sbr"
	-@erase "$(INTDIR)\jidctfst.obj"
	-@erase "$(INTDIR)\jidctfst.sbr"
	-@erase "$(INTDIR)\jidctint.obj"
	-@erase "$(INTDIR)\jidctint.sbr"
	-@erase "$(INTDIR)\jidctred.obj"
	-@erase "$(INTDIR)\jidctred.sbr"
	-@erase "$(INTDIR)\jmemansi.obj"
	-@erase "$(INTDIR)\jmemansi.sbr"
	-@erase "$(INTDIR)\jmemmgr.obj"
	-@erase "$(INTDIR)\jmemmgr.sbr"
	-@erase "$(INTDIR)\jquant1.obj"
	-@erase "$(INTDIR)\jquant1.sbr"
	-@erase "$(INTDIR)\jquant2.obj"
	-@erase "$(INTDIR)\jquant2.sbr"
	-@erase "$(INTDIR)\jutils.obj"
	-@erase "$(INTDIR)\jutils.sbr"
	-@erase "$(INTDIR)\rdbmp.obj"
	-@erase "$(INTDIR)\rdbmp.sbr"
	-@erase "$(INTDIR)\rdcolmap.obj"
	-@erase "$(INTDIR)\rdcolmap.sbr"
	-@erase "$(INTDIR)\rdgif.obj"
	-@erase "$(INTDIR)\rdgif.sbr"
	-@erase "$(INTDIR)\rdppm.obj"
	-@erase "$(INTDIR)\rdppm.sbr"
	-@erase "$(INTDIR)\rdrle.obj"
	-@erase "$(INTDIR)\rdrle.sbr"
	-@erase "$(INTDIR)\rdswitch.obj"
	-@erase "$(INTDIR)\rdswitch.sbr"
	-@erase "$(INTDIR)\rdtarga.obj"
	-@erase "$(INTDIR)\rdtarga.sbr"
	-@erase "$(INTDIR)\transupp.obj"
	-@erase "$(INTDIR)\transupp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wrbmp.obj"
	-@erase "$(INTDIR)\wrbmp.sbr"
	-@erase "$(INTDIR)\wrgif.obj"
	-@erase "$(INTDIR)\wrgif.sbr"
	-@erase "$(INTDIR)\wrppm.obj"
	-@erase "$(INTDIR)\wrppm.sbr"
	-@erase "$(INTDIR)\wrrle.obj"
	-@erase "$(INTDIR)\wrrle.sbr"
	-@erase "$(INTDIR)\wrtarga.obj"
	-@erase "$(INTDIR)\wrtarga.sbr"
	-@erase "$(OUTDIR)\JPEGLib.bsc"
	-@erase "$(OUTDIR)\JPEGLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\JPEGLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\JPEGLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cdjpeg.sbr" \
	"$(INTDIR)\jcapimin.sbr" \
	"$(INTDIR)\jcapistd.sbr" \
	"$(INTDIR)\jccoefct.sbr" \
	"$(INTDIR)\jccolor.sbr" \
	"$(INTDIR)\jcdctmgr.sbr" \
	"$(INTDIR)\jchuff.sbr" \
	"$(INTDIR)\jcinit.sbr" \
	"$(INTDIR)\jcmainct.sbr" \
	"$(INTDIR)\jcmarker.sbr" \
	"$(INTDIR)\jcmaster.sbr" \
	"$(INTDIR)\jcomapi.sbr" \
	"$(INTDIR)\jcparam.sbr" \
	"$(INTDIR)\jcphuff.sbr" \
	"$(INTDIR)\jcprepct.sbr" \
	"$(INTDIR)\jcsample.sbr" \
	"$(INTDIR)\jctrans.sbr" \
	"$(INTDIR)\jdapimin.sbr" \
	"$(INTDIR)\jdapistd.sbr" \
	"$(INTDIR)\jdatadst.sbr" \
	"$(INTDIR)\jdatasrc.sbr" \
	"$(INTDIR)\jdcoefct.sbr" \
	"$(INTDIR)\jdcolor.sbr" \
	"$(INTDIR)\jddctmgr.sbr" \
	"$(INTDIR)\jdhuff.sbr" \
	"$(INTDIR)\jdinput.sbr" \
	"$(INTDIR)\jdmainct.sbr" \
	"$(INTDIR)\jdmarker.sbr" \
	"$(INTDIR)\jdmaster.sbr" \
	"$(INTDIR)\jdmerge.sbr" \
	"$(INTDIR)\jdphuff.sbr" \
	"$(INTDIR)\jdpostct.sbr" \
	"$(INTDIR)\jdsample.sbr" \
	"$(INTDIR)\jdtrans.sbr" \
	"$(INTDIR)\jerror.sbr" \
	"$(INTDIR)\jfdctflt.sbr" \
	"$(INTDIR)\jfdctfst.sbr" \
	"$(INTDIR)\jfdctint.sbr" \
	"$(INTDIR)\jidctflt.sbr" \
	"$(INTDIR)\jidctfst.sbr" \
	"$(INTDIR)\jidctint.sbr" \
	"$(INTDIR)\jidctred.sbr" \
	"$(INTDIR)\jmemansi.sbr" \
	"$(INTDIR)\jmemmgr.sbr" \
	"$(INTDIR)\jquant1.sbr" \
	"$(INTDIR)\jquant2.sbr" \
	"$(INTDIR)\jutils.sbr" \
	"$(INTDIR)\rdbmp.sbr" \
	"$(INTDIR)\rdcolmap.sbr" \
	"$(INTDIR)\rdgif.sbr" \
	"$(INTDIR)\rdppm.sbr" \
	"$(INTDIR)\rdrle.sbr" \
	"$(INTDIR)\rdswitch.sbr" \
	"$(INTDIR)\rdtarga.sbr" \
	"$(INTDIR)\transupp.sbr" \
	"$(INTDIR)\wrbmp.sbr" \
	"$(INTDIR)\wrgif.sbr" \
	"$(INTDIR)\wrppm.sbr" \
	"$(INTDIR)\wrrle.sbr" \
	"$(INTDIR)\wrtarga.sbr"

"$(OUTDIR)\JPEGLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\JPEGLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cdjpeg.obj" \
	"$(INTDIR)\jcapimin.obj" \
	"$(INTDIR)\jcapistd.obj" \
	"$(INTDIR)\jccoefct.obj" \
	"$(INTDIR)\jccolor.obj" \
	"$(INTDIR)\jcdctmgr.obj" \
	"$(INTDIR)\jchuff.obj" \
	"$(INTDIR)\jcinit.obj" \
	"$(INTDIR)\jcmainct.obj" \
	"$(INTDIR)\jcmarker.obj" \
	"$(INTDIR)\jcmaster.obj" \
	"$(INTDIR)\jcomapi.obj" \
	"$(INTDIR)\jcparam.obj" \
	"$(INTDIR)\jcphuff.obj" \
	"$(INTDIR)\jcprepct.obj" \
	"$(INTDIR)\jcsample.obj" \
	"$(INTDIR)\jctrans.obj" \
	"$(INTDIR)\jdapimin.obj" \
	"$(INTDIR)\jdapistd.obj" \
	"$(INTDIR)\jdatadst.obj" \
	"$(INTDIR)\jdatasrc.obj" \
	"$(INTDIR)\jdcoefct.obj" \
	"$(INTDIR)\jdcolor.obj" \
	"$(INTDIR)\jddctmgr.obj" \
	"$(INTDIR)\jdhuff.obj" \
	"$(INTDIR)\jdinput.obj" \
	"$(INTDIR)\jdmainct.obj" \
	"$(INTDIR)\jdmarker.obj" \
	"$(INTDIR)\jdmaster.obj" \
	"$(INTDIR)\jdmerge.obj" \
	"$(INTDIR)\jdphuff.obj" \
	"$(INTDIR)\jdpostct.obj" \
	"$(INTDIR)\jdsample.obj" \
	"$(INTDIR)\jdtrans.obj" \
	"$(INTDIR)\jerror.obj" \
	"$(INTDIR)\jfdctflt.obj" \
	"$(INTDIR)\jfdctfst.obj" \
	"$(INTDIR)\jfdctint.obj" \
	"$(INTDIR)\jidctflt.obj" \
	"$(INTDIR)\jidctfst.obj" \
	"$(INTDIR)\jidctint.obj" \
	"$(INTDIR)\jidctred.obj" \
	"$(INTDIR)\jmemansi.obj" \
	"$(INTDIR)\jmemmgr.obj" \
	"$(INTDIR)\jquant1.obj" \
	"$(INTDIR)\jquant2.obj" \
	"$(INTDIR)\jutils.obj" \
	"$(INTDIR)\rdbmp.obj" \
	"$(INTDIR)\rdcolmap.obj" \
	"$(INTDIR)\rdgif.obj" \
	"$(INTDIR)\rdppm.obj" \
	"$(INTDIR)\rdrle.obj" \
	"$(INTDIR)\rdswitch.obj" \
	"$(INTDIR)\rdtarga.obj" \
	"$(INTDIR)\transupp.obj" \
	"$(INTDIR)\wrbmp.obj" \
	"$(INTDIR)\wrgif.obj" \
	"$(INTDIR)\wrppm.obj" \
	"$(INTDIR)\wrrle.obj" \
	"$(INTDIR)\wrtarga.obj"

"$(OUTDIR)\JPEGLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("JPEGLib.dep")
!INCLUDE "JPEGLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "JPEGLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "JPEGLib - Win32 Release" || "$(CFG)" == "JPEGLib - Win32 Debug" || "$(CFG)" == "JPEGLib - Win32 Debug Testing"
SOURCE=.\ansi2knr.c
SOURCE=.\cdjpeg.c

"$(INTDIR)\cdjpeg.obj"	"$(INTDIR)\cdjpeg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cjpeg.c
SOURCE=.\ckconfig.c
SOURCE=.\djpeg.c
SOURCE=.\example.c
SOURCE=.\jcapimin.c

"$(INTDIR)\jcapimin.obj"	"$(INTDIR)\jcapimin.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcapistd.c

"$(INTDIR)\jcapistd.obj"	"$(INTDIR)\jcapistd.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jccoefct.c

"$(INTDIR)\jccoefct.obj"	"$(INTDIR)\jccoefct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jccolor.c

"$(INTDIR)\jccolor.obj"	"$(INTDIR)\jccolor.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcdctmgr.c

"$(INTDIR)\jcdctmgr.obj"	"$(INTDIR)\jcdctmgr.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jchuff.c

"$(INTDIR)\jchuff.obj"	"$(INTDIR)\jchuff.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcinit.c

"$(INTDIR)\jcinit.obj"	"$(INTDIR)\jcinit.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcmainct.c

"$(INTDIR)\jcmainct.obj"	"$(INTDIR)\jcmainct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcmarker.c

"$(INTDIR)\jcmarker.obj"	"$(INTDIR)\jcmarker.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcmaster.c

"$(INTDIR)\jcmaster.obj"	"$(INTDIR)\jcmaster.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcomapi.c

"$(INTDIR)\jcomapi.obj"	"$(INTDIR)\jcomapi.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcparam.c

"$(INTDIR)\jcparam.obj"	"$(INTDIR)\jcparam.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcphuff.c

"$(INTDIR)\jcphuff.obj"	"$(INTDIR)\jcphuff.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcprepct.c

"$(INTDIR)\jcprepct.obj"	"$(INTDIR)\jcprepct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jcsample.c

"$(INTDIR)\jcsample.obj"	"$(INTDIR)\jcsample.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jctrans.c

"$(INTDIR)\jctrans.obj"	"$(INTDIR)\jctrans.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdapimin.c

"$(INTDIR)\jdapimin.obj"	"$(INTDIR)\jdapimin.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdapistd.c

"$(INTDIR)\jdapistd.obj"	"$(INTDIR)\jdapistd.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdatadst.c

"$(INTDIR)\jdatadst.obj"	"$(INTDIR)\jdatadst.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdatasrc.c

"$(INTDIR)\jdatasrc.obj"	"$(INTDIR)\jdatasrc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdcoefct.c

"$(INTDIR)\jdcoefct.obj"	"$(INTDIR)\jdcoefct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdcolor.c

"$(INTDIR)\jdcolor.obj"	"$(INTDIR)\jdcolor.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jddctmgr.c

"$(INTDIR)\jddctmgr.obj"	"$(INTDIR)\jddctmgr.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdhuff.c

"$(INTDIR)\jdhuff.obj"	"$(INTDIR)\jdhuff.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdinput.c

"$(INTDIR)\jdinput.obj"	"$(INTDIR)\jdinput.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdmainct.c

"$(INTDIR)\jdmainct.obj"	"$(INTDIR)\jdmainct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdmarker.c

"$(INTDIR)\jdmarker.obj"	"$(INTDIR)\jdmarker.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdmaster.c

"$(INTDIR)\jdmaster.obj"	"$(INTDIR)\jdmaster.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdmerge.c

"$(INTDIR)\jdmerge.obj"	"$(INTDIR)\jdmerge.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdphuff.c

"$(INTDIR)\jdphuff.obj"	"$(INTDIR)\jdphuff.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdpostct.c

"$(INTDIR)\jdpostct.obj"	"$(INTDIR)\jdpostct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdsample.c

"$(INTDIR)\jdsample.obj"	"$(INTDIR)\jdsample.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jdtrans.c

"$(INTDIR)\jdtrans.obj"	"$(INTDIR)\jdtrans.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jerror.c

"$(INTDIR)\jerror.obj"	"$(INTDIR)\jerror.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jfdctflt.c

"$(INTDIR)\jfdctflt.obj"	"$(INTDIR)\jfdctflt.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jfdctfst.c

"$(INTDIR)\jfdctfst.obj"	"$(INTDIR)\jfdctfst.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jfdctint.c

"$(INTDIR)\jfdctint.obj"	"$(INTDIR)\jfdctint.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jidctflt.c

"$(INTDIR)\jidctflt.obj"	"$(INTDIR)\jidctflt.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jidctfst.c

"$(INTDIR)\jidctfst.obj"	"$(INTDIR)\jidctfst.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jidctint.c

"$(INTDIR)\jidctint.obj"	"$(INTDIR)\jidctint.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jidctred.c

"$(INTDIR)\jidctred.obj"	"$(INTDIR)\jidctred.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jmemansi.c

"$(INTDIR)\jmemansi.obj"	"$(INTDIR)\jmemansi.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jmemdos.c
SOURCE=.\jmemmac.c
SOURCE=.\jmemmgr.c

"$(INTDIR)\jmemmgr.obj"	"$(INTDIR)\jmemmgr.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jmemname.c
SOURCE=.\jmemnobs.c
SOURCE=.\jpegtran.c
SOURCE=.\jquant1.c

"$(INTDIR)\jquant1.obj"	"$(INTDIR)\jquant1.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jquant2.c

"$(INTDIR)\jquant2.obj"	"$(INTDIR)\jquant2.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\jutils.c

"$(INTDIR)\jutils.obj"	"$(INTDIR)\jutils.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdbmp.c

"$(INTDIR)\rdbmp.obj"	"$(INTDIR)\rdbmp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdcolmap.c

"$(INTDIR)\rdcolmap.obj"	"$(INTDIR)\rdcolmap.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdgif.c

"$(INTDIR)\rdgif.obj"	"$(INTDIR)\rdgif.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdjpgcom.c
SOURCE=.\rdppm.c

"$(INTDIR)\rdppm.obj"	"$(INTDIR)\rdppm.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdrle.c

"$(INTDIR)\rdrle.obj"	"$(INTDIR)\rdrle.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdswitch.c

"$(INTDIR)\rdswitch.obj"	"$(INTDIR)\rdswitch.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rdtarga.c

"$(INTDIR)\rdtarga.obj"	"$(INTDIR)\rdtarga.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\transupp.c

"$(INTDIR)\transupp.obj"	"$(INTDIR)\transupp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wrbmp.c

"$(INTDIR)\wrbmp.obj"	"$(INTDIR)\wrbmp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wrgif.c

"$(INTDIR)\wrgif.obj"	"$(INTDIR)\wrgif.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wrjpgcom.c

!IF  "$(CFG)" == "JPEGLib - Win32 Release"


"$(INTDIR)\wrjpgcom.obj"	"$(INTDIR)\wrjpgcom.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug"

!ELSEIF  "$(CFG)" == "JPEGLib - Win32 Debug Testing"

!ENDIF 

SOURCE=.\wrppm.c

"$(INTDIR)\wrppm.obj"	"$(INTDIR)\wrppm.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wrrle.c

"$(INTDIR)\wrrle.obj"	"$(INTDIR)\wrrle.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wrtarga.c

"$(INTDIR)\wrtarga.obj"	"$(INTDIR)\wrtarga.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

