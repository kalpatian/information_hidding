include ../StirMark.tmpl

SRCDIR = $(StirmakBench)/SpecialTransforms

CC_SRC = SMBST_Cropping.cpp \
	SMBST_RemoveLines.cpp \
	SMBST_Transposition.cpp \
	SMBST_Identity.cpp \
	SMBST_HFlip.cpp \
	SMBST_DFlip.cpp \
	SMBST_AFlip.cpp \
	SMBST_VFlip.cpp \
	SMBST_Rot90.cpp \
	SMBST_Rot180.cpp \
	SMBST_Rot270.cpp 

C_SRC =

EXENAME = 
LIBNAME = libSpecTrans.a
SONAME  = libSpecTrans.so

ifneq ($(EXENAME), )
  EXE = $(BINDIR)/$(EXENAME)
else
  EXE =
endif

ifneq ($(LIBNAME), )
  LIB = $(LIBDIR)/$(LIBNAME)
else
  LIB =
endif

ifneq ($(SONAME), )
  SO = $(LIBDIR)/$(SONAME)
else
  SO =
endif

ifneq ($(CC_SRC), )
  COMP_OPTS := $(COMP_OPTS)  $(DYNC_OPTS)
  CC_OBJ = $(CC_SRC:%.cpp=$(OBJDIR)/%.opp)
  LINKER = $(CC)
  LINK_OPTS := $(LINK_OPTS)
  DYNL_OPTS := $(DYNL_OPTS)
else
  CC_OBJ =
endif

ifneq ($(C_SRC), )
  COMP_OPTS := $(COMP_OPTS) $(DYNC_OPTS)
  C_OBJ = $(C_SRC:%.c=$(OBJDIR)/%.o)
  LINKER = $(C)
  LINK_OPTS := $(LINK_OPTS)
  DYNL_OPTS := $(DYNL_OPTS)
else
  C_OBJ =
endif


all: startup $(LIB) $(SO) $(EXE)

obj: startup $(C_OBJ) $(CC_OBJ)


startup:
	@echo XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	@echo XX "  "  "arch      :" $(MYCPU)
	@echo XX "  "  "linker    :" $(LINKER)
ifneq ($(CC_SRC), )
	@echo XX "  "  "ccsources :" $(CC_SRC)
	@echo XX "  "  "ccobj     :" $(CC_OBJ)
endif
ifneq ($(C_SRC), )
	@echo XX "  "  "csources  :" $(C_SRC)
	@echo XX "  "  "cobj      :" $(C_OBJ)
endif
ifneq ($(EXE), )
	@echo XX "  "  "exe       :" $(EXE)
endif
ifneq ($(LIB), )
	@echo XX "  "  "lib       :" $(LIB)
endif
	@echo XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

$(EXE) : $(C_OBJ) $(CC_OBJ)
	$(RM) $(EXE)
	$(LINKER)  $(C_OBJ) $(CC_OBJ) -o $(EXE) $(LINK_OPTS)


$(LIB) : $(C_OBJ) $(CC_OBJ)
	$(AR) $(AR_OPTS) $@ $(C_OBJ) $(CC_OBJ)
	$(RANLIB) $@

$(SO) : $(C_OBJ) $(CC_OBJ)
	$(LINKER) $(DYNL_OPTS) $(C_OBJ) $(CC_OBJ) -o $(SO)

$(CC_OBJ):  $(OBJDIR)/%.opp  : %.cpp
	@echo Compiling C++ Souce files
	$(CC) -c $(COMP_OPTS) $< -o $@

$(C_OBJ):  $(OBJDIR)/%.o : %.c
	@echo Compiling C Souce files
	$(C) -c $(COMP_OPTS) $< -o $@


clean :
ifneq ($(LIB), )
	$(RM) $(LIB)
endif
ifneq ($(SO), )
	$(RM) $(SO)
endif
ifneq ($(EXE), )
	$(RM) $(EXE)
endif
	$(RM) $(CC_OBJ) $(C_OBJ)