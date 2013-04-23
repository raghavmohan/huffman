#! /bin/sh
LIST=../input/list/
UNIQUE=../input/uniquewords.txt
RUN=../output/
OUTPUT=../output/
INPUT=../input/
SPEECH="${INPUT}speechdata/"
#./unique.sh
cd ../src
make huff
nums[0]=1
nums[1]=2
nums[2]=10
nums[3]=100
nums[4]=300

for i in {0..4}
do
  ls ../input/speechdata/*.txt | tail -n ${nums[i]} > ../input/list/recent-${nums[i]}.list
  ls -r ../input/speechdata/*.txt | tail -n ${nums[i]} > ../input/list/old-${nums[i]}.list
done
for i in $(basename ${SPEECH}*.txt); do
  echo $i
  #./huff -b ../input/uniquewords.txt -i ../input/list/files.list -o ../output/$i.huff
done
