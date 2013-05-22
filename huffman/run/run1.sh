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

for i in {0..4}
do
  cd $INPUT
  ls -d -1 $PWD/speechdata/*.txt | tail -n ${nums[i]} > list/exp/recent-${nums[i]}.list
  ls -d -1 $PWD/uniquewords.txt >> list/exp/recent-${nums[i]}.list
  ls -r -d -1 $PWD/speechdata/*.txt | tail -n ${nums[i]} > list/exp/old-${nums[i]}.list
  ls -d -1 $PWD/uniquewords.txt >> list/exp/old-${nums[i]}.list
done

rm -f list/run/*
for i in $(ls -d -1 $PWD/speechdata/*.txt); do
  a=$(basename $i)
  a=${a/.txt/}
  echo $i > list/run/$a.list
done

rm -rf $OUTPUT/*
cd $SRC
for j in $(ls -d -1 ${LIST}exp/*.list); do
  dname=$(basename $j)
  dname=${dname/.list/}
  mkdir ../output/$dname
  for i in $(ls -d -1 ${LIST}run/*.list); do
    a=$(basename $i)
    #echo "./huff -b $j -i $i -o ../output/$dname/${a/.list/}.huff"
    ./huff -b $j -i $i -o ../output/$dname/${a/.list/}.huff
  done
done

