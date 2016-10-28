#!/bin/bash
t=0;
while [ $t -lt 100 ] 
do 
 let "t=$t+1";
 echo $RANDOM|./gen>4062.in
 time ./4062<4062.in>4062.out
 time ./hgr<4062.in>hgr.out
 if diff 4062.out hgr.out; then
 	echo "AC $t";
 else
 	echo "WA $t";
 	break;
 fi;
done