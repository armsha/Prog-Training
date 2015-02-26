

all:
	g++ -Wall -pedantic -g -std=c++11 KDtree.cpp -o KDtree

test: FORCE
	clear;clear;g++ -Wall -g -std=c++11 -D __TEST__ tt_test.h KDtree.cpp -o test

testrun: FORCE
	clear;clear;g++ -Wall -g -std=c++11 -D __TEST__ tt_test.h KDtree.cpp -o test
	clear;clear;valgrind --leak-check=full --show-reachable=yes ./test

clean: FORCE
	rm -f KDtree test a.out

FORCE:
