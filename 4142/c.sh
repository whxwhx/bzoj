t=0
while [ $t -lt 20 ]
do
	let "t=$t+1"
	./4142<data$t.in>t.out
	if diff data$t.out t.out -w; then
		echo "AC $t";
	else 
		echo "WA $t"; break;
	fi
done