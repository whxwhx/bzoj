#!/bin/bash
t=0
b=19
while [ $t -lt $b ]
do
	let "t=$t+1"
	time ./4069_bitset<sculpture_8_$t.in>$t.out;
	if diff $t.out sculpture_8_$t.out; then
		echo "AC $t";
	else 
		echo "WA $t";
		break;
	fi;
done
