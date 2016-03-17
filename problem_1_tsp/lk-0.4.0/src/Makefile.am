## Process this file with automake to produce Makefile.in
# Makefile for generating binary program LK from sources.
# $Id: Makefile.am,v 1.25 1998/05/23 16:24:54 neto Exp neto $

##   Copyright (C) 1994, 1995, 1996, 1997 David Neto
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation; either version 2, or (at your option)
##   any later version.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with this program; if not, write to the Free Software
##   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
##   02111-1307, USA.

## AUTOMAKE_OPTIONS = no-dependencies 

## These .w files are the *real* sources.
## File cwebmac.tex is required to typeset CWEB programs.  It is taken from
## the CWEB distribution.
EXTRA_DIST = \
	array.w construct.w copyrt.w decluster.w dict.w distcalc.w dsort.w \
	error.w fixincludes.w gb_flip.w gb_flip.ch \
	fullgrid.w ifs.w jbmr.w kdtree.w \
	length.w lk.w memory.w nn.w pool.w read.w resource.w sier.w tspgen.w \
	twolevel.w types.w unifd.w webdefs.w \
	cwebmac.tex compile.c.in \
	prng.w prngconfig.h \
	jitter.w \
	shake.w \
	prolog.ps \
	mkcwebch.pl \
	tspps.w \
	match.w \
	ascend.w \
	pq.w \
# Stanford GraphBase's boilerplate file.
	boilerplate.w

# Docs should also include ifs.dvi, but that also needs
# fern.eps nicecloud.eps tropicalfish.eps tropicalfisheye.eps

DOCS = array.dvi construct.dvi decluster.dvi dict.dvi distcalc.dvi dsort.dvi \
	error.dvi fixincludes.dvi gb_flip.dvi \
	fullgrid.dvi jbmr.dvi kdtree.dvi \
	length.dvi lk.dvi memory.dvi nn.dvi pool.dvi read.dvi resource.dvi  \
	sier.dvi tspgen.dvi \
	twolevel.dvi unifd.dvi \
	prng.dvi \
	jitter.dvi \
	shake.dvi \
	tspps.dvi \
	match.dvi \
	ascend.dvi \
	pq.dvi \
	upper.dvi

bin_PROGRAMS = lk tspgen jitter tspps shake \
	ifs fullgrid unifd sier distcalc \
	dsorttest dicttest declustertest test_flip prngtest pqtest

TESTS = test_flip dicttest declustertest prngtest dsorttest pqtest

lk_SOURCES = \
	array.c \
	array.h \
	construct.c \
	construct.h \
	declevel.h \
	decluster.c \
	decluster.h \
	dict.c \
	dict.h \
	dsort.c \
	dsort.h \
	error.c \
	error.h \
	fixincludes.h \
	gb_flip.c \
	gb_flip.h \
	jbmr.c \
	jbmr.h \
	kdtree.c \
	kdtree.h \
	length.h \
	match.c \
	match.h \
	lk.c \
	lk.h \
	lkconfig.h \
	memory.c \
	memory.h \
	nn.c \
	nn.h \
	pool.c \
	pool.h \
	prng.c \
	prng.h \
	pq.h \
	pq.c \
	read.c \
	read.h \
	resource.c \
	resource.h \
	twolevel.c \
	twolevel.h \
	ascend.c \
	ascend.h \
	compile.c 

tspgen_SOURCES = \
	dsort.c \
	dsort.h \
	error.c \
	error.h \
	memory.c \
	memory.h \
	gb_flip.c \
	gb_flip.h \
	tspgen.c

# read needs gb_flip.
tspps_SOURCES = \
	length.h \
	error.c \
	error.h \
	memory.c \
	memory.h \
	gb_flip.c \
	gb_flip.h \
	read.c \
	read.h \
	tspps.c

jitter_SOURCES = \
	decluster.h \
	decluster.c \
	dsort.c \
	dsort.h \
	error.c \
	error.h \
	kdtree.c \
	kdtree.h \
	memory.c \
	memory.h \
	gb_flip.c \
	gb_flip.h \
	pool.c \
	pool.h \
	prng.c \
	prng.h \
	prngconfig.h \
	pq.c \
	pq.h \
	read.h \
	read.c \
	jitter.c

shake_SOURCES = \
	decluster.h \
	decluster.c \
	dsort.c \
	dsort.h \
	error.c \
	error.h \
	kdtree.c \
	kdtree.h \
	memory.c \
	memory.h \
	gb_flip.c \
	gb_flip.h \
	pool.c \
	pool.h \
	prng.c \
	prng.h \
	prngconfig.h \
	pq.c \
	pq.h \
	read.h \
	read.c \
	shake.c

dist-hook : 
	rm -f $(distdir)/compile.c
	cp -r RCS $(distdir)


ifs_SOURCES = gb_flip.c gb_flip.h ifs.c
unifd_SOURCES = gb_flip.c gb_flip.h unifd.c
sier_SOURCES = gb_flip.c gb_flip.h sier.c
fullgrid_SOURCES = fullgrid.c
distcalc_SOURCES = error.h error.c memory.h memory.c read.c read.h \
	gb_flip.h gb_flip.c \
	length.h distcalc.c


BUILT_SOURCES = \
	array.c \
	array.h \
	compile.c \
	construct.c \
	construct.h \
	decluster.c \
	decluster.h \
    declustertest.c \
	dict.c \
	dict.h \
	dicttest.c \
	distcalc.c \
	dsort.c \
	dsort.h \
	dsorttest.c \
	error.c \
	error.h \
	fixincludes.h \
	gb_flip.c \
	gb_flip.h \
	fullgrid.c \
	ifs.c \
	jbmr.c \
	jbmr.h \
	kdtree.c \
	kdtree.h \
	length.h \
	lk.c \
	lk.h \
	memory.c \
	memory.h \
	nn.c \
	nn.h \
	pool.c \
	pool.h \
	prng.c \
	prng.h \
	prngtest.c \
	read.c \
	read.h \
	resource.c \
	resource.h \
	sier.c \
	test_flip.c \
	tspgen.c \
	twolevel.c \
	twolevel.h \
	unifd.c


# Programs required to process the .w sources.
# ctangle makes .w into .c and .h  (not necessarily both or either)
# cweave makes .w into .tex (.idx and .scn)
# tex makes .tex (and .idx and .scn) into .dvi
CTANGLE = @CTANGLE@
CWEAVE = @CWEAVE@
TEX = @TEX@

# Get default flags from confgure
CTANGLEFLAGS_DEFAULT = @CTANGLEFLAGS_DEFAULT@
CWEAVEFLAGS_DEFAULT = @CWEAVEFLAGS_DEFAULT@


# FIXME: separate tests 
test_flip_SOURCES = test_flip.c gb_flip.c gb_flip.h
dsorttest_SOURCES = dsort.c dsorttest.c
dicttest_SOURCES = dicttest.c dict.c dict.h \
	error.c memory.c pool.c gb_flip.c \
	error.h memory.h pool.h gb_flip.h 
pqtest_SOURCES = pqtest.c pq.c pq.h \
	error.c error.h
declustertest_SOURCES = declustertest.c decluster.c decluster.h \
	pq.c pq.h resource.c resource.h \
	error.c memory.c pool.c gb_flip.c kdtree.c read.c dsort.c \
	error.h memory.h pool.h gb_flip.h kdtree.h read.h dsort.h 

# If your compiler does not have inlining, then add prng.c to this list.
prngtest_SOURCES = error.c error.h memory.c memory.h gb_flip.c gb_flip.h \
	prng.c prng.h prngtest.c fixincludes.h

# All the DVI documentation is generated from the program sources.
docs : $(DOCS)

#########################################################################
# Implicit rules.
# .ch  -- CWEB change files; implicit .ch rules should precede implicit .w rules
# .w   -- CWEB files
# .tex -- TeX files
# .scn -- generated by CWEAVE and used by TeX to typeset programs
# .idx -- index files generated by CWEAVE and used by TeX to typeset programs
# .dvi -- device independent typeset files generated by TeX

SUFFIXES = .ch .w .c .h .o .tex .scn .idx .dvi

# When to run ctangle
.ch.c :
	@CTANGLE_CMD@

.w.c :
	@CTANGLE_CMD@

# Maybe need to fix this kludge for headers?
.ch.h :
	@CTANGLE_CMD@

.w.h :
	@CTANGLE_CMD@

# When to run cweave
.w.tex :
	@CWEAVE_CMD@
	
.w.idx :
	@CWEAVE_CMD@

.w.scn :
	@CWEAVE_CMD@

# When to run TeX
# We put $(srcdir) on TEXINPUTS path because it contains cwebmac.tex, which
# is required to typeset CWEB programs.
.tex.dvi :
	(TEXINPUTS=$(TEXINPUTS):$(srcdir);@TEX_CMD@)
 

