#!/bin/bash
t=0
while [ $t -lt 1000 ]
do
	let "t=$t+1"
	echo $RANDOM|./gen>t.in
	./force<t.in>f.out
	./4227<t.in>t.out
	if diff -w f.out t.out; then
		echo "AC $t";
	else 
		echo "WA $t";
		break;
	fi
done