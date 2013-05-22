for i in $(ls ../output/all/*.huff); do
	a=$(basename $i)
	b=${a/.huff/}
	b=${b/_/}
	b=${b/_/}
	b=${b/_/}
	echo ${b:0:8}
done
