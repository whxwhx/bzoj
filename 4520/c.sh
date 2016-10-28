#!/bin/bash
t=0
while [ $t -lt 100 ]
do
	let "t=$t+1"
	echo $RANDOM|./gen>4520.in
	./4520<4520.in>f.out
	./std<4520.in>s.out
	if diff f.out s.out; then
		echo "AC $t";
	else 
		echo "WA $t";
		break;
	fi
done