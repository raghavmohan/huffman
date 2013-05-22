#! /bin/bash
LIST=../input/list/
UNIQUE=../input/uniquewords.txt
RUN=../run/
OUTPUT=../output/
INPUT=../input/
SRC=../src/
SPEECH="${INPUT}speechdata/"
cd $RUN
for j in $(ls -d -1 ${OUTPUT}*); do
dname=$(basename $j)
	echo $dname
	echo -e "FILE \t HUFFSIZE \t ORIGINAL SIZE"
	for i in $(ls ${j}/*); do
dname2=$(basename $i)
	hsize=$(cat $i | wc -c)
	osize=$(cat ${INPUT}speechdata/${dname2/.huff/}.txt | wc -c)
	echo -e "$dname2 \t $hsize \t $osize"
	done
	done

