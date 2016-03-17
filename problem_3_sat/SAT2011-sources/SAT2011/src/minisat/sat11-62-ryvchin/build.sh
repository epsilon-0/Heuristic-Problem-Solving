#!/bin/sh
export MROOT=$PWD
#echo $MROOT
cd simp
gmake clean
gmake r
cp minisat_release ../lr_gl_shr
