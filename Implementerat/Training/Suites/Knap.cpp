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
#include <vector>
#include <algorithm>
#include <iostream>

/*
 * Method to implement
 *	DESCRIPTION: <detailed description of method>
 *	INPUT: <@param stuff>
 *	OUTPUT: <@return stuff>
 */	
// -- Implementation here ---

std::vector<int> bin_knapsack_find_items(std::vector<int> values, std::vector<int> weights, int nrOfItems, int capacity) {
	int **m = (int**)calloc(sizeof(int*), nrOfItems+1);
	int **keep = (int**)calloc(sizeof(int*), nrOfItems+1);
	/* Contains indices of items to keep */
	int i,j;
	for (i = 0; i < nrOfItems+1; i++) {
		m[i] = (int*)calloc(sizeof(int), capacity+1);
		keep[i] = (int*)calloc(sizeof(int), capacity+1);
	}

	for (i = 1; i <= nrOfItems; i++) {
//		std::cout << "Value is: " << values[i-1];
//		std::cout << ", Weight is: " << weights[i-1];
//		std::cout << ", index is: " << i;
//		std::cout << std::endl;
		for (j = 0; j <= capacity; j++) {
			if ((weights[i-1] <= j) && ((values[i-1] + m[i-1][j-weights.at(i-1)]) > m[i-1][j])) {
//				std::cout << "m[i-1][j] is: " << m[i-1][j];
//				std::cout << ", m[i-1][j-w[i]]+v[i] is: " << m[i-1][j-weights.at(i-1)]+values.at(i-1);
//				std::cout << std::endl;
				m[i][j] = m[i-1][j-weights.at(i-1)]+values.at(i-1);
				keep[i][j] = 1;

			} else {
				m[i][j] = m[i-1][j];
				keep[i][j] = 0;
			}
		}
	}
	int K = capacity;
	std::vector<int> itemIndexesToKeep;
	for( i = nrOfItems; i > 0; i-- ) {
		if (keep[i][K] == 1) {
//			std::cout << "Item at index: " << i-1;
//			std::cout << " should be included" << std::endl;
			itemIndexesToKeep.push_back(i-1);
			K -= weights[i-1];

		}
	}
//	for ( i = 0; i <= nrOfItems; i++) {
//		for ( j = 0; j <= capacity; j++) {
//			std::cout << m[i][j];
//			std::cout << " ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "Profit1 is: " << m[nrOfItems][capacity] << std::endl;
	for (i = 0; i < nrOfItems+1; i++) {
		free(m[i]);
		free(keep[i]);
	}
	free(m);
	free(keep);
	return itemIndexesToKeep;

}

int bin_knapsack(std::vector<int> values, std::vector<int> weights, int nrOfItems, int capacity) {
	std::vector<int> items = bin_knapsack_find_items(values, weights, nrOfItems, capacity);
	int profit = 0;
	for(int i: items) {
		profit += values[i];
	}
	std::cout << "Profit is: " << profit;
	std::cout << std::endl;
	return profit;
}

int bin_knapsack2(std::vector<int> values, std::vector<int> weights, int nrOfItems, int capacity) {
	int **m = (int**)calloc(sizeof(int*), nrOfItems+1);
	int i,j;
	for (i = 0; i < nrOfItems+1; i++) {
		m[i] = (int*)calloc(sizeof(int), capacity+1);
	}

	for (i = 1; i <= nrOfItems; i++) {
//		std::cout << "Value is: " << values[i-1];
//		std::cout << ", Weight is: " << weights[i-1];
//		std::cout << ", index is: " << i;
//		std::cout << std::endl;
		for (j = 0; j <= capacity; j++) {
			if (weights[i-1] <= j) {
//				std::cout << "m[i-1][j] is: " << m[i-1][j];
//				std::cout << ", m[i-1][j-w[i]]+v[i] is: " << m[i-1][j-weights.at(i-1)]+values.at(i-1);
//				std::cout << std::endl;
				m[i][j] = std::max( m[i-1][j], m[i-1][j-weights.at(i-1)]+values.at(i-1) );
			} else {
				m[i][j] = m[i-1][j];
			}
		}
	}
//	for ( i = 0; i <= nrOfItems; i++) {
//		for ( j = 0; j <= capacity; j++) {
//			std::cout << m[i][j];
//			std::cout << " ";
//		}
//		std::cout << std::endl;
//	}
	std::cout << "Max value is: " << m[nrOfItems][capacity] << std::endl;
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
	std::vector<int> values;
	values.push_back(3);
	values.push_back(4);
	values.push_back(6);
	values.push_back(5);

	std::vector<int> weights;
	weights.push_back(2);
	weights.push_back(1);
	weights.push_back(6);
	weights.push_back(5);

	TT_assert_EQ( bin_knapsack(values, weights, 4, 1794), 18);
}

void testBinSackMaxCostLargerThanConstraint() {
	std::vector<int> values;
	values.push_back(10);
	values.push_back(7);
	values.push_back(25);
	values.push_back(24);

	std::vector<int> weights;
	weights.push_back(2);
	weights.push_back(1);
	weights.push_back(6);
	weights.push_back(5);


	TT_assert_EQ( bin_knapsack(values, weights, 4, 7), 34);
}

/*
 * Found online on https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/
 */

void testBinSack3() {
	std::vector<int> values;
	values.push_back(442);
	values.push_back(525);
	values.push_back(511);
	values.push_back(593);
	values.push_back(546);
	values.push_back(564);
	values.push_back(617);

	std::vector<int> weights;
	weights.push_back(41);
	weights.push_back(50);
	weights.push_back(49);
	weights.push_back(59);
	weights.push_back(55);
	weights.push_back(57);
	weights.push_back(60);


	TT_assert_EQ( bin_knapsack(values, weights, 7, 170), 1735);
}


/*
 * Found online on https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/
 */

void testBinSack4() {
	std::vector<int> values;
	values.push_back(135);
	values.push_back(139);
	values.push_back(149);
	values.push_back(150);
	values.push_back(156);
	values.push_back(163);
	values.push_back(173);
	values.push_back(184);
	values.push_back(192);
	values.push_back(201);
	values.push_back(210);
	values.push_back(214);
	values.push_back(221);
	values.push_back(229);
	values.push_back(240);


	std::vector<int> weights;
	weights.push_back(70);
	weights.push_back(73);
	weights.push_back(77);
	weights.push_back(80);
	weights.push_back(82);
	weights.push_back(87);
	weights.push_back(90);
	weights.push_back(94);
	weights.push_back(98);
	weights.push_back(106);
	weights.push_back(110);
	weights.push_back(113);
	weights.push_back(115);
	weights.push_back(118);
	weights.push_back(120);


	TT_assert_EQ( bin_knapsack(values, weights, 15, 750), 1458);
}


/*
 * Found online on https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/
 */

void testBinSack5() {
	std::vector<int> values;
	values.push_back(825594);
	values.push_back(1677009);
	values.push_back(1676628);
	values.push_back(1523970);
	values.push_back(943972);
	values.push_back(97426);
	values.push_back(69666);
	values.push_back(1296457);
	values.push_back(1679693);
	values.push_back(1902996);
	values.push_back(1844992);
	values.push_back(1049289);
	values.push_back(1252836);
	values.push_back(1319836);
	values.push_back(953277);
	values.push_back(2067538);
	values.push_back(675367);
	values.push_back(853655);
	values.push_back(1826027);
	values.push_back(65731);
	values.push_back(901489);
	values.push_back(577243);
	values.push_back(466257);
	values.push_back(369261);



	std::vector<int> weights;
	weights.push_back(382745);
	weights.push_back(799601);
	weights.push_back(909247);
	weights.push_back(729069);
	weights.push_back(467902);
	weights.push_back(44328);
	weights.push_back(34610);
	weights.push_back(698150);
	weights.push_back(823460);
	weights.push_back(903959);
	weights.push_back(853665);
	weights.push_back(551830);
	weights.push_back(610856);
	weights.push_back(670702);
	weights.push_back(488960);
	weights.push_back(951111);
	weights.push_back(323046);
	weights.push_back(446298);
	weights.push_back(931161);
	weights.push_back(31385);
	weights.push_back(496951);
	weights.push_back(264724);
	weights.push_back(224916);
	weights.push_back(169684);


	TT_assert_EQ( bin_knapsack(values, weights, 24, 6404180), 13549094);
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
	TT_TEST( testBinSack3 );
	TT_TEST( testBinSack4 );
	TT_TEST( testBinSack5 );

	TT_FINAL;

	return 0;
}

#endif
