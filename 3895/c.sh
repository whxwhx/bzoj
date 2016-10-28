#!/bin/bash
t=0
while [ $t -lt 10 ]
do
	echo $RANDOM|./gen>t.in
	./3895<t.in>3895.out
	./std<t.in>std.out
	if diff -w std.out 3895.out; then
		echo "AC $t";
	else 
		echo "WA $t";
	fi
	let "t=$t+1";
done