#!/bin/bash
sixty_four=63
one=2
line_cnt=$(wc -l < $1)
#echo $line_cnt
if [ "$line_cnt" -lt 64 ];
then
	python ut1.py $1 inputform.in
	./bin/gsieve -f inputform.in > tempmat
	./bin/print_result inputform.in tempmat > $2
else
	python ut1.py $1 inputform.in
	./bin/trysample $1 inputform.in > tempmat
	./bin/print_result inputform.in tempmat > $2
fi