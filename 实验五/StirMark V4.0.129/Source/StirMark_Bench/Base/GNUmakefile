include ../StirMark.tmpl

SRCDIR = $(StirmakBench)/Base

CC_SRC = SMBBench.cpp \
	SMBDatabase.cpp \
	SMBError.cpp \
	SMBException.cpp \
	SMBFileException.cpp \
	SMBImage.cpp \
	SMBImageList.cpp \
	SMBLog.cpp \
	SMBMarkingScheme.cpp \
	SMBMatrix.cpp \
	SMBMemoryException.cpp \
	SMBQuality.cpp \
	SMBRandomNumberGenerator.cpp \
	SMBString.cpp \
	SMBTools.cpp


CC_BENCH = StirMarkBenchmark.cpp
CC_SRC_BENCH = $(CC_SRC) $(CC_BENCH)

CC_TEST = SMBProgramTesting.cpp
CC_SRC_TEST = $(CC_SRC) $(CC_TEST)

CC_SRC_ALL = $(CC_SRC) $(CC_TEST) $(CC_BENCH)

C_SRC =

EXENAME = smb
LIBNAME = 

ifneq ($(EXENAME), )
  EXE = $(BINDIR)/$(EXENAME)
  EXETEST = $(BINDIR)/testsmb
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
  CC_OBJ_BENCH = $(CC_SRC_BENCH:%.cpp=$(OBJDIR)/%.opp)
  CC_OBJ_TEST = $(CC_SRC_TEST:%.cpp=$(OBJDIR)/%.opp)
  CC_OBJ_ALL = $(CC_SRC_ALL:%.cpp=$(OBJDIR)/%.opp)
  LINKER = $(CC)
  LINK_OPTS := $(LINK_OPTS) -lSelfSim -lTest -lSigProc -lSpecTrans -lGeoTrans $(LIBJPEG) -ldl
  DYNL_OPTS := $(DYNL_OPTS)
else
  CC_OBJ =
endif

ifneq ($(C_SRC), )
  COMP_OPTS := $(COMP_OPTS)
  C_OBJ = $(C_SRC:%.c=$(OBJDIR)/%.o)
  LINKER = $(C)
  LINK_OPTS := $(LINK_OPTS)
  $(DYNL_OPTS) := $(DYNL_OPTS)
else
  C_OBJ =
endif

all: startup $(LIB) $(EXE) $(EXETEST)

obj: startup $(C_OBJ) $(CC_OBJ_ALL)

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
ifneq ($(SO), )
	@echo XX "  "  "so        :" $(SO)
endif
	@echo XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

$(EXETEST): startup $(C_OBJ) $(CC_OBJ_TEST) 
	$(LINKER)  $(C_OBJ) $(CC_OBJ_TEST) -o $(EXETEST) $(LINK_OPTS)

$(EXE) : $(C_OBJ) $(CC_OBJ_BENCH)
	$(RM) $(EXE)
	$(LINKER)  $(C_OBJ) $(CC_OBJ_BENCH) -o $(EXE) $(LINK_OPTS)


$(LIB) : $(C_OBJ) $(CC_OBJ)
	$(AR) $(AR_OPTS) $@ $(C_OBJ) $(CC_OBJ_BENCH)
	$(RANLIB) $@

$(SO) : $(C_OBJ) $(CC_OBJ)
	$(LINKER) $(C_OBJ) $(CC_OBJ) $(DYNL_OPTS) -o $(SO)

$(CC_OBJ_ALL):  $(OBJDIR)/%.opp  : %.cpp
	@echo Compiling C++ Souce files
	$(CC) -c $(COMP_OPTS) $< -o $@

$(C_OBJ):  $(OBJDIR)/%.o : %.c
	@echo Compiling C Souce files
	$(C) -c $(COMP_OPTS) $< -o $@


clean :
ifneq ($(LIB), )
	$(RM) $(LIB)
endif
ifneq ($(EXE), )
	$(RM) $(EXE)
	$(RM) $(EXETEST)
endif
	$(RM) $(CC_OBJ_ALL) $(C_OBJ)