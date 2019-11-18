include ./StirMark.tmpl

SUBDIRS = GeometricTransforms \
	SignalProcessing/SelfSimilarities/\
	SignalProcessing \
	SpecialTransforms \
	Tests \
	Base

NEEDEDDIRS = $(INCLUDEDIR) $(BINDIR) $(LIBDIR)  $(OBJDIR)


all:
#Creating the directories
	@$(RM) ./bin/smb

	@for i in $(NEEDEDDIRS) ;\
	do \
	  if test ! -d $$i; then \
	    echo "Creating directory $$i"; \
	    mkdir $$i; \
	  fi; \
	done

	@for i in $(SUBDIRS) ; \
	do \
	  echo "Enterring $$i" ; \
	  cd $$i && $(MAKE) all && cd - ; \
	done

	@echo "";
	@echo "";
	@echo "";
	@echo "==============================================================";
	@echo "  Don't forget to set your LD_LIBRARY_PATH";
	@echo "            BEFORE running 'smb'";
	@echo "  Libraries are located in $(LIBDIR)";
	@echo "==============================================================";
	@echo "";
	@echo "";
	@echo "";

clean:
	$(RM) $(OBJDIR)/*opp
	@for i in $(SUBDIRS) ;\
	do \
	  echo "cleaning" all "from $$i..."; \
	  $(MAKE) -C $$i clean; \
	done
	find . -name "*~" -exec $(RM) {} \;

