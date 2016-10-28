#!/bin/bash
t=0;
while [ $t -lt 5 ]
do 
	let "t=$t + 1";
	./4062<"./data/data$t.in">"data$t.out"
	if diff "data$t.out" "./data/data$t.out"; then
		echo "AC $t";
	else 
		echo "WA $t";
		break;
	fi
done