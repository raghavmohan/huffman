#! /bin/sh

cd src
make clean
make
rm -f *.txt
./huff -i ../input/jefferson-1806.txt -o jefferson.txt
./huff -i ../input/obama-2009.txt -o obama.txt


