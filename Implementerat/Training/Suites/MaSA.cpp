/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		Maximum Subarray
 *	INPUT: 
 *		An array A, of length n. Containing potentially negative numbers.
 *	OUTPUT: 
 *		The maximum sum of a subarray of A, 
 *		and the start and end indexes of this subarray (p and q).
 *	DESCRIPTION: 
 *		Given an array A of length n, search it to find a maximal
 *		subarray A[p...q], where the sum from p to q of elements in A
 *		is the highest in the entire array. Return this maximal sum, 
 *		as well as the left and right indexes of this subarray.
 *	USE: 
 *		Instead of comparing values directly in several stock- (or similiar)
 *		based exercises, first compute the differences to get an array of 
 *		the changes. Finding the largest distance between two following 
 *		stock-points, then corresponds to finding the maximal subarray.
 *	COMPLEXITY: 
 *		The naive solution would be O(n^3), with a slight improvement
 *		using precomputed partial sums O(n^2). Divide-and-Conquer can be
 *		used to get O(nlog(n)), or Dynamic Programming for the optimal O(n).
 */

// Includes and namespace

/**
 * Helper class to store the data returned from maximumSubarray in.
 */
class AnswerTriplet {
public:
	int p;   // Start index
	int q;   // End index
	int sum; // Sum between indexes

	AnswerTriplet( int p, int q, int sum ) :
		p(p),q(q),sum(sum) {}

};

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Implement a max-subarray method, looking for indices p and q of A,
 *		such that the sum inbetween them is maximized. If sums are equal,
 *		return the one with smallest size q-p, and after that the first such subarray. 
 *		Atleast one element will be returned when p=q, to return no element
 *		set p = q = -1. (This is perferred if sum is 0.)
 *	INPUT: 
 *		int A[], 	An array of any numbers (integers).
 *		int n, 		the length of A.
 *	OUTPUT: 
 *		AnswerTriplet r, Triplet containing p, q, and sum of a max-array.
 */	
AnswerTriplet maximumSubarray( int A[], int n ){

	return AnswerTriplet( -1, -1, 0 );
}

/*
 * Results to enter when done.
 *	TIME: <how many minutes did it take this time>
 *	COMPLEXITY: <what O is the implementation>
 */


/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"

/* Test methods */

void testEmpty(){

	int arr[] = {};
	AnswerTriplet ans = maximumSubarray( arr, 0 );

	TT_assert_True( ans.p == -1 and ans.q == -1 and ans.sum == 0 );
}

void testSingleElement(){

	int arr[] = { 1 };
	AnswerTriplet ans = maximumSubarray( arr, 1 );

	TT_assert_True( ans.p == 0 and ans.q == 0 and ans.sum == 1 );
}

void testNegativeSingleElement(){

	int arr[] = { -1 };
	AnswerTriplet ans = maximumSubarray( arr, 1 );

	TT_assert_True( ans.p == -1 and ans.q == -1 and ans.sum == 0 );
}

void testNegativeElements(){

	int arr[] = { -2, -3, -1 };
	AnswerTriplet ans = maximumSubarray( arr, 3 );

	TT_assert_True( ans.p == -1 and ans.q == -1 and ans.sum == 0 );
}

void testZero(){

	int arr[] = { 0 };
	AnswerTriplet ans = maximumSubarray( arr, 1 );

	TT_assert_True( ans.p == -1 and ans.q == -1 and ans.sum == 0 );
}

void testZero2(){

	int arr[] = { 0, 0 };
	AnswerTriplet ans = maximumSubarray( arr, 2 );

	TT_assert_True( ans.p == -1 and ans.q == -1 and ans.sum == 0 );
}

void testSmallArray(){

	int arr[] = { 1, 2, 3 };
	AnswerTriplet ans = maximumSubarray( arr, 3 );

	TT_assert_True( ans.p == 0 and ans.q == 2 and ans.sum == 6 );
}

void testSmallArray2(){

	int arr[] = { 1, -2, 1, 1, 1, -1 };
	AnswerTriplet ans = maximumSubarray( arr, 6 );

	TT_assert_True( ans.p == 2 and ans.q == 4 and ans.sum == 3 );
}

void testSmallArray3(){

	int arr[] = { 1, -2, 2, -1, 2, -1 };
	AnswerTriplet ans = maximumSubarray( arr, 6 );

	TT_assert_True( ans.p == 2 and ans.q == 4 and ans.sum == 3 );
}

void testChoseSmaller(){

	int arr[] = { 1, 2, -2, 1, 1, 1, -5, 3, 1, 0 };
	AnswerTriplet ans = maximumSubarray( arr, 10 );

	TT_assert_True( ans.p == 7 and ans.q == 8 and ans.sum == 4 );
}

void testLargeArray(){

	int arr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		arr[i] = ( (i*101) % 37 ) + ( (i*991) % 137 ) - ( ((2*i+3)*101) % 37) - ( ((3*i+5)*991) % 137 );
	}

	AnswerTriplet ansC(-1,-1,0);
	int sum;
	for (int p = 0; p < 1000; ++p)
	{
		for (int q = p; q < 1000; ++q)
		{
			sum = 0;
			for (int i = p; i <= q; ++i)
			{
				sum += arr[i];
			}
			if ( ( sum > ansC.sum ) or ( ( sum == ansC.sum ) and ( q-p < ansC.q - ansC.p ) ) )
			{
				ansC.sum = sum;
				ansC.p = p;
				ansC.q = q;
			}
		}
	}

	AnswerTriplet ansV = maximumSubarray( arr, 1000 );

	TT_assert_True( ansC.p == ansV.p and ansC.q == ansV.q and ansC.sum == ansV.sum );
}


/* 
 * Main method
 * Runs all the tests, and prints the result
 */
int main(int argc, char const *argv[])
{

	TT_SETUP;
	TT_TEST(testEmpty);
	TT_TEST(testSingleElement);
	TT_TEST(testNegativeSingleElement);
	TT_TEST(testNegativeElements);
	TT_TEST(testZero);
	TT_TEST(testZero2);
	TT_TEST(testSmallArray);
	TT_TEST(testSmallArray2);
	TT_TEST(testSmallArray3);
	TT_TEST(testChoseSmaller);
	TT_TEST(testLargeArray);
	TT_FINAL;

	return 0;
}

#endif