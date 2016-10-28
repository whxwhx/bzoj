#!/bin/bash
t=0;
while [ $t -lt 10000 ]
do
	let "t=$t+1";
	echo $RANDOM|./gen>3730.in
	./3730<3730.in>3730.out
	./b<3730.in>b.out
	if diff 3730.out b.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi;
done