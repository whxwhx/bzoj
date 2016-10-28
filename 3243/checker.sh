#!/bin/bash
t=0
while [ $t -lt 100 ] 
do 
	let "t=$t+1"
	echo $RANDOM|./gen>3243.in
	./3243_1<3243.in>3243_1.out
	./3243_2<3243.in>3243_2.out
	if diff 3243_1.out 3243_2.out; then
		echo "AC $t cases";
	else
		echo "WA at No.$t case";
		break;
	fi
done
