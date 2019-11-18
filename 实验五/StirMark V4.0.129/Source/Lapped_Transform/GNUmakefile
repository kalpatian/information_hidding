######################
#  Base directories  #
######################
#StirmakBenchDir = $(PWD)
BaseDir = /a/user/raynal/Source/Lapped_Transform
INCLUDEDIR = $(BaseDir)
BINDIR     = $(BaseDir)/bin
LIBDIR     = $(BaseDir)/lib
OBJDIR     = $(BaseDir)/Objects

##################
#  Needed tools  #
##################
MAKE   = gmake
CC     = g++
C      = gcc
AR     = ar
RANLIB = ranlib

############################
#  Some compilation flags  #
############################
INC_PATH  = -I$(INCLUDEDIR) -I.
LINK_PATH = -L$(LIBDIR)
COMP_OPTS = -O2 $(INC_PATH)
LINK_OPTS = $(LINK_PATH) $(LINK_LIB)
AR_OPTS   = rcs
DYNL_OPTS = -shared
DYNC_OPTS = -fPIC


CC_SRC = 


C_SRC =  FDCT.C \
	 FDCTIV2.C \
	 FELT.C \
	 FLOT.C \
	 RSFFT.C \
	 FDCTIV.C \
	 FDHT.C \
	 FELT2.C \
	 FLOT2.C \
	 SRFFT.C


EXENAME = 
LIBNAME = liblt.a

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

ifneq ($(CC_SRC), )
  COMP_OPTS := $(COMP_OPTS)
  CC_OBJ = $(CC_SRC:%.cpp=$(OBJDIR)/%.opp)
  LINKER = $(CC)
  LINK_OPTS := 
else
  CC_OBJ =
endif

ifneq ($(C_SRC), )
  COMP_OPTS := $(COMP_OPTS) -x c
  C_OBJ = $(C_SRC:%.C=$(OBJDIR)/%.o)
  LINKER = $(C)
  $(LINK_OPTS) := $(LINK_OPTS)
else
  C_OBJ =
endif

all: startup $(LIB) $(EXE)

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

$(CC_OBJ):  $(OBJDIR)/%.opp  : %.cpp
	@echo Compiling C++ Souce files
	$(CC) -c $(COMP_OPTS) $< -o $@

$(C_OBJ):  $(OBJDIR)/%.o : %.C
	@echo Compiling C Souce files
	$(C) -c $(COMP_OPTS) $< -o $@


clean :
ifneq ($(LIB), )
	$(RM) $(LIB)
endif
ifneq ($(EXE), )
	$(RM) $(EXE)
endif
	rm -f $(CC_OBJ) $(C_OBJ)