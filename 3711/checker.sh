#!/bin/bash
t=0
while [ $t -lt 100 ] 
do 
	let "t=$t+1"
	echo $RANDOM|./gen>3711.in
	./3711<3711.in>3711.out
	./log2<3711.in>log2.out
	if diff 3711.out log2.out; then
		echo "AC $t cases";
	else
		echo "WA at No.$t case";
		break;
	fi
done
