#! /bin/bash
LIST=../input/list/
UNIQUE=../input/uniquewords.txt
RUN=../run/
OUTPUT=../output/
INPUT=../input/
SRC=../src/
SPEECH="${INPUT}speechdata/"
cd $RUN
	for i in $(ls ${RUN}scr/*); do
dname2=$(basename $i)
	$i > ${RUN}txt/${dname2/.sh/}.txt
	#echo "$i > ${RUN}txt/${dname2/.sh/}.txt"
done

