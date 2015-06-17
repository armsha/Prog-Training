/*
 * Algorithm implementation training test suite.
 *	NAME: 
 *		String Search
 *	INPUT: 
 *		A text T, of length n, and a pattern P, of length m.
 *		T and P is either strings, or equivalently, arrays of integers.
 *	OUTPUT: 
 *		The index i, at which P has the same contents as the substring of 
 *		T starting at this index, or an indication that no such i exists.
 *	DESCRIPTION: 
 *		The objective here is to find an index after which the "letters" of T is
 *		the same as those in P. That is T[i]...T[i+m-1] == P[0]...P[m-1].
 *	USE:
 *		This is used everywhere, the simplest imaginable application would be
 *		The simple string search. Note however that it often is not strings and
 *		text we match in, but rather other things we represent by lists of
 *		symbols.
 *	COMPLEXITY: 
 *		The naive solution runs at O(n*m), but there exists several different
 *		solutions running at O(n+m).
 */

// Includes and namespace

/*
 * Method to implement
 *	DESCRIPTION:
 *		Implement a string-search method, looking through T for an index i at
 *		which the following m letters in T is equal to those in P. Return the
 *		first such index i, or mark that none exist by returning -1.
 *	INPUT:
 *		char T[], The main text to search
 *		int  n, The length of T
 *		char P[], The pattern to search for
 *		int  m, The length of P
 *	OUTPUT: 
 *		int   i, The index the match starts at, or -1 if no such exist
 */	
int stringSearch( const char T[], int n, const char P[], int m ) {
	
	if (m==0)
	{
		return 0;
	}

	if (m>n)
	{
		return -1;
	}

	bool failed;
	for (int i = 0; i < n-m+1; ++i)
	{
		failed = false;
		for (int j = 0; j < m; ++j)
		{
			if (T[i+j]!=P[j])
			{
				failed = true;
				break;
			}
		}
		if (failed)
		{
			continue;
		}
		return i;
	}

	return -1;
}

/*
 * Results to enter when done.
 *	TIME: 		5 min
 *	COMPLEXITY: O(n*m) naive solution
 */

/* ------ Test Section ------ */
#ifdef __TEST__

// Includes
#include "tt_test.h"

/* --- Test methods --- */

void testEmptyPattern(){
	int res = stringSearch( "123", 3, "", 0 );
	TT_assert_EQ( 0, res );
}

void testEmptyText(){
	int res = stringSearch( "", 0, "1", 1 );
	TT_assert_EQ( -1, res );
}

void testLongerPattern(){
	int res = stringSearch( "ab", 2, "abc", 3 );
	TT_assert_EQ( -1, res );
}


void testSimpleMatch(){
	int res = stringSearch( "a", 1, "a", 1 );
	TT_assert_EQ( 0, res );
}

void testSimpleMismatch(){
	int res = stringSearch( "a", 1, "b", 1 );
	TT_assert_EQ( -1, res );
}

void testSmallTextMatch(){
	int res = stringSearch( "ab", 2, "b", 1 );
	TT_assert_EQ( 1, res );
}

void testSmallTextMatch2(){
	int res = stringSearch( "abcd", 4, "c", 1 );
	TT_assert_EQ( 2, res );
}


void testSmallPatternMatch(){
	int res = stringSearch( "abcd", 4, "ab", 2 );
	TT_assert_EQ( 0, res );
}

void testSmallPatternMatch2(){
	int res = stringSearch( "abcd", 4, "bc", 2 );
	TT_assert_EQ( 1, res );
}

void testSmallPatternMatch3(){
	int res = stringSearch( "abcd", 4, "bcd", 3 );
	TT_assert_EQ( 1, res );
}

void testSmallPatternMismatch(){
	int res = stringSearch( "abcd", 4, "bb", 2 );
	TT_assert_EQ( -1, res );
}

void testSmallPatternMismatch2(){
	int res = stringSearch( "abcd", 4, "abcc", 4 );
	TT_assert_EQ( -1, res );
}

void testLargeTextsMatch(){
	char T[1000];
	char P[100];

	for ( int i = 0; i<1000; i++ ){
		T[i] = (i+i%99)%101;
	}
	for ( int i = 0; i<100; i++ ){
		P[i] = T[i+900];
	}

	int res = stringSearch( T, 1000, P, 100 );
	TT_assert_EQ( 900, res );
}

void testLargeTextsMismatch(){
	char T[1000];
	char P[100];

	for ( int i = 0; i<1000; i++ ){
		T[i] = (i+i%99)%101;
	}
	for ( int i = 0; i<100; i++ ){
		P[i] = T[i+900];
	}
	P[99]=0;

	int res = stringSearch( T, 1000, P, 100 );
	TT_assert_EQ( -1, res );
}

/* 
 * Main method
 * Runs all the tests, and prints the result
 */
int main(int argc, char const *argv[])
{

	TT_SETUP;
	TT_TEST(testEmptyPattern);
	TT_TEST(testEmptyText);
	TT_TEST(testLongerPattern);
	TT_TEST(testSimpleMatch);
	TT_TEST(testSimpleMismatch);
	TT_TEST(testSmallTextMatch);
	TT_TEST(testSmallTextMatch2);
	TT_TEST(testSmallPatternMatch);
	TT_TEST(testSmallPatternMatch2);
	TT_TEST(testSmallPatternMatch3);
	TT_TEST(testSmallPatternMismatch);
	TT_TEST(testSmallPatternMismatch2);
	TT_TEST(testLargeTextsMatch);
	TT_TEST(testLargeTextsMismatch);
	TT_FINAL;

	return 0;
}

#endif