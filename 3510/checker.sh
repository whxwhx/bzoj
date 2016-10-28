#!/bin/bash
t=0
while [ $t -lt 100 ] 
do
	let "t=$t+1"
	echo $RANDOM|./gen>3510.in
	./3510<3510.in>3510.out
	./b<3510.in>b.out
	if diff 3510.out b.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done