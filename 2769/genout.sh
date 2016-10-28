#!/bin/bash
t=0
while [ $t -lt 10 ]
do
	let "t=$t+1"
	./2769<sort$t.in>sort$t.out
done