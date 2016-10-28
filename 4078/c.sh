t=0
while [ $t -lt 10 ]
do
	let "t=$t+1";
	time ./4078<./florida/florida$t.in>florida.out
	if diff -w ./florida/florida$t.out florida.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done
