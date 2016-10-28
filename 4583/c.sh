#!/bin/bash
t=0
while [ $t -lt 10 ]
do
	let "t=$t+1";
	cp shopping$t.in shopping.in
	time ./4583<shopping.in>shopping.out
	if diff -w --side-by-side shopping.out shopping$t.out; then
		echo "AC $t";
	else 
		echo "WA $t";
		break;
	fi
done