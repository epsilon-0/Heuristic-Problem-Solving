## Template for Makefile

unexport

LIB_DIR   ?= ../../lib
BIN_DIR   ?= ../../bin
INC_DIR   ?= ../../inc

SUBDIR    ?= 
LYFUNC    ?= 
CSRCS     ?= $(wildcard *.cpp)
CXXSRCS   ?= $(filter %.cpp, $(CSRCS)) $(filter %.cc, $(CSRCS))
CCSRCS    ?= $(filter %.c, $(CSRCS))
CHDRS     ?= $(wildcard *.h)
SCOBJS    ?= $(addsuffix .o, $(basename $(CSRCS)))
DCOBJS    ?= $(addsuffix .od, $(basename $(CSRCS)))
RCOBJS    ?= $(addsuffix .or, $(basename $(CSRCS)))
PCOBJS    ?= $(addsuffix .op, $(basename $(CSRCS)))
COBJS     :=

LIBADD    ?=
CLIBS     ?= $(addprefix -l,$(LIBADD))
LIBDIRS   ?= $(addprefix -L,$(LIB_DIR))

BIN       ?= 
LIB       ?= $(notdir $(shell pwd))
CXX       ?= g++
CC        ?= gcc
CFLAGS    ?= -Wall
CCFLAGS   ?= -Wall
FFLAGS    ?= -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -fno-builtin-calloc -fno-builtin-cfree \
	     -fno-builtin-memalign -fno-builtin-posix_memalign -fno-builtin-valloc -fno-builtin-pvalloc 
LFLAGS    ?= 
COPTIMIZE ?= 

LIBRARY    = $(addprefix lib, $(addsuffix .a, $(LIB) ) )
LYOBJS     =
CFLAGS    += $(COPTIMIZE)
CCFLAGS   += $(COPTIMIZE)
CLNDIR     = $(addsuffix .clean, $(SUBDIR))
LEX        = flex
YACC       = bison
MAKECMD    = make
STRIPCMD   ?= 

.PHONY : s d r p $(SUBDIR) $(CLNDIR) $(LYFUNC) $(LYCLAIM) clean test all

ifdef BIN
s:	$(SCOBJS) $(BIN)
d:	$(DCOBJS) $(BIN)_debug
r:	$(RCOBJS) $(BIN)_release
p:      $(PCOBJS) $(BIN)_profile
else
s:	$(SCOBJS) $(LIBRARY)
d:	$(DCOBJS) $(LIBRARY) 
r:	$(RCOBJS) $(LIBRARY)
p:      $(PCOBJS) $(LIBRARY)
endif
## Compile options
s:	COBJS += $(SCOBJS)
d:	COBJS += $(DCOBJS)
r:      COBJS += $(RCOBJS)
p:      COBJS += $(PCOBJS)
s:	CFLAGS +=-g -O3
d:	CFLAGS +=-g
r:	CFLAGS +=-O3 -DNDEBUG
p:      CFLAGS +=-pg -O3 -DNDEBUG
d:	MAKECMD = make d
r:	MAKECMD = make r
p:      MAKECMD = make p
r:	STRIPCMD = strip $@ 
$(SUBDIR):	SUBDIR =   
## Link options

## Dependencies

$(BIN) : $(COBJS)
$(BIN)_debug : $(DCOBJS)
$(BIN)_release : $(RCOBJS)
$(BIN)_profile : $(PCOBJS)
## Build rule
%.o %.od %.or %.op: %.c
	@echo Compiling: "$@ ( $< )"
	$(CC) $(CCFLAGS) -c -o $@ $<

%.o %.od %.or %.op: %.cpp
	@echo Compiling: "$@ ( $< )"
	$(CXX) $(CFLAGS) $(FFLAGS) -c -o $@ $<

%.o %.od %.or %.op: %.cc
	@echo Compiling: "$@ ( $< )"
	$(CXX) $(CFLAGS) $(FFLAGS) -c -o $@ $<

%.cpp : %.y %.l
	@echo Lex and Yacc: "$(LYPREFIX) ( $^ )"
	@$(YACC) -d -p $(LYPREFIX) -o $@ $*.y
	@$(LEX) -P$(LYPREFIX) -t $*.l >> $@
	@cp $@ $(addsuffix .cxx, $(basename $@))
	
## Binary rules 
	
$(BIN) $(BIN)_debug $(BIN)_release $(BIN)_profile: $(SUBDIR) $(LYFUNC)
	@echo Linking: "$@ ( $^ )"
	$(CXX) $(CFLAGS) $(FFLAGS) -o $@ $(COBJS) $(LYOBJS) $(LIBDIRS) $(CLIBS) $(CLIBS) 
	@$(STRIPCMD)
ifdef BIN_DIR
	@mv $@ $(BIN_DIR)
endif

## Library rule
$(LIBRARY): $(SUBDIR) $(LYFUNC) 
	@echo Library: "$@ ( $(COBJS) $(LYOBJS) )" 
	@rm -f $@
#ar cq
	@ar cur $@ $(COBJS) $(LYOBJS)
ifdef LIB_DIR
	@mv $@ $(LIB_DIR)
endif

## Lex Yacc rule

define LYFUNC_template
$(1): LYPREFIX = $(1)
$(1): $($(addsuffix _SRC,$(1))).o
LYOBJS += $($(addsuffix _SRC,$(1))).o
endef

$(foreach func,$(LYFUNC), $(eval $(call LYFUNC_template,$(func) ) ) )

$(LYFUNC):
	@rm -f $($@_SRC).cpp	
	
## Sub Directory Recursively Making rule
$(SUBDIR):
	@echo ------ Enter Directory: $@ ------
	@cd $@ && ( $(MAKECMD) --no-print-directory; cd .. )

## Test rule
test: lib$(LIB).a
	@echo Linking: "$@ ( $^ )"
	@$(CXX) $(CFLAGS) $(FFLAGS) -o $@ -L$(LIB_DIR) -l$(LIB)	

## Clean rule
clean:  $(CLNDIR)
	@rm -f $(SCOBJS) $(DCOBJS) $(RCOBJS) $(PCOBJS) depend.mk

$(CLNDIR):
	@cd $(basename $@) && (make clean --no-print-directory; cd ..)
	
## Make dependencies
depend.mk: $(CSRCS) $(CHDRS)
	@echo Making dependencies ...
ifneq ($(CXXSRCS),)
	@$(CXX) $(CFLAGS) $(FFLAGS) -MM $(CXXSRCS) >> depend.mk
endif
ifneq ($(CCSRCS),)
	@$(CC) $(CCFLAGS) -MM $(CCSRCS) >> depend.mk
endif

ifneq ($(CSRCS),)
-include depend.mk
endif

