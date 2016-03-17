#!/bin/bash

datadir="data/"
solndir="soln/"
invoke="java -jar ShortestVector.jar"
rm -rf "${solndir}"

#Problem 1
for n in 1 2 3 4 
do
  infile="${datadir}input${n}.in"
  outfile="${solndir}input${n}.out"
  echo "${infile}"
  ${invoke} ${infile} ${outfile}

  java -jar ./spec/evaluathor.jar "${infile}" "${outfile}"
done
echo

