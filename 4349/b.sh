while [ true ] 
do
	echo $RANDOM|./gen>t.in
	./std<t.in>t.out
	./4349<t.in>f.out
	if diff t.out f.out; then
		echo "AC $t";
	else
		echo "WA $t";
		break;
	fi
done