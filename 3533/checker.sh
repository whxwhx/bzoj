t=0
while [ $t -lt 200 ]
do
	let "t=$t+1"
	python gen.py>b.in
	./force<b.in>b.out
	./3533<b.in>3533.out
	if diff b.out 3533.out; then 
		echo "AC $t";
	else
		echo "WA $t"
		break;
	fi
done