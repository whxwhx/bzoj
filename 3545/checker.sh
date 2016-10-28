#!/bin/bash
t=0;
while [ $t -lt 100 ] 
do 
 let "t=$t+1";
 echo $RANDOM|./gen>3545.in
 time ./3545<3545.in>3545.out
 time ./hzwer<3545.in>hzwer.out
 if diff 3545.out hzwer.out; then
 	echo "AC $t";
 else
 	echo "WA $t";
 	break;
 fi;
done