FILE = test.cpp

test: FORCE
	clear;clear;g++ -Wall -g -D __TEST__ tt_test.h $(FILE) -o test

testrun: FORCE
	clear;clear;g++ -std=c++11 -Wall -g -D __TEST__ tt_test.h $(FILE) -o test
	clear;clear;./test

testrunV: FORCE
	clear;clear;g++ -Wall -g -D __TEST__ tt_test.h $(FILE) -o test
	clear;clear;valgrind --leak-check=full --show-reachable=yes ./test

clean: FORCE
	rm -f test a.out

FORCE:
