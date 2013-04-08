CXX   = /usr/bin/g++
#OPTS = -Wall -Werror -g -O0
OPTS =  -Werror -g -O0

all :huff

huff: huff.o
	$(CXX) $(OPTS) -o huff huff.o

huff.o : huff.cpp
	$(CXX) $(OPTS) -c 		huff.cpp -o huff.o

clean :
	rm -f *.o huff .*swp
