## Process this file with automake to produce Makefile.in
# Makefile for generating scripts related to program LK.

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

EXTRA_DIST = README  \
att2upper.pl.in \
cd.pl.in \
cfresults.pl.in \
cfresults.pl.in.new \
countpages.pl.in \
domst.pl.in \
doshake.pl.in \
doshakelk.pl.in \
expt.pl.in \
GB_flip.pm.in \
hist.pl.in \
improve.pl.in \
least.pl.in \
lkdoit.in \
lkdoitcmp.in \
milestone.pl.in \
mkcwebch.pl.in \
mstelratio.pl.in \
mstrsortlen.pl.in \
mstsortlen.pl.in \
myps2eps.pl.in \
number.pl.in \
PRNG.pm.in \
probe.pl.in \
results.pl.in \
spectrum.pl.in \
TSP.pm.in \
tsp2dm.pl.in \
tspbgen.pl.in \
tspreorder.pl.in \
tsprotate.pl.in

bin_SCRIPTS = \
att2upper.pl \
cd.pl \
cfresults.pl \
countpages.pl \
domst.pl \
doshake.pl \
doshakelk.pl \
expt.pl \
GB_flip.pm \
hist.pl \
improve.pl \
least.pl \
lkdoit \
lkdoitcmp \
milestone.pl \
mkcwebch.pl \
mstelratio.pl \
mstrsortlen.pl \
mstsortlen.pl \
myps2eps.pl \
number.pl \
PRNG.pm.in \
probe.pl \
results.pl \
spectrum.pl \
TSP.pm \
tsp2dm.pl \
tspbgen.pl \
tspreorder.pl \
tsprotate.pl

# A hack to use the SCRIPTS before a full-blown install.
myall :
	chmod +x $(bin_SCRIPTS)

# Distribute RCS files too.
dist-hook :
	cp -r RCS $(distdir)
