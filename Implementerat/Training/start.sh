#!/usr/bin/env bash

supported=""\
"(MaSA):\tMaximum subarray\n"\
"(BinS):\tBinary search (Not implemented)\n"\
"(StrS):\tString search\n"\
"(DfS):\tDepth-first search (Not implemented)\n"\
"(BfS):\tBredth-first search (Not implemented)\n"\
"(TopS):\tTopological sort (Not implemented)\n"\
"(SCC):\tStrongly connected component find (Not implemented)\n"\
"(2SAT):\t2-Sat problem (Not implemented)\n"\
"(ConH):\tConvex hull\n"\
"(Knap):\tKnapsack problem (Not implemented)\n"\
"(Flow):\tMaximum flow problem (Not implemented)\n"
editor="sublime"


if [[ $# -ne 1 ]]; then
	#Invalid usage
	printf "Invalid arguments\n"
	bash "$0" "-usage"
	exit 1
fi

if [[ $1 = "-usage" ]]; then
	#Usage instructions
	printf "Usage: $0 <algorithm-abbreviation>\n"
	printf "Current supported algorithms:\n"
	printf "$supported"
	exit 0
fi

if [[ $1 = "-help" ]]; then
	#Help instructions
	bash "$0" "-usage"
	printf "\nHelp:\n"\
"A new directory, named with the current date and algorithm-abbreviation,\n\
will be created. This will contain a testing environment for the algorithm,\n\
as well as a started .cpp file, in which the algorithm should be implemented,\n\
following a given interface.\n"\
"To test the implementation, run the command \"make testrun\".\n"
	exit 0
fi

case $1 in
	MaSA )
		printf "Maximum subarray\n";;
	BinS )
		printf "Binary search\n";;
	StrS )
		printf "String search\n";;
	DfS )
		printf "Depth-first search\n";;
	BfS )
		printf "Bredth-first search\n";;
	TopS )
		printf "Topological sort\n";;
	ConH )
		printf "Convex hull\n";;
    SCC )
        printf "Strongly connected component find\n";;
    2SAT )
        printf "2-Sat problem\n";;
    Knap )
        printf "Knapsack problem\n";;
    Flow )
        printf "Maximal flow problem\n";;
	* )
		printf "Invalid algorithm-abbreviation\n"
		bash "$0" "-usage"
		exit 1;;
esac

datum=`date "+%Y-%m-%d_%H:%M:%S"`
printf "Date: $datum\n"

dirname="Sessions/$1_$datum"

mkdir "$dirname"
printf "Directory $dirname created!\n"

cp Utilities/Makefile "$dirname"
cp Utilities/tt_test.h "$dirname"
cp "Suites/$1.cpp" "$dirname/test.cpp"
printf "Files copied!\n"

cd "$dirname"
pwd
ls -l

"$editor" -n test.cpp & bash -i 


