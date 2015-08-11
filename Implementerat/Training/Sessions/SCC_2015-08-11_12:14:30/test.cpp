/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		Strongly Connected Component algorithms
 *	INPUT: 
 *		A graph G, for which to find strongly conected components.
 *	OUTPUT: 
 *		The strongly connected components of G.
 *	DESCRIPTION: 
 *		The strongly connected components of a graph G, are each a subset of the 
 *		vertices, V_1, V_2, V_3... in V, such that for each u,w in a component V_i,
 *		there exists a path between u to w, from w to u. Each such V_i is maximal, meaning
 *		it contains all the u and w for which the above holds.
 *	USE: 
 *		This is used as a building block in other algorithms, notably in 2-SAT. Strongly
 *		connected components are useful because a graph can often be divided into them, and they
 *		in turn can be solved separately, to be connected later.
 *	COMPLEXITY: 
 *		These components can be found in linear (O(|V|+|E|)) time.
 */

// Includes and namespace
#include <vector>
#include <iostream>

#define UNDEF -1
#define MIN( a, b ) ( ((a)<(b))?(a):(b) )

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
	vector<edge> neighbours;
	int index = UNDEF;
	int lowlink;
	bool onstack = false;
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

void strongconnect( vector<vector<int>> &components, vector< vertex* > &stack, int *index, vertex *nod ){

	nod->index = *index;
	nod->lowlink = *index;
	*index = *index + 1;

	stack.push_back(nod);
	nod->onstack = true;

	for ( edge e: nod->neighbours ){

		if ( e.target->index == UNDEF )
		{
			strongconnect( components,stack,index,e.target );
			nod->lowlink = MIN( nod->lowlink, e.target->lowlink );
		} else if ( e.target->onstack )
		{
			nod->lowlink = MIN( nod->lowlink, e.target->index );
		}

	}

	if ( nod->lowlink == nod->index )
	{
		vector<int> component;
		vertex *v;
		do{
			v = stack.back();
			component.push_back( v->label );

			stack.pop_back();
			v->onstack = false;

		} while ( v->label != nod->label );

		components.push_back(component);
	}


}

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Find the strungly connected components of the provided graph G, returned as
 *		a vector of vectors, where each inner vector contains a component, ordered by its 
 *		labels. The strongly connected components are the maximal subsets of the vertices
 *		of the graph, such that each vertex in the component can reach each other vertex.
 *	INPUT: 
 *		graph G, a graph containing vertexes with lists of edges
 *	OUTPUT: 
 *		vector< vector< int > > components, where each inner vector contains a whole component,
 *			with vertices represented by their label values.
 */	
vector< vector<int> > SCC( graph G ){

	vector< vector<int> > components;

	int index = 0;

	vector< vertex* > stack;

	for ( vertex *v : G.vertices )
		if ( v->index == UNDEF )
			strongconnect( components,stack,&index,v);


	return components;

}

/*
 * Results to enter when done.
 *	TIME: 50
 *	COMPLEXITY: Tarjans O(n+e) linear
 */

/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"


bool matches( vector<vector<int>> A, vector<vector<int>> B ){

	if ( not A.size() == B.size() )
		return false;

	bool hasB,hasI;
	int val;

	for ( vector<int> component: A ){

		hasB = false;

		for ( vector<int> potential: B ){

			if ( component.size() == 0 or potential.size() == 0 )
				return false;

			if ( not ( component.size() == potential.size() ) )
				continue;

			val = component[0];

			for ( int i : potential )
				if ( val == i )
					hasB = true;

			if ( hasB ) {

				for ( int i : component ){

					hasI = false;
					for ( int j : potential )
						if ( i == j )
							hasI = true;

					if ( not hasI )
						return false;

				}
				break;
			}

		}

		if ( not hasB )
			return false;

	}

	return true;
}

void testEmpty(){

	vector<vertex*> v;

	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<vector<int>> vtru;

	bool result = matches( vtru, ans );

	TT_assert_True( result );
}

void testSingle(){
	
	vertex a(1);

	vector<vertex*> v;
	v.push_back( &a );

	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<int> SC1 = { 1 };
	vector<vector<int>> trueans;
	trueans.push_back( SC1 );

	bool result = matches( trueans, ans );

	TT_assert_True( result );


}

void testDoubleSeparated(){

	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	vertex a4(4);

	vector<vertex*> v;
	v.push_back( &a4 );
	v.push_back( &a2 );
	v.push_back( &a3 );
	v.push_back( &a );


	edge e( &a2 );
	edge e1( &a );
	edge e2( &a2 );
	edge e3( &a4 );
	edge e4( &a3 );
	a.neighbours.push_back(e);
	a2.neighbours.push_back(e1);
	a2.neighbours.push_back(e2);
	a3.neighbours.push_back(e3);
	a4.neighbours.push_back(e4);

	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<int> SC1 = { 1,2 };
	vector<int> SC2 = { 3,4 };
	vector<vector<int>> trueans;
	trueans.push_back( SC1 );
	trueans.push_back( SC2 );

	bool result = matches( trueans, ans );

	TT_assert_True( result );


}

void testOrdering1(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	vertex a4(4);
	vertex a5(5);

	edge e( &a2 );
	edge e2( &a3 );
	edge e3( &a );
	edge e4( &a4 );
	edge e5( &a5 );
	edge e6( &a5 );
	a.neighbours.push_back(e);
	a2.neighbours.push_back(e2);
	a3.neighbours.push_back(e3);
	a3.neighbours.push_back(e4);
	a4.neighbours.push_back(e5);
	a5.neighbours.push_back(e6);
	
	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a5 );
	v.push_back( &a4 );
	v.push_back( &a3 );
	v.push_back( &a2 );

	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<int> SC1 = { 1,2,3 };
	vector<int> SC2 = { 4 };
	vector<int> SC3 = { 5 };
	vector<vector<int>> trueans;
	trueans.push_back( SC1 );
	trueans.push_back( SC2 );
	trueans.push_back( SC3 );

	bool result = matches( trueans, ans );

	TT_assert_True( result );


}

void testOrdering2(){
	
	vertex a(1);
	vertex a2(2);
	vertex a3(3);
	vertex a4(4);
	vertex a5(5);
	vertex a6(6);
	vertex a7(7);
	vertex a8(8);

	edge e( &a2 );
	edge e2( &a3 );
	edge e3( &a4 );
	edge e4( &a3 );
	edge e5( &a );
	edge e6( &a5 );
	edge e7( &a6 );
	edge e8( &a7 );
	edge e9( &a8 );
	edge e10( &a4 );
	edge e11( &a6 );
	edge e12( &a7 );
	edge e13( &a6 );
	edge e14( &a7 );

	a.neighbours.push_back(e);
	a2.neighbours.push_back(e2);
	a3.neighbours.push_back(e3);
	a4.neighbours.push_back(e4);
	a5.neighbours.push_back(e5);
	a2.neighbours.push_back(e6);
	a2.neighbours.push_back(e7);
	a3.neighbours.push_back(e8);
	a4.neighbours.push_back(e9);
	a8.neighbours.push_back(e10);
	a5.neighbours.push_back(e11);
	a6.neighbours.push_back(e12);
	a7.neighbours.push_back(e13);
	a8.neighbours.push_back(e14);

	vector<vertex*> v;	
	v.push_back( &a );
	v.push_back( &a3 );
	v.push_back( &a4 );
	v.push_back( &a5 );
	v.push_back( &a2 );
	v.push_back( &a8 );
	v.push_back( &a7 );
	v.push_back( &a6 );
	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<int> SC1 = { 1,2,5 };
	vector<int> SC2 = { 3,4,8 };
	vector<int> SC3 = { 6,7 };
	vector<vector<int>> trueans;
	trueans.push_back( SC1 );
	trueans.push_back( SC2 );
	trueans.push_back( SC3 );

	bool result = matches( trueans, ans );

	TT_assert_True( result );


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
	vertex a12(12);
	vertex a13(13);
	vertex a14(14);

	edge e( &a2 );
	edge e2( &a4 );
	edge e3( &a6 );
	edge e4( &a3 );
	edge e5( &a2 );
	edge e6( &a8 );
	edge e7( &a3 );
	edge e8( &a6 );
	edge e9( &a4 );
	edge e10( &a10 );
	edge e11( &a2 );
	edge e12( &a8 );
	edge e13( &a14 );
	edge e14( &a3 );
	edge e15( &a8 );
	edge e16( &a14 );
	edge e17( &a5 );
	edge e18( &a11 );
	edge e19( &a9 );
	edge e20( &a6 );
	edge e21( &a10 );
	edge e22( &a14 );

	edge e23( &a7 );
	edge e24( &a );

	// edge e25( &a13 );

	edge e26( &a2 );
	edge e27( &a12 );


	a.neighbours.push_back(e);
	a.neighbours.push_back(e2);
	a.neighbours.push_back(e3);
	a4.neighbours.push_back(e4);
	a5.neighbours.push_back(e5);
	a5.neighbours.push_back(e6);
	a6.neighbours.push_back(e7);
	a7.neighbours.push_back(e8);
	a7.neighbours.push_back(e9);
	a7.neighbours.push_back(e10);
	a9.neighbours.push_back(e11);
	a9.neighbours.push_back(e12);
	a9.neighbours.push_back(e13);
	a10.neighbours.push_back(e14);
	a11.neighbours.push_back(e15);
	a11.neighbours.push_back(e16);
	a12.neighbours.push_back(e17);
	a12.neighbours.push_back(e18);
	a12.neighbours.push_back(e19);
	a13.neighbours.push_back(e20);
	a13.neighbours.push_back(e21);
	a13.neighbours.push_back(e22);

	a3.neighbours.push_back(e23);
	a4.neighbours.push_back(e24);

	// a14.neighbours.push_back(e25);

	a8.neighbours.push_back(e26);
	a2.neighbours.push_back(e27);
	
	vector<vertex*> v;
	v.push_back( &a );
	v.push_back( &a3 );
	v.push_back( &a4 );
	v.push_back( &a5 );
	v.push_back( &a2 );
	v.push_back( &a8 );
	v.push_back( &a6 );
	v.push_back( &a7 );
	v.push_back( &a9 );
	v.push_back( &a10 );
	v.push_back( &a11 );
	v.push_back( &a12 );
	v.push_back( &a13 );
	v.push_back( &a14 );

	graph G = graph(v);

	vector<vector<int>> ans = SCC(G);

	vector<int> SC1 = { 1,3,4,6,7,10 };
	vector<int> SC2 = { 13 };
	vector<int> SC3 = { 14 };
	vector<int> SC4 = { 2,5,8,9,11,12 };
	vector<vector<int>> trueans;
	trueans.push_back( SC1 );
	trueans.push_back( SC2 );
	trueans.push_back( SC3 );
	trueans.push_back( SC4 );

	bool result = matches( trueans, ans );

	TT_assert_True( result );

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