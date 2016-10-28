#!/bin/bash
t=0
while [ $t -lt 100 ] 
do 
	let "t=$t+1"
	echo $RANDOM|./gen>4310.in
	./4310<4310.in>4310.out
	./claris<4310.in>c.out
	if diff 4310.out c.out; then
		echo "AC $t cases";
	else
		echo "WA at No.$t case";
		break;
	fi
done
