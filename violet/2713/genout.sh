#!/bin/bash
t=0
while [ $t -lt 10 ]
do
	let "t=$t+1"
	time ./en<en$t.in>en$t.out
done