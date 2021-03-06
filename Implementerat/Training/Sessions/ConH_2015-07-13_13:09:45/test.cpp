/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		Convex Hull
 *	INPUT: 
 *		A set S of n two-dimensional points, P_1 ... P_n.
 *	OUTPUT: 
 *		A list of h points, in order, selected to be those that can not be written as
 *		a (convex) combination of any other points. These are the boundary, or convex hull, of
 *		the points.
 *	DESCRIPTION: 
 *		The algorithm should find all those points that lie on the outside boundary of
 *		a set of points, such that all the rest of the points lie in between them. This 
 *		also means that the outside points can not be written as a linear combination of
 *		other points, with their factors positiva and summing to 1. The set should
 *		contain atleast 3 points to make the problem interesting.
 *	USE: 
 *		The convex hull is a basic building block for many geometric algorithms and problems.
 *		For example, the two most distant of a set of points will be two points in the 
 *		convex hull.
 *	COMPLEXITY: 
 *		Common effective algorithms achieve O(n*log(n)) complexity, or O(n*h), where h is the number
 *		of points on the hull. Best is probably O(n*log(h)) algorithms. Naive algorithms would probably 
 *		find O(n^2) or O(n^3).
 */

// Includes and namespace
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef pair<double,double> point;

double getAlpha( point a, point b ) {
	return acos( (a.first*b.first + a.second*b.second) / sqrt( (a.first*a.first + a.second*a.second)*(b.first*b.first + b.second*b.second) ) );
}

double getDist( point a, point b ) {
	return sqrt( (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second) );
}

point pointMin( point a, point b ) {
	return point( a.first - b.first, a.second-b.second );
}

/*
 * Method to implement
 *	DESCRIPTION: 
 *		Find the set of points on the convex hull of the input. Listing all the
 *		outside points of the set.
 *		Use an epsilon of 10^-6, and return only the corner points, not those on lines.
 *	INPUT: 
 *		point S[], representing the set of n points.
 *		int n, the number of points in S.
 *	OUTPUT:
 *		vector< pair<int,int> > H, containing the h points on the hull.
 */	
vector< point > convex_hull( point S[], int n ){

	if ( n <= 2 )
		return vector< point >( S, S+n );

	vector< point > ans;
	point first = S[0];

	for (int i = 1; i < n; ++i)
	{
		if ( (first.second < S[i].second) or (first.second-0.000001 < S[i].second and first.first < S[i].first) )
		{
			first = S[i];
		}
	}
	ans.push_back(first);

	point curr = point( first.first - 1, first.second );
	point last;
	point next = first;
	double bestA;

	do {

		last = curr;
		curr = next;
		next = S[0];
		bestA = 9;

		for (int i = 0; i < n; ++i)
		{
			if ( curr == S[i] )
				continue;

			if ( getAlpha( pointMin(curr,last), pointMin(S[i],curr) )+0.00000001 < bestA or 
				(getAlpha( pointMin(curr,last), pointMin(S[i],curr) )-0.00000001 < bestA and getDist( curr, S[i]) > getDist( curr, next ) ) )
			{
				next = S[i];
				bestA = getAlpha( pointMin(curr,last), pointMin(next,curr) );
			}
		}

		if ( next != first )
			ans.push_back( next );


	} while ( next != first );

	return ans;
}

/*
 * Results to enter when done.
 *	TIME: 2h
 *	COMPLEXITY: O(n*h) Jarvis march
 */

/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"


bool containsSame( vector< point > A, vector< point > B ){

	if (not A.size() == B.size())
	{
		return false;
	}
	
	bool same = true;

	for( point p: A ){

		bool inside = false;
		for( point c: B ){

			if ( p == c )
			{
				inside = true;
				break;
			}
		}

		if ( not inside )
		{
			same = false;
			break;
		}

	}

	return same;
}

/* Test methods */
void testEmpty(){
	point S[] = {};
	TT_assert_True( convex_hull(S,0).size() == 0 );
}

void testSingle(){
	point S[] = { point(0,0) };
	vector< point > ans = convex_hull(S,1);
	vector< point > actual = { point(0,0) };
	TT_assert_True( ans.size() == 1 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testDouble(){
	point S[] = { point(0,0), point(1,1) };
	vector< point > ans = convex_hull(S,2);
	vector< point > actual = { point(0,0), point(1,1) };
	TT_assert_True( ans.size() == 2 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testTriple(){
	point S[] = { point(0,0), point(1,1), point(0,1) };
	vector< point > ans = convex_hull(S,3);
	vector< point > actual = { point(0,0), point(1,1), point(0,1) };
	TT_assert_True( ans.size() == 3 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testOnLine(){
	point S[] = { point(0,0), point(1,1), point(2,2) };
	vector< point > ans = convex_hull(S,3);
	vector< point > actual = { point(0,0), point(2,2) };
	TT_assert_True( ans.size() == 2 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testOnLine2(){
	point S[] = { point(0,0), point(-10,-10), point(-5,-5), point(1,1), point(2,2) };
	vector< point > ans = convex_hull(S,5);
	vector< point > actual = { point(-10,-10), point(2,2) };
	TT_assert_True( ans.size() == 2 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testOneInMiddle(){
	point S[] = { point(0,0), point(1,1), point(0,1), point( 0.25, 0.5 ) };
	vector< point > ans = convex_hull(S,4);
	vector< point > actual = { point(0,0), point(1,1), point(0,1) };
	TT_assert_True( ans.size() == 3 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testNegatives(){
	point S[] = { point( -1,0 ), point(0,-1), point(-1,-1), point( 0, 0 ), point(1,1) };
	vector< point > ans = convex_hull(S,5);
	vector< point > actual = { point(-1,-1), point(0,-1), point(1,1), point(-1,0) };
	TT_assert_True( ans.size() == 4 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testLargeComplete(){

	point S[1000];
	for (int i = 0; i < 1000; ++i)
	{
		S[i] = point( i, i*i );
	}

	vector< point > ans = convex_hull(S,1000);
	vector< point > actual( S, S + sizeof(S) / sizeof(S[0]) );
	TT_assert_True( ans.size() == 1000 );
	TT_assert_True( containsSame( actual, ans ) );
}

void testLarge(){

	point S[2000];
	for (int i = 0; i < 1000; ++i)
	{
		S[i] = point( i, i*i );
		S[i+1000] = point( i, 998.1*i );
	}
	S[1000] = point(2,5);
	S[1999] = point(2,7);

	vector< point > ans = convex_hull(S,2000);
	vector< point > actual( S, S + 1000 );
	TT_assert_True( ans.size() == 1000 );
	TT_assert_True( containsSame( actual, ans ) );

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
	TT_TEST(testDouble);
	TT_TEST(testTriple);
	TT_TEST(testOnLine);
	TT_TEST(testOnLine2);
	TT_TEST(testOneInMiddle);
	TT_TEST(testNegatives);
	TT_TEST(testLargeComplete);
	TT_TEST(testLarge);
	TT_FINAL;

	return 0;
}

#endif