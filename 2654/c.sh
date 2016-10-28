t=0
while [ $t -lt 1000 ]
do
	let "t=$t+1"
	echo $RANDOM|./gen>t.in
	./hzwer<t.in>t.out
	./2654<t.in>f.out
	if diff -w t.out f.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done