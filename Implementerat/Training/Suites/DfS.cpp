/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		Depth first search
 *	INPUT: 
 *		A graph G
 *	OUTPUT: 
 *		Perhaps used for searching as name suggests, but often just to descend through 
 *		a graph, maybe doing something at each node.
 *	DESCRIPTION: 
 *		Descend through a graph G, and do something for each node. The order this is done
 *		is depth-first, meaning that one continues directly along available visiblie paths,
 *		down the graph from the current node.
 *	USE: 
 *		This is used as a basic building block in several graph-algorithms.
 *	COMPLEXITY: 
 *		This should be done in linear time (O(|V|+|E|)).
 */

// Includes and namespace
#include <vector>

using namespace std;

class edge
{
public:
	edge( vertex t) : target(t) {};

	vertex target;
	/* data */

};

class vertex
{
public:
	vertex( int l, vector<edge> n ) : label(l), neighbours(n) {};

	int label;
	int color;
	int predecessor;
	int discoveryT;
	int finishT;
	vector<edge> neighbours;
	/* data */
};

class graph
{
public:
	graph( vector<vertex> v ) : vertices(v) {};

	vector<vertex> vertices;
};

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Descend through the graph from different starting points until every 
 *	 	node has been visited. Do this in a DFS manner.
 *	 	Set the discovery, and finish times, as well as predecessors for the vertices.
 *	 	Also note in the algorithm where a function call should be performed to create
 *	 	pre-, or post-ordering of nodes.
 *	INPUT: 
 *		graph G, with a vector of nodes, holding lists of neighbours.
 *	OUTPUT: 
 *		Modify the graph, setting discovery and finish times, as well as predecessor 
 *		vertices, as the DFS finds them.
 */	
void DFS( graph& G ){
	
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


/* 
 * Main method
 * Runs all the tests, and prints the result
 */
int main(int argc, char const *argv[])
{

	TT_SETUP;
	/* Tests */
	// TT_TEST(testmethod);
	TT_FINAL;

	return 0;
}

#endif