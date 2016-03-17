CSRCS  = $(wildcard *.cc) $(wildcard base/*.cc) $(wildcard base/*.c)
LIB_DIR = ../../../lib
CFLAGS = -I. -DHAVE_CONFIG_H -DNO_TCMALLOC_SAMPLES -DNO_HEAP_CHECK  \
	-DNO_FRAME_POINTER   
CCFLAGS = -I.
include ../../template.mk

