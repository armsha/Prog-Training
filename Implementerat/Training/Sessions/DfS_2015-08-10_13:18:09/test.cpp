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

#define BLACK 2
#define GRAY 1
#define WHITE 0

// Includes and namespace
#include <vector>
#include <iostream>

using namespace std;

class edge;
class vertex;
class graph;

class vertex
{
public:
	vertex( int l, vector<edge> n ) : label(l), neighbours(n) {};
	vertex( int l ) : label(l) { };

	int label;
	int colour = -1;
	int predecessor = -1;
	int discoveryT = -1;
	int finishT = -1;
	vector<edge> neighbours;
	/* data */
};

class edge
{
public:
	edge( vertex* t ) : target(t) {};

	vertex* target;
	/* data */

};



class graph
{
public:
	graph( vector<vertex*> v ) : vertices(v) {};

	vector<vertex*> vertices;
};


void DFS_visit( vertex *v, graph *G, int *t ){

	v->discoveryT = *t;
	v->colour = GRAY;
	*t = *t +1;

	for ( edge e : v->neighbours )
		if ( e.target->colour == WHITE ){
			DFS_visit( e.target, G, t );
			e.target->predecessor = v->label;
		}

	v->finishT = *t;
	v->colour = BLACK;
	*t = *t +1;

}

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Descend through the graph from different starting points until every 
 *	 	node has been visited. Do this in a DFS manner.
 *	 	Set the discovery, and finish times, as well as predecessors for the vertices.
 *	 	Also note in the algorithm where a function call should be performed to create
 *	 	pre-, or post-ordering of nodes.
 *	INPUT: 
 *		graph *G, with a vector of nodes, holding lists of neighbours.
 *	OUTPUT: 
 *		Modify the graph, setting discovery and finish times, as well as predecessor 
 *		vertices, as the DFS finds them. 
 *		* The test assumes starting time of 0, and colours
 *		used as defined, with starting white, and then getting coloured gray-and finally black.
 *		The order of vertices should be arbitrary, but the tests will check each in turn, as
 *		ordered in the vectors. *
 */	
graph* DFS( graph *G ){

	for ( vertex *v : G->vertices )
		v->colour = WHITE;

	int t = 0;

	for ( vertex *v : G->vertices )
		if ( v->colour == WHITE )
			DFS_visit( v, G, &t );	

	return G;
}

/*
 * Results to enter when done.
 *	TIME: 15
 *	COMPLEXITY: recursive O(n+e)
 */

/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"

bool vertexequals( vertex *v1, vertex *v2 ){
	return (v1->colour == v2->colour and 
			v1->predecessor == v2->predecessor and 
			v1->discoveryT == v2->discoveryT and
			v1->finishT == v2->finishT );
}

bool graphequals( graph *G1, graph *G2 ){

	bool b = true;
	bool has;

	for ( vertex *v1 : G1->vertices ){

		has = false;
		for ( vertex *v2 : G2->vertices ){

			if ( v1->label == v2->label ){
				has = true;

				if (not vertexequals(v1,v2) )
					b = false;

			}
		}

		if (!has)
			return false;
	}

	return b;
}

/* Test methods */

void testEmpty(){
	
	vector<vertex*> v;

	graph G = graph(v);

	graph G2 = graph(v);

	TT_assert_True( graphequals( &G, DFS(&G2) ) );

}

void testSingle(){
	
	vertex a(1);
	vertex b(1);

	b.colour = BLACK;
	b.predecessor = -1;
	b.discoveryT = 0;
	b.finishT = 1;

	vector<vertex*> v;
	v.push_back(&a);

	graph G = graph(v);

	graph *ans = DFS(&G);

	vector<vertex*> vtru;
	vtru.push_back(&b);

	graph trueans = graph(vtru);

	TT_assert_True( graphequals( &trueans,  ans ) );

}

void testDoubleSeparated(){

	vertex a(1);
	vertex a2(2);

	vertex b(1);
	b.colour = BLACK;
	b.predecessor = -1;
	b.discoveryT = 0;
	b.finishT = 1;


	vertex b2(2);
	b2.colour = BLACK;
	b2.predecessor = -1;
	b2.discoveryT = 2;
	b2.finishT = 3;
	
	vector<vertex*> v;
	v.push_back(&a);
	v.push_back(&a2);

	graph G = graph(v);

	graph  *ans = DFS(&G);

	vector<vertex*> vtru;
	vtru.push_back(&b);
	vtru.push_back(&b2);

	graph trueans = graph(vtru);

	TT_assert_True( graphequals( &trueans,  ans ) );

}

void testOrdering1(){
	
	vertex a(1);
	vertex a2(2);
	edge e( &a2 );
	a.neighbours.push_back(e);

	vertex b(1);
	b.colour = BLACK;
	b.predecessor = -1;
	b.discoveryT = 0;
	b.finishT = 3;


	vertex b2(2);
	b2.colour = BLACK;
	b2.predecessor = 1;
	b2.discoveryT = 1;
	b2.finishT = 2;
	
	vector<vertex*> v;
	v.push_back(&a);
	v.push_back(&a2);

	graph G = graph(v);

	graph *ans = DFS(&G);

	vector<vertex*> vtru;
	vtru.push_back(&b);
	vtru.push_back(&b2);

	graph trueans = graph(vtru);


	TT_assert_True( graphequals( &trueans,  ans ) );

}

void testOrdering2(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	edge e( &a3 );
	a.neighbours.push_back(e);

	vertex b(1);
	b.colour = BLACK;
	b.predecessor = -1;
	b.discoveryT = 0;
	b.finishT = 3;

	vertex b2(2);
	b2.colour = BLACK;
	b2.predecessor = -1;
	b2.discoveryT = 4;
	b2.finishT = 5;

	vertex b3(3);
	b3.colour = BLACK;
	b3.predecessor = 1;
	b3.discoveryT = 1;
	b3.finishT = 2;
	
	vector<vertex*> v;
	v.push_back(&a);
	v.push_back(&a2);
	v.push_back(&a3);

	graph G = graph(v);

	graph *ans = DFS(&G);

	vector<vertex*> vtru;
	vtru.push_back(&b);
	vtru.push_back(&b2);
	vtru.push_back(&b3);

	graph trueans = graph(vtru);


	TT_assert_True( graphequals( &trueans, ans ) );

}

void testOrdering3(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	edge e( &a3 );
	edge e2( &a2 );
	a.neighbours.push_back(e);
	a3.neighbours.push_back(e2);

	vertex b(1);
	b.colour = BLACK;
	b.predecessor = -1;
	b.discoveryT = 0;
	b.finishT = 5;

	vertex b2(2);
	b2.colour = BLACK;
	b2.predecessor = 3;
	b2.discoveryT = 2;
	b2.finishT = 3;

	vertex b3(3);
	b3.colour = BLACK;
	b3.predecessor = 1;
	b3.discoveryT = 1;
	b3.finishT = 4;
	
	vector<vertex*> v;
	v.push_back(&a);
	v.push_back(&a2);
	v.push_back(&a3);

	graph G = graph(v);

	graph *ans = DFS(&G);

	vector<vertex*> vtru;
	vtru.push_back(&b);
	vtru.push_back(&b2);
	vtru.push_back(&b3);

	graph trueans = graph(vtru);


	TT_assert_True( graphequals( &trueans, ans ) );

}


/* 
 * Main method
 * Runs all the tests, and prints the result
 */
int main(int argc, char const *argv[])
{

	TT_SETUP;
	TT_TEST(testEmpty);
	TT_TEST(testSingle);
	TT_TEST(testDoubleSeparated);
	TT_TEST(testOrdering1);
	TT_TEST(testOrdering2);
	TT_TEST(testOrdering3);
	TT_FINAL;

	return 0;
}

#endif