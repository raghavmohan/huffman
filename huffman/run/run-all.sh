#! /bin/bash
LIST=../input/list/
UNIQUE=../input/uniquewords.txt
RUN=../run/
OUTPUT=../output/
INPUT=../input/
SRC=../src/
SPEECH="${INPUT}speechdata/"
./unique.sh
cd $SRC
make huff
nums[0]=1
nums[1]=2
nums[2]=10
nums[3]=100
nums[4]=300

cd $SRC
LISTALL=${LIST}exp/all.list
	j=$LISTALL
	dname=$(basename $j)
	dname=${dname/.list/}
	rm -rf ../output/$dname
	mkdir ../output/$dname
	for i in $(ls -d -1 ${LIST}run/*.list); do
		a=$(basename $i)
		#echo "./huff -b $j -i $i -o ../output/$dname/${a/.list/}.huff"
		./huff -b $j -i $i -o ../output/$dname/${a/.list/}.huff
done
