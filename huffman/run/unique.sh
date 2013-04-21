#! /bin/sh
LIST=../input/list/all.list
UNIQUE=../input/uniquewords.txt
#ls -d -1 $PWD/../input/speechdata/*.txt > ../input/list/all.list
ls -d -1 $PWD/../input/speechdata/*.txt > $LIST
cd ../src
make uniquewords
rm -f $UNIQUE
./uniquewords $LIST $UNIQUE
