#! /bin/bash
LIST=../input/list/
UNIQUE=../input/uniquewords.txt
RUN=../run/
OUTPUT=../output/
INPUT=../input/
SRC=../src/
SPEECH="${INPUT}speechdata/"
cd $RUN
j=${OUTPUT}old-1/
dname=$(basename $j)
	echo $dname
	echo -e "FILE \t HUFFSIZE \t ORIGINAL SIZE \t WORDSIZE"
	for i in $(ls ${j}/*); do
dname2=$(basename $i)
	hsize=$(cat $i | wc -c)
	osize=$(cat ${INPUT}speechdata/${dname2/.huff/}.txt | wc -c)
	wsize=$(cat ${INPUT}speechdata/${dname2/.huff/}.txt | wc -w)
	echo -e "$dname2 \t $hsize \t $osize \t $wsize"
	done
