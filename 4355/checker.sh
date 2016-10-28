#!/bin/bash
t=0
while [ $t -lt 10000 ]
do
	let "t=$t+1"
	python gen.py>b.in
	python b.py<b.in>b.out
	./4355<b.in>std.out
	if diff b.out std.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done