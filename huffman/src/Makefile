CXX   = /usr/bin/g++
#OPTS = -Wall -Werror -g -O0
OPTS =  -Werror -g -O3

all: huff uniquewords

huff: huff.o
	$(CXX) $(OPTS) -o huff huff.o

huff.o : huff.cpp
	$(CXX) $(OPTS) -c 		huff.cpp -o huff.o

uniquewords: uniquewords.o
	$(CXX) $(OPTS) -o uniquewords uniquewords.o

uniquewords.o : uniquewords.cpp
	$(CXX) $(OPTS) -c uniquewords.cpp -o uniquewords.o

clean :
	rm -f *.o huff .*swp uniquewords *.txt *.huff
