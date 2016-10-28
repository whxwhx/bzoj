t=0
while [ $t -lt 100 ]
do
	let "t=$t+1"
	echo $RANDOM|./gen>queue.in
	./4315<queue.in>queue.out
	./force<queue.in>force.out
	if diff queue.out force.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done