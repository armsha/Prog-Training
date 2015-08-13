/*
 * Algorithm implementation training test suite.
 *	NAME: <template>
 *	INPUT: <input for algorithm>
 *	OUTPUT: <output for algorithm>
 *	DESCRIPTION: <what the algorithm does>
 *	USE: <where the algorithm is used, or an example>
 *	COMPLEXITY: <a solution of atleast O(x) exists...>
 */

// Includes and namespace

/*
 * Method to implement
 *	DESCRIPTION: <detailed description of method>
 *	INPUT: <@param stuff>
 *	OUTPUT: <@return stuff>
 */	
// -- Implementation here ---
int bin_knapsack(const int [] values, const int [] weights, int nrOfItems, int capacity) {
	int m[n][capacity];
	int i,j;
	for (j = 0; j < capacity; j++) {
		m[0][j] = 0;
	}

	for (i = 1; i < nrOfItems; i++) {
		for (j = 0; j < capacity; j++) {
			if (weights[i] <= j) {
				m[i][j] = max( m[i-1,j], m[i-1,j-weights[i]]+v[i] );
			} else {
				m[i][j] = m[i-1][j];
			}
		}
	}
	return m[nrOfItems][capacity];

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
// void testmethod(){
// 	TT_assert_True( true );
// 	TT_assert_EQ( 2, 1+1 );
// 	TT_FAIL;
// }

void testBinSackMaxCostSmallerThanConstraint() {
	TT_assert_EQ( bin_knapsack([3,4,6,5], [2,1,6,5], 4, 1794), 18);
}

void testBinSackMaxCostLargerThanConstraint() {
	TT_assert_EQ( bin_knapsack([10,7,25,24], [2,1,6,5], 4, 7), 34);
}


/* 
 * Main method
 * Runs all the tests, and prints the result
 */
int main(int argc, char const *argv[])
{

	TT_SETUP;
	/* Tests */
	// TT_TEST(testmethod);
	TT_TEST( testBinSackMaxCostSmallerThanConstraint );
	TT_TEST( testBinSackMaxCostLargerThanConstraint );

	TT_FINAL;

	return 0;
}

#endif
