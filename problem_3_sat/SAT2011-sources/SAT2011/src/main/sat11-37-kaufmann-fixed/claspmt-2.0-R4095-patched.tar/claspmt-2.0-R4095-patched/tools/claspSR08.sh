#!/bin/bash
if [ -z "$1" ]; then 
echo usage: $0 instance
exit
fi
if [ -z "$SATTIMEOUT" ]
then
maxPreTime=150
else
maxPreTime=$[$SATTIMEOUT/5]
fi
./clasp 1 -f "$1" --rand-w=false --sat-p=-1,50,$maxPreTime 
