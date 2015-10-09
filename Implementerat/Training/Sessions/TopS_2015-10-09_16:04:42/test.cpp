/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		Topological sort
 *	INPUT: 
 *		A graph G, directed and acyklic.
 *	OUTPUT: 
 *		A linear ordering ov all vertices in G, such that if u,v in G, and v < u in the ordering,
 *		then there is no path from u to v in G.
 *	DESCRIPTION:
 *		A basic building block for graph algorithms. It is often useful to be able to impose a topological ordering
 *		on a graph, for example during computation of strongly conected components.
 *		The ordering results in that for each vertex u that you can reach in G from a vertex v, v will come before
 *		in the ordering.
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
#include <algorithm>

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

void visit( vertex* v, int *t, int pred, std::vector<int> &ord ){ 

	v->discoveryT = *t;
	*t = *t+1;
	v->predecessor = pred;
	v->colour = GRAY;

	for (std::vector<edge>::iterator e = v->neighbours.begin(); e != v->neighbours.end(); ++e)
	{
		vertex* u = (*e).target;
		if ( u->colour == WHITE )
		{
			visit( u, t, v->label, ord );
		}
	}

	v->finishT = *t;
	*t = *t +1;
	v->colour = BLACK;
	ord.push_back( v->label );

}

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Create a topological ordering on the graph, which can be assumed to be directed and acyklic.
 *	INPUT: 
 *		graph *G, with a vector of nodes, holding lists of neighbours.
 *	OUTPUT: 
 *		vector<int> O, a vector representing the ordering, with the labels of vertices as entries. 
 *			The values should be ordered such that a label later than another, cannot reach this other.
 *			Also note in the algorithm where cyckle detection can be added.
 */	
vector<int> TopSort( graph *G ){

	for (std::vector<vertex*>::iterator v = G->vertices.begin(); v != G->vertices.end(); ++v)
	{
		(*v)->colour = WHITE;
	}

	vector<int> order;

	int t = 0;
	for (std::vector<vertex*>::iterator v = G->vertices.begin(); v != G->vertices.end(); ++v)
	{
		if ((*v)->colour == WHITE ){
			visit( *v, &t, -1, order );
		}
	}

	reverse(order.begin(),order.end());
	return order;
}

/*
 * Results to enter when done.
 *	TIME: 10
 *	COMPLEXITY: DFS v+e
 */

/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"

/* Test methods */

void testEmpty(){

	vector<vertex*> v;

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	vector<int> vtru = {};

	TT_assert_True( ans == vtru );

}

void testSingle(){
	
	vertex a(1);

	vector<vertex*> v;
	v.push_back( &a );

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	vector<int> vtru = { 1 };

	TT_assert_True( ans == vtru );


}

void testDoubleSeparated(){

	vertex a(1);
	vertex a2(2);

	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a2 );

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	vector<int> vtru = {1,2};
	vector<int> vtru2 = {2,1};

	TT_assert_True( ((ans == vtru) or (ans == vtru2)) );


}

void testOrdering1(){
	
	vertex a(1);
	vertex a2(2);
	edge e( &a2 );
	a.neighbours.push_back(e);
	
	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a2 );

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	vector<int> vtru = {1,2};

	TT_assert_True( ans == vtru );


}

void testOrdering2(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	edge e( &a3 );
	a.neighbours.push_back(e);
	edge e1( &a );
	a2.neighbours.push_back(e1);
	
	
	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a2 );
	v.push_back( &a3 );

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	vector<int> vtru = {2,1,3};

	TT_assert_True( ans == vtru );


}

bool comesbefore( vector<int> ordering, int a, int b ){

	bool foundA = false;
	bool foundB = false;

	for ( int v: ordering ){
		if ( (v == b) and (not foundA) )
			return false;
		if ( v == a )
			foundA = true;
		if ( v == b )
			foundB = true;
	}

	if ( ( not foundA ) or (not foundB ) )
		return false;

	return true;

}

void testOrdering3(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	vertex a4(4);
	vertex a5(5);
	vertex a6(6);
	vertex a7(7);
	vertex a8(8);
	vertex a9(9);
	vertex a10(10);
	vertex a11(11);

	edge e( &a2 );
	edge e2( &a3 );
	edge e3( &a5 );
	edge e4( &a3 );
	edge e5( &a4 );
	edge e6( &a5 );
	edge e7( &a6 );
	edge e8( &a8 );
	edge e9( &a8 );
	edge e10( &a10 );
	edge e11( &a11 );
	edge e12( &a10 );
	edge e13( &a11 );

	a.neighbours.push_back(e);
	a.neighbours.push_back(e2);
	a.neighbours.push_back(e3);
	a2.neighbours.push_back(e4);
	a3.neighbours.push_back(e5);
	a4.neighbours.push_back(e6);
	a4.neighbours.push_back(e7);
	a5.neighbours.push_back(e8);
	a6.neighbours.push_back(e9);
	a6.neighbours.push_back(e10);
	a7.neighbours.push_back(e11);
	a8.neighbours.push_back(e12);
	a9.neighbours.push_back(e13);

	
	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a3 );
	v.push_back( &a4 );
	v.push_back( &a5 );
	v.push_back( &a2 );
	v.push_back( &a8 );
	v.push_back( &a7 );
	v.push_back( &a9 );
	v.push_back( &a10 );
	v.push_back( &a11 );
	v.push_back( &a6 );

	graph G = graph(v);

	vector<int> ans = TopSort(&G);

	TT_assert_True( comesbefore( ans, 1, 2 ) );
	TT_assert_True( comesbefore( ans, 1, 3 ) );
	TT_assert_True( comesbefore( ans, 1, 5 ) );
	TT_assert_True( comesbefore( ans, 2, 3 ) );
	TT_assert_True( comesbefore( ans, 3, 4 ) );
	TT_assert_True( comesbefore( ans, 4, 5 ) );
	TT_assert_True( comesbefore( ans, 4, 6 ) );
	TT_assert_True( comesbefore( ans, 5, 8 ) );
	TT_assert_True( comesbefore( ans, 6, 8 ) );
	TT_assert_True( comesbefore( ans, 6, 10 ) );
	TT_assert_True( comesbefore( ans, 7, 11 ) );
	TT_assert_True( comesbefore( ans, 8, 10 ) );
	TT_assert_True( comesbefore( ans, 9, 11 ) );

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