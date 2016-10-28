#!/bin/bash
t=0
while [ $t -lt 100 ] 
do 
	let "t=$t+1"
	python ./gen.py>4311.in
	python ./b.py<4311.in>b.out
	./4311 <4311.in>4311.out
	if diff b.out 4311.out; then
		echo "AC $t cases";
	else
		echo "WA at No.$t case";
		break;
	fi
done
