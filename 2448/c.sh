#!/bin/bash
t=0
while [ $t -lt 100 ]
do
	let "t=$t+1"
	echo $RANDOM|./gen>t.in
	./2448<t.in>t.out
	./force<t.in>f.out
	if diff -w t.out f.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done