## Process this file with automake to produce Makefile.in
# Makefile for generating plot data from LK output.
# $Id: Makefile.am,v 1.8 1997/11/22 17:58:15 neto Exp neto $
# Requires GNU make (pattern rules, functions).
# vi :set tw=0 sw=4 ts=4:

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

EXTRA_DIST = 0.0 expttest expttsp exptmatch expttsphk

dist-hook : 
	cp -r RCS $(distdir)

scriptdir=../script

comma=,
dollar=\$$


# LK output files names are of the form:
# 	out.<instance-basename>.<massage-key>.<permutation>.<lk-kind>.gz
# e.g.
#	out.dsj1000.c.5.deg.gz

# <massage-key> is of form <rotate><sfc><clone>, where
# 
# <rotate> is r if the instance was rotated instead of having its s cities
# randomly renamed.  Otherwise it is empty
# 
# <sfc> is s if LK reordered the cities by Moore's space-filling curve.
# Otherwise it is empty
#
# <clone> is c if this instance is a clone of the instance instead of the
# original instance itself.  Otherwise it is empty

# <permutation> is a number, usually 0 through 5.  It affects
# the massaging.  If the massage is a random renaming, the number
# is the seed used for the reordering, with 0 being the identity
# permutation.  If the massage is a rotation, the number is the
# number of radians by which the instance is rotated.

# <lk-kind> is one of
# 	no_d indicating no declustering
# 	deg indicating declustering in eligibility test and greedy selection

#permnumbers		= 0 1 2 3 4 5
permnumbers		= 0 1 2
permutations 	= $(foreach n,$(permnumbers),$(massagekey).$(n) )

plotno_d 	=with lines
plotdeg  	=with linespoints
cfplotno_d	=with lines
cfplotdeg	=with points

plotfiles ='$(foreach perm,$(permutations),"$*.$(perm).LKKIND.DATA.gpl" PLOTOPTION$(comma))'

no_dplotfiles	=$(subst PLOTOPTION,$(plotno_d),$(subst LKKIND,no_d,$(plotfiles)))
degplotfiles	=$(subst PLOTOPTION,$(plotdeg),$(subst LKKIND,deg,$(plotfiles)))
plotline 		= plot $(no_dplotfiles) $(degplotfiles)
milemileplotline= plot \"0.0\" with lines, $(no_dplotfiles) $(degplotfiles)

cfno_dplotfiles =$(subst PLOTOPTION,$(cfplotno_d),$(subst LKKIND,no_d,$(plotfiles)))
cfdegplotfiles  =$(subst PLOTOPTION,$(cfplotdeg),$(subst LKKIND,deg,$(plotfiles)))
cfcfplotline    =plot \"0.0\" with lines, $(no_dplotfiles) $(degplotfiles)

mileplotline 	= $(subst DATA,mile,$(milemileplotline))
cfplotline 		= $(subst DATA,cf,$(cfcfplotline))
probeplotline 	= $(subst DATA,probe,$(plotline))
moveplotline 	= $(subst DATA,move,$(plotline))
improveplotline = $(subst DATA,improve,$(plotline))

gpl = if [ -r out.$*.$(perm).$(lkkind).gz ]; then make $*.$(perm).$(lkkind).DATA.gpl ;fi;

cfgpl 	= out.$*.$(perm).$(lkkind)
milegpl 		= $(subst DATA,mile,$(gpl))
probegpl 		= $(subst DATA,probe,$(gpl))
movegpl 		= $(subst DATA,move,$(gpl))
improvegpl 		= $(subst DATA,improve,$(gpl))

allmilegpl 		= $(foreach lkkind,no_d deg,$(milegpl))
allcfgpl 		= $(foreach lkkind,deg no_d,$(cfgpl))
allprobegpl 	= $(foreach lkkind,no_d deg,$(probegpl))
allmovegpl 		= $(foreach lkkind,no_d deg,$(movegpl))
allimprovegpl 	= $(foreach lkkind,no_d deg,$(improvegpl))

plttops = \
	echo set term postscript landscape monochrome >$@.tmp; \
	grep -v pause <`echo $@ | sed s/\.ps/\.plt/` >>$@.tmp; \
	gnuplot $@.tmp >$@; \
	rm -f $@.tmp


%.ps : Makefile %.plt
	$(plttops)

%..cf.plt : Makefile
	make massagekey= $*.cf.plt
%..mile.plt : Makefile
	make massagekey= $*.mile.plt
%..probe.plt : Makefile
	make massagekey= $*.probe.plt
%..improve.plt : Makefile
	make massagekey= $*.improve.plt
%..move.plt : Makefile
	make massagekey= $*.move.plt

%.r.cf.plt : Makefile
	make massagekey=r $*.cf.plt
%.r.mile.plt : Makefile
	make massagekey=r $*.mile.plt
%.r.probe.plt : Makefile
	make massagekey=r $*.probe.plt
%.r.improve.plt : Makefile
	make massagekey=r $*.improve.plt
%.r.move.plt : Makefile
	make massagekey=r $*.move.plt

%.s.cf.plt : Makefile
	make massagekey=s $*.cf.plt
%.s.mile.plt : Makefile
	make massagekey=s $*.mile.plt
%.s.probe.plt : Makefile
	make massagekey=s $*.probe.plt
%.s.improve.plt : Makefile
	make massagekey=s $*.improve.plt
%.s.move.plt : Makefile
	make massagekey=s $*.move.plt

%.c.cf.plt : Makefile
	make massagekey=c $*.cf.plt
%.c.mile.plt : Makefile
	make massagekey=c $*.mile.plt
%.c.probe.plt : Makefile
	make massagekey=c $*.probe.plt
%.c.improve.plt : Makefile
	make massagekey=c $*.improve.plt
%.c.move.plt : Makefile
	make massagekey=c $*.move.plt

%.rs.cf.plt : Makefile
	make massagekey=rs $*.cf.plt
%.rs.mile.plt : Makefile
	make massagekey=rs $*.mile.plt
%.rs.probe.plt : Makefile
	make massagekey=rs $*.probe.plt
%.rs.improve.plt : Makefile
	make massagekey=rs $*.improve.plt
%.rs.move.plt : Makefile
	make massagekey=rs $*.move.plt

%.rc.cf.plt : Makefile
	make massagekey=rc $*.cf.plt
%.rc.mile.plt : Makefile
	make massagekey=rc $*.mile.plt
%.rc.probe.plt : Makefile
	make massagekey=rc $*.probe.plt
%.rc.improve.plt : Makefile
	make massagekey=rc $*.improve.plt
%.rc.move.plt : Makefile
	make massagekey=rc $*.move.plt

%.sc.cf.plt : Makefile
	make massagekey=sc $*.cf.plt
%.sc.mile.plt : Makefile
	make massagekey=sc $*.mile.plt
%.sc.probe.plt : Makefile
	make massagekey=sc $*.probe.plt
%.sc.improve.plt : Makefile
	make massagekey=sc $*.improve.plt
%.sc.move.plt : Makefile
	make massagekey=sc $*.move.plt

%.rsc.cf.plt : Makefile
	make massagekey=rsc $*.cf.plt
%.rsc.mile.plt : Makefile
	make massagekey=rsc $*.mile.plt
%.rsc.probe.plt : Makefile
	make massagekey=rsc $*.probe.plt
%.rsc.improve.plt : Makefile
	make massagekey=rsc $*.improve.plt
%.rsc.move.plt : Makefile
	make massagekey=rsc $*.move.plt


%.cf.plt : Makefile
	zcat $(foreach perm,$(permutations),$(allcfgpl)) | $(scriptdir)/cfresults.pl
	$(foreach perm,$(permnumbers),$(foreach lkkind,deg no_d,mv cf.$(perm).$(lkkind) $*.$(massagekey).$(perm).$(lkkind).cf.gpl; ))
	echo set title \"LK compared with LK+decluster \(% vs. time\)\" >$*.$(massagekey).cf.plt
	echo $(cfplotline) | sed -e s#,$(dollar)##g >>$*.$(massagekey).cf.plt
	echo pause -1 >>$*.$(massagekey).cf.plt

%.mile.plt :
	$(foreach perm,$(permutations),$(allmilegpl))
	echo set title \"Percentage milestones vs. time\" >$*.$(massagekey).mile.plt
	echo $(mileplotline) | sed -e s#,$(dollar)##g >>$*.$(massagekey).mile.plt
	echo pause -1 >>$*.$(massagekey).mile.plt

%.probe.plt :
	$(foreach perm,$(permutations),$(allprobegpl))
	echo set title \"Histogram of probe depths\" >$*.$(massagekey).probe.plt
	echo $(probeplotline) | sed -e s#,$(dollar)##g >>$*.$(massagekey).probe.plt
	echo pause -1 >>$*.$(massagekey).probe.plt

%.move.plt :
	$(foreach perm,$(permutations),$(allmovegpl))
	echo set title \"Histogram of move depths\" >$*.$(massagekey).move.plt
	echo $(moveplotline) | sed -e s#,$(dollar)##g >>$*.$(massagekey).move.plt
	echo pause -1 >>$*.$(massagekey).move.plt

%.improve.plt :
	$(foreach perm,$(permutations),$(allimprovegpl))
	echo set title \"Tour length vs. time\" >$*.$(massagekey).improve.plt
	echo $(improveplotline) | sed -e s#,$(dollar)##g >>$*.$(massagekey).improve.plt
	echo pause -1 >>$*.$(massagekey).improve.plt

%.probe.gpl : out.%.gz
	$(scriptdir)/probe.pl $<
	mv probe.gpl $@

%.move.gpl %.: out.%.gz
	$(scriptdir)/probe.pl $<
	mv move.gpl $@

%.mile.gpl %.: out.%.gz
	$(scriptdir)/milestone.pl $<
	mv milestone.gpl $@

%.improve.gpl %.: out.%.gz
	$(scriptdir)/improve.pl $<
	mv improve.gpl $@

%.cost.gpl %.: out.%.gz
	$(scriptdir)/cd.pl $<
	mv cost.gpl $@

%.decd.gpl %.: out.%.gz
	$(scriptdir)/cd.pl $<
	mv decd.gpl $@

%.prd.gpl %.: out.%.gz
	$(scriptdir)/cd.pl $<
	mv prd.gpl $@


clean :
	rm -f *.plt

veryclean :  clean
	rm -f *.gpl

