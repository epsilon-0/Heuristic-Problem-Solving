LIB_DIR = ../lib 
BIN_DIR = ../
CFLAGS = -fopenmp
SUBDIR = cmain par techmap cnf aig truth cmd util cryptominisat google/tcmalloc 
SUBLIB = cmain par techmap cnf aig truth cmd util cryptominisat tcmalloc 
#SUBDIR = cmain par rwt techmap aig truth cmd util cryptominisat minisat 
#SUBLIB = cmain par rwt techmap aig truth cmd util cryptominisat minisat
LIBADD = pthread termcap readline z $(SUBLIB)
BIN = qutersat

include template.mk

