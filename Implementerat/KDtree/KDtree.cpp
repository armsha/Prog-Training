#ifndef __KDTREE__
#define __KDTREE__ 

using namespace std;

// Includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <random>
#include <cmath>
#include <limits>

/* Is there a child on this side of the tree */
#define KDTREE_END NULL


/**
 * For exceptions when using the KDTree.
 */
class KDtreeException: public exception{
	virtual const char* what() const throw(){
		return "Exception in KDTree usage!";
	}
} KDTerr;

/**
 * Interface for comparing functor.
 */
template<typename T> 
class Compare {
public:
	virtual bool operator()( const T& a, const T& b ) = 0;
};

/**
 * Implementation of compare, that takes an implementation to use.
 * Workaround for passing by value, neccessary in for example sort.
 */
template<typename T> 
class Comparator: public Compare<T>{
private:
	Compare<T>& cmp;
public:
	Comparator( Compare<T>& c ): cmp(c) {}
	bool operator()( const T& a, const T& b ) {
		return cmp( a, b );
	}
};

/**
 * For comparing vectors of values.
 * Only checking the dimension of them provided.
 */
template <typename T>
class DimensionComparator: public Compare<T> {
private:
	unsigned int dim;
public:
	DimensionComparator( unsigned int d ) : dim(d) {}
	bool operator()( const T& a, const T& b ){ 
		return a.at(dim) < b.at(dim); 
	}
};

/**
 * For single value comarisons.
 */
template <typename T>
class SingleValueComparator: public Compare<T> {
public:
	bool operator()( const T& a, const T& b ){ return a < b; }
};

/**
 * Apparently this already exists.
 */
template <typename T>
T builtinMedianSelect( vector<T>& values, Comparator<T>& comp ){
	
	if ( values.size() == 0 ){ throw KDTerr; }

	unsigned int mid = values.size() / 2;
	nth_element(values.begin(), values.begin()+mid, values.end(), comp);

	return values[ mid ];
}

/**
 * Kviksort-like,
 * Will leave lower part of the less or equal than median. And 
 * same for above. Semisorted.
 */
template <typename T>
T MyKvikMedianSelect( vector<T>& values, Comparator<T>& comp ){

	if ( values.size() == 0 )
	{
		throw KDTerr;
	} else if ( values.size() <= 2 ){
		return values.front();
	}

	auto mid = values.begin() + (values.size() / 2);

	auto fst = values.begin();
	auto lst = values.end();
	auto pivpos = values.begin();
	T pivval = *pivpos;
	T tmp;
	auto checkpos = values.begin();

	while ( fst < lst ){

		pivpos = fst+1;
		checkpos = fst+1;
		pivval = *fst;
		while ( checkpos < lst ){


			if ( comp( *checkpos, pivval ) ){
				// Perform the swap at the positions.

				tmp = *pivpos;
				*pivpos = *checkpos;
				*checkpos = tmp;
				pivpos++;
			}
			checkpos++;

		}
		tmp = *fst;
		*fst = *(pivpos-1);
		*(pivpos-1) = tmp;

		// Only values smaller or equal than pivot to the left of pivpos
		// Chose which side median is on.
		if ( pivpos <= mid ){
			fst = pivpos;
		} else if ( pivpos > mid ) {
			lst = pivpos -1;
		}

	}

	return *mid;
}


/**
 * Using sort.
 */
template <typename T>
T mySlowMedianSelect( vector<T>& values, Comparator<T>& comp ){

	if ( values.size() == 0 ) { throw KDTerr; }

	sort( values.begin(), values.end(), comp );
	unsigned int mid = values.size() / 2;

	return values[ mid ];
}

/**
 * Select the median value.
 *
 * Used in order for the division to split the points evenly.
 * Takes a vector of values, and a comparator of them.
 * Error if no values given.
 */
template <typename T>
T medianSelect( vector<T>& values, Comparator<T>& comp ){

	if ( values.size() == 0 ) { throw KDTerr; }

	return MyKvikMedianSelect(values,comp);
	// return mySlowMedianSelect( values, comp );
	// return builtinMedianSelect(values,comp);
}

/**
 * Simply rotate through all dimensions, using the passed depth.
 */
template <typename T>
unsigned int rotatingDiscern( vector<vector<T>>& values, unsigned int depth = 0 ){

	// Error if no elements.	
	if ( values.size() == 0 ) { throw KDTerr; }

	unsigned int dim = values.front().size(); // Assume all same length.

	// Error if empty vectors.	
	if ( dim == 0 ) { throw KDTerr; }

	return depth % dim;
}

/**
 * Select the next dimension to split after.
 * 
 * Takes a vector of vectors to chose amongst, and optional depth.
 * Error if no values, or zero-dimensional ones. Inner vectors should be of same length.
 */
template <typename T>
unsigned int discernDimension( vector<vector<T>>& values, unsigned int depth = 0 ){

	// Error if no elements.	
	if ( values.size() == 0 ) { throw KDTerr; }

	// Error if empty vectors.	
	if ( values.front().size() == 0 ) { throw KDTerr; }

	return rotatingDiscern(values,depth); 
	/* Better would be to take dimension with maximal abs distance between
	 *  max and min elements. */
	/* Best would be to meassure variance of all dimensions 
	 * and chose that with the highest. */

}

/**
 * Squared distance between two vectors.
 * Using the squared normal distance meassure to avoid needing sqrt.
 */
template <typename T>
T squaredDistance( vector<T> a, vector<T> b ){

	// Error if different lenght	
	if ( a.size() != b.size() ) { throw KDTerr; }

	// Error if no elements.	
	if ( a.size() == 0 ) { throw KDTerr; }

	T sum = (a.front()-b.front())*(a.front()-b.front());
	for ( unsigned int i = 1; i < a.size(); i++ ){
		sum += (a.at(i)-b.at(i))*(a.at(i)-b.at(i));
	}

	return sum;
}

/**
 * Squared distance between two vectors.
 * Using the squared normal distance meassure to avoid needing sqrt.
 */
template <typename T>
T infinityNorm( vector<T> a, vector<T> b ){

	// Error if different lenght	
	if ( a.size() != b.size() ) { throw KDTerr; }

	// Error if no elements.	
	if ( a.size() == 0 ) { throw KDTerr; }

	T max = abs(a.front()-b.front());
	for ( unsigned int i = 1; i < a.size(); i++ ){
		if ( abs(a.at(i)-b.at(i)) > max ) 
			max = abs(a.at(i)-b.at(i));
	}

	return max;
}

/**
 * Normal distance between two vectors.
 * Using the 2-norm distance meassure.
 */
template <typename T>
T regularDistance( vector<T> a, vector<T> b ){

	return sqrt( squaredDistance(a,b) );
}

/**
 * Meassure how dissimilar two 'points' are.
 * Could for example be a norm, or square distance.
 * Vectors should be of equal lenght.
 */
template <typename T>
T dissimilarityMeassure( vector<T> a, vector<T> b ){

	// Error if different lenght	
	if ( a.size() != b.size() ) { throw KDTerr; }

	// Error if no elements.	
	if ( a.size() == 0 ) { throw KDTerr; }

	// return squaredDistance( a, b );
	return regularDistance(a,b);
	// return infinityNorm(a,b);
	/* The infinity norm is perhaps better. */
}

/**
 * KDTree
 * A kind of multidimensional binary tree, allowing for fast algorithms
 * dealing with spatial-like data.
 * Currently implementing a O(log(n))'ish  nearest neighbour search.
 * Choices about how to pick dimension to divide at, median, and how to
 * store values could be tried differently. Currently only one value is 
 * stored at each node of the tree.
 * Works by dividing the tree in halves by the median, such that half of 
 * the points larger than the current node is bigger in a chosen dimension.
 * Then this is performed again at each half of the set, dividing them 
 * further along the other directions. Imagine a hyperplane located at the 
 * median in the chosen dimension, and orthogonal to this, dividing all the 
 * points in half. This can then be used to simpy tell whether something needs
 * to be in a given half of the tree, just compare it to the given plane.
 * Creating the tree from a set of n points will be O(k*n*log(n)), if a 
 * sofisticated way to chose dividing dimensions is used. In the current 
 * version no such thing is used, but we should achieve O(n*log(n)) for
 * random sets of points.
 */
template <typename T>
class KDtree
{

private:

	KDtree<T>* 		left;	// left subtree.
	KDtree<T>* 		right;	// right subtree.
	unsigned int 	depth;	// depth of this subtree (0 for root).
	unsigned int 	dim;	// dimension this tree divides at.
	unsigned int 	size;	// total size of the tree
	vector<T>*		node;	// hyperplane of this division located at this value.

	/**
	 * Make sure that all values in the left half is smaller than the median.
	 */
	vector<T> pivotValues( vector<vector<T>>& values, vector<T> medianV, Comparator<vector<T>>& comp ){

		unsigned int mid = values.size() / 2; 

		auto fst = values.begin();
		auto lst = values.end();
		auto checkpos = values.begin();
		auto pivpos = values.begin();
		auto movpos = values.begin();

		// Check if already correct.
		bool isCorrect = true;
		while ( checkpos < lst ){

			if ( checkpos < fst+mid ){
				if ( comp( medianV, *checkpos ) ) {
					isCorrect = false;
					break;
				}
			} else if ( checkpos > fst+mid ) {
				if ( comp( *checkpos, medianV ) ) {
					isCorrect = false;
					break;
				}
			} else {
				if ( comp(*checkpos, medianV) or comp(medianV,*checkpos) ){
					isCorrect = false;
					break;
				}
			}
			checkpos++;

		}
		if (isCorrect) return values.at(mid);

		// Find a median.
		checkpos = values.begin();
		while ( checkpos < lst ){
			if ( not comp(medianV,*checkpos) and not comp(*checkpos,medianV) ){
				*pivpos = *checkpos;
			}
			checkpos++;
		}

		// Move things to correct positions.
		checkpos = values.begin();
		movpos = values.begin();
		auto tmppos = values.front();
		while ( checkpos < lst ){
			if ( comp( *checkpos, medianV ) ){
				tmppos = *movpos;
				*movpos = *checkpos;
				*checkpos = tmppos;
				movpos++;
			}
			checkpos++;
		}
		tmppos = *pivpos;
		*pivpos = *movpos;
		*movpos = tmppos;

		isCorrect = true;
		while ( checkpos < lst ){

			if ( checkpos < fst+mid ){
				if ( comp( medianV, *checkpos ) ) {
					isCorrect = false;
					break;
				}
			} else if ( checkpos > fst+mid ) {
				if ( comp( *checkpos, medianV ) ) {
					isCorrect = false;
					break;
				}
			} else {
				if ( comp(*checkpos, medianV) or comp(medianV,*checkpos) ){
					isCorrect = false;
					break;
				}
			}
			checkpos++;

		}
		if ( not isCorrect )
			cerr << endl << "NOT CORRECT AT ALL!!!!" << endl << endl;


		return *movpos;
	}



public:
	/**
	 * Create a new KDtree with the given set of values.
	 * Will assume that the depth is 0 if none is given.
	 * Recursively creates subtrees.
	 * Will take O(n*log(n)) normally (depending on distribution)-
	 * also maybe multiply the k-dimension if discerning cares about all.
	 */
	KDtree( vector<vector<T>>& values, unsigned int depth = 0 ){

		// Handle errors
		// Error if no elements.	
		if ( values.size() == 0 ) { throw KDTerr; }
		

		// Discern dimension - save as dim
		dim = discernDimension( values, depth );
		size = values.size();
		this->depth = depth;

		// Handle small sets.
		if ( values.size() == 1 ) {
			node = new vector<T>(values.front());
			left = KDTREE_END;
			right = KDTREE_END;
			return;
		}

		// Divide at median for this dimension
		DimensionComparator<vector<T>> dc( dim );
		Comparator<vector<T>> dimcmp( dc );
		vector<T> medianV = medianSelect( values, dimcmp );

		// Check that only values smaller or equal to median is to the left.
		// If not pivot them there. - save middle as node.
		node = new vector<T>( pivotValues( values, medianV, dimcmp ) );
		// node = new vector<T> (medianV);

		// Create left and right subtrees with the divided values, if any left.
		unsigned int mid = values.size() / 2; 

		if ( not (values.at(mid)==*node) ){
			if ( mid > 0 and (values.at(mid -1)==medianV) ) mid--;
			else if ( mid < values.size()-1 and (values.at(mid+1)==medianV ) ) mid ++;
		}

			// Setup left 	
		if( values.begin() < values.begin()+mid ) {
			vector<vector<T>> lvals(values.begin(),values.begin()+mid);
			left = new KDtree(lvals,depth+1);
		} else left = KDTREE_END;
		
			// Setup right
		if (values.begin()+1+mid < values.end()) {
			vector<vector<T>> rvals(values.begin()+1+mid,values.end());
			right = new KDtree(rvals,depth+1);
		} else right = KDTREE_END;
	}
	/**
	 * Clear up the tree, deleting the subtrees and stored node.
	 */
	~KDtree(){
		if ( not (left == KDTREE_END) ) delete left;
		if ( not (right == KDTREE_END) ) delete right;
		delete node;
	}

	/**
	 * Get total size of the tree
	 * @return the size
	 */
	unsigned int getSize() const { return size; }

	/**
	 * Get the dimension at this level of the tree.
	 * @return the dimension
	 */
	unsigned int getDim() const { return dim; }

	/**
	 * Get the depth at this level of the tree.
	 * @return the depth
	 */
	unsigned int getDepth() const { return depth; }

	/**
	 * Get the 'dim' coordinate of this levels dividing hyperplane.
	 * @return     the plane 'dim'-coordinate
	 */
	T getHyperplaneLocation() const { return node->at(dim); }

	/**
	 * Get the hyperplane dividing this level.
	 * Will be a vector of correct size with 0 everywhere but dim,
	 * which will contain the hyperplanelocation.
	 * @return     the plane
	 */
	vector<T> getHyperplane() const { 
		vector<T> plane;
		for ( unsigned int i = 0; i < node->size(); i++ ){
			if ( i == dim ) plane.push_back( getHyperplaneLocation() );
			else plane.push_back(0);
		}
		return plane;
	}

	/**
	 * Get the node of this level of the tree.
	 * @return the node value at this level.
	 */
	vector<T> getNode() const { return *node; }

	/**
	 * Get the left subtree.
	 * @return a pointer to a KDTree to the left.
	 */
	KDtree<T>* getLeft() const { return left; }

	/**
	 * Get the right subtree.
	 * @return a pointer to a KDTree to the right.
	 */
	KDtree<T>* getRight() const { return right; }

	/**
	 * Find the nearest neighbour of a target position.
	 * Will use the KDTree structure to do this quickly (log(N) if divisions chosen well)
	 * @return the vector closest in the tree to the given one.
	 */
	vector<T> nearestNeighbour( vector<T>& tar ) const {

		vector<T> curr = getNode(); 

		// If this is a leaf, unwind.
		if ( (getLeft() == KDTREE_END) and (getRight()==KDTREE_END) ){
			return curr;
		}

		// Continue to check the correct subtree.
		vector<T> best;
		unsigned int d = getDim();
		KDtree<T>* ll = getLeft();
		KDtree<T>* rr = getRight();
		if ( tar.at(d) <= getNode().at(dim) ){
			if (ll ==KDTREE_END) best = rr->nearestNeighbour( tar ); // Make sure it is not null
			else best = ll->nearestNeighbour( tar );
		} else {
			if (rr ==KDTREE_END) best = ll->nearestNeighbour( tar );
			else best = rr->nearestNeighbour( tar ); 
		}


		T bestdist = dissimilarityMeassure( best, tar );
		// Check if this node is better than the subtrees
		if (  bestdist \
				>= dissimilarityMeassure( curr, tar ) ){
			best = curr;
			bestdist = dissimilarityMeassure( best, tar );
		}

		// Check if something can be closer at the other side of the tree
		vector<T> plane = getHyperplane();
		vector<T> ball; // Translate hyperball distance and compare to hyperplane
		for ( unsigned int i = 0; i < node->size(); i++ ){
			if ( i == d ) ball.push_back( best.at(i) );
			else ball.push_back(0);
		}
		if ( bestdist \
				>= dissimilarityMeassure( plane, ball ) ){
			// Ball crosses the plane.
			// Continue into other subtree.
			vector<T> contender;
			if ( tar.at(d) <= getNode().at(dim) ){
				if (rr ==KDTREE_END) contender = best; // Avoid Null
				else contender = rr->nearestNeighbour( tar );
			} else {
				if (ll ==KDTREE_END) contender = best; // Avoid Null
				else contender = ll->nearestNeighbour( tar ); 
			}

			if (  bestdist \
					>= dissimilarityMeassure( contender, tar ) ){
				best = contender;
				bestdist = dissimilarityMeassure( best, tar );
			}
		}

		return best;

	}

	friend std::ostream& operator<<(std::ostream& os, const KDtree<T>& tree){

        os << "KDT: depth " << tree.depth << \
        	", division dimension " << tree.dim << \
        	", total size " << tree.size << endl;
        
        os << "    Node at [";
        for ( T e : *tree.node ) os << e << ", ";
        os << "]" << endl;

		os << "    Left: d=" << tree.depth << endl;
        if (not (tree.left == KDTREE_END) ) os << (*tree.left) << endl;
        else os << "    No Left subtree." << endl;

        os << "    Right:  d=" << tree.depth << endl;
        if (not (tree.right == KDTREE_END) ) os << (*tree.right);
      	else os << "    No Right subtree.";

        return os;
    }


};


#ifdef __TEST__
#include "tt_test.h"

void testSelectSimple(){

	vector<int> small;

	small.push_back(1);
	small.push_back(2);
	small.push_back(3);

	SingleValueComparator<int> svc;
	Comparator<int> svComp( svc );

	int ans = medianSelect( small, svComp );
	TT_assert_EQ( ans, 2 );

}

void testSelectBigger(){

	vector<float> small;

	small.push_back(1.1);
	small.push_back(2.2);
	small.push_back(3.3);
	small.push_back(1.2);
	small.push_back(2.3);
	small.push_back(3.4);
	small.push_back(1.3);
	small.push_back(2.5);

	// small.push_back(1.1);
	// small.push_back(1.2);
	// small.push_back(1.3);
	// small.push_back(2.2);
	// small.push_back(2.3);
	// small.push_back(2.5);
	// small.push_back(3.3);
	// small.push_back(3.4);
	// 
	SingleValueComparator<float> fsvc;
	Comparator<float> svComp(fsvc);

	float ans = medianSelect( small, svComp );
	bool t = FLOAT_EQ( ans, 2.3, 0.01 ) or FLOAT_EQ( ans, 2.2, 0.01 );
	TT_assert_True( t );

}

void testSelectVector(){

	vector<vector<int>> set;

	int iA[] = {1,9,2};
	int iB[] = {2,7,32};
	int iC[] = {3,5,4};
	int iD[] = {4,3,16};
	int iE[] = {5,1,8};

	vector<int> pA ( iA, iA + sizeof(iA)/sizeof(int));
	vector<int> pB ( iB, iB + sizeof(iB)/sizeof(int));
	vector<int> pC ( iC, iC + sizeof(iC)/sizeof(int));
	vector<int> pD ( iD, iD + sizeof(iD)/sizeof(int));
	vector<int> pE ( iE, iE + sizeof(iE)/sizeof(int));

	set.push_back(pA);
	set.push_back(pB);
	set.push_back(pC);
	set.push_back(pD);
	set.push_back(pE);


	DimensionComparator<vector<int>> d1(0);
	Comparator<vector<int>> cmp1(d1);

	DimensionComparator<vector<int>> d2(1); 
	Comparator<vector<int>> cmp2(d2);

	DimensionComparator<vector<int>> d3(2);  
	Comparator<vector<int>> cmp3(d3);

	vector<int> ans1 = medianSelect(set,cmp1);
	vector<int> ans2 = medianSelect(set,cmp2);
	vector<int> ans3 = medianSelect(set,cmp3);

	TT_assert_EQ( ans1, pC );
	TT_assert_EQ( ans2, pC );
	TT_assert_EQ( ans3, pE );

}

void testSelectEdge(){

	vector<char> small;

	small.push_back('1');

	SingleValueComparator<char> csvc;
	Comparator<char> svComp(csvc);

	char ans = medianSelect( small, svComp );
	TT_assert_EQ( ans, '1' );

}

void testSelectError(){

	vector<char> v;
	bool excp = false;
	SingleValueComparator<char> csvc;
	Comparator<char> svComp(csvc);
	try {
		medianSelect( v, svComp );
	} catch ( exception& e ){
		excp = true;
	}
	TT_assert_True(excp);

}

void testSelectLarge(){

	minstd_rand0 gen;
	vector<double> v;

	SingleValueComparator<double> csvc;
	Comparator<double> svComp(csvc);

	for (int i = 0; i < 1000; ++i)
	{
		v.push_back( gen() );
	}

	double ms = medianSelect( v, svComp );

	sort( v.begin(), v.end(), svComp );
	double cs = v[v.size()/2];

	TT_assert_EQ( ms, cs );


	vector<double> vv;

	for (int i = 0; i < 1001; ++i)
	{
		vv.push_back( gen() );
	}

	double ms2 = medianSelect( vv, svComp );

	sort( vv.begin(), vv.end(), svComp );
	double cs2 = vv[vv.size()/2];

	TT_assert_EQ( ms2, cs2 );

}

void testDiscernError(){

	vector<vector<char>> v;

	bool excp = false;

	try {
		discernDimension( v );
	} catch ( exception& e ){
		excp = true;
	}
	TT_assert_True(excp);

	vector<char> e;
	v.push_back(e);
	excp = false;
	
	try {
		discernDimension( v );
	} catch ( exception& e ){
		excp = true;
	}
	TT_assert_True(excp);

}

void testDiscernRange(){

	vector<vector<char>> v;

	vector<char> e1;
	vector<char> e2;
	vector<char> e3;

	e1.push_back('a');
	e2.push_back('b');
	e3.push_back('c');

	v.push_back(e1);
	v.push_back(e2);
	v.push_back(e3);

	unsigned int d = discernDimension(v);

	TT_assert_True( d < v.size() );

}

void testTriangleInequality(){

	minstd_rand0 gen;
	double a, b, c;

	a =gen();
	b =gen();
	c =gen();
	vector<double> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);


	a =gen();
	b =gen();
	c =gen();
	vector<double> vv;
	vv.push_back(a);
	vv.push_back(b);
	vv.push_back(c);


	a =gen();
	b =gen();
	c =gen();
	vector<double> vvv;
	vvv.push_back(a);
	vvv.push_back(b);
	vvv.push_back(c);

	double vtvv = dissimilarityMeassure(v,vv);
	double vvtvvv = dissimilarityMeassure(vv,vvv);
	double vtvvv = dissimilarityMeassure(v,vvv);
	double dd = vvtvvv + vtvv;

	// cerr << vtvv << endl << vvtvvv << endl << vtvvv << endl << dd << endl;

	TT_assert_True( vtvvv <= dd );


}

void testKDTreeSimple(){

	vector<vector<int>> set;

	int iA[] = {1,9,2};
	int iB[] = {2,7,32};
	int iC[] = {3,5,8};
	int iD[] = {4,3,16};
	int iE[] = {5,1,4};

	vector<int> pA ( iA, iA + sizeof(iA)/sizeof(int));
	vector<int> pB ( iB, iB + sizeof(iB)/sizeof(int));
	vector<int> pC ( iC, iC + sizeof(iC)/sizeof(int));
	vector<int> pD ( iD, iD + sizeof(iD)/sizeof(int));
	vector<int> pE ( iE, iE + sizeof(iE)/sizeof(int));

	set.push_back(pA);
	set.push_back(pB);
	set.push_back(pC);
	set.push_back(pD);
	set.push_back(pE);

	KDtree<int>* t = new KDtree<int>( set, 0 );
	// cout << *t << endl;

	unsigned int s = t->getSize();
	TT_assert_EQ( s, 5 );

	vector<int> nn = t->getNode(); 
	TT_assert_EQ( nn, pC );

	int hp = t->getHyperplaneLocation();
	unsigned int dm = t->getDim();
	int dmcord = nn[dm];
	TT_assert_EQ( hp, dmcord );

	delete t;

}

void testKDTreeError(){

	vector<vector<int>> set;

	bool excp = false;

	try {
		KDtree<int> t( set );
	} catch ( exception& e ){
		excp = true;
	}
	TT_assert_True(excp);

}

void testKDTreeSmall(){

	vector<vector<int>> set1;
	vector<int> pA1 ( {1,9,2} );
	set1.push_back(pA1);
	KDtree<int>* t1 = new KDtree<int>( set1, 0 );
	// cout << *t1 << endl;

	vector<vector<int>> set2;
	vector<int> pA2 ( {1,9,2} );	
	vector<int> pB2 ( {2,7,32} );
	set2.push_back(pA2);
	set2.push_back(pB2);
	KDtree<int>* t2 = new KDtree<int>( set2 );
	// // cout << *t2 << endl;
	
	vector<vector<int>> set3;	
	vector<int> pA3 ( {1,9,2} );	
	vector<int> pB3 ( {2,7,32} );
	vector<int> pC3 ( {3,5,8} );
	set3.push_back(pA3);
	set3.push_back(pB3);
	set3.push_back(pC3);
	KDtree<int>* t3 = new KDtree<int>( set3 );
	// cout << *t3 << endl;

	unsigned int s1 = t1->getSize();
	TT_assert_EQ( s1, 1 );


	unsigned int s2 = t2->getSize();
	TT_assert_EQ( s2, 2 );


	unsigned int s3 = t3->getSize();
	TT_assert_EQ( s3, 3 );

	delete t1;
	delete t2;
	delete t3;

}

void testKDTreeLarge(){

	vector<vector<double>> set;

	minstd_rand0 gen;

	double a, b, c, d;
	for (int i = 0; i < 1001; ++i)
	{
		a =gen();
		b =gen();
		c =gen();
		d =gen();
		vector<double> vv;
		vv.push_back(a);
		vv.push_back(b);
		vv.push_back(c);
		vv.push_back(d);
		set.push_back(vv);
	}

	KDtree<double>* tt = new KDtree<double>( set, 0 );

	// cerr << *tt << endl;

	KDtree<double>* next = tt;
	vector<double> v = tt->getNode(); 
	unsigned int dim = tt->getDim();
	double oldv = v.at(dim);
	double currv;

	// Check that its decreasing to the left by each dim.
	while ( not (next == KDTREE_END) ){

		v = next->getNode();
		currv = v.at(dim);
		dim = next->getDim();

		TT_assert_True( currv <= oldv );

		oldv = v.at(dim);

		next = next->getLeft();
	}

	next = tt;
	v = tt->getNode();
	dim = tt->getDim();
	oldv = v.at(dim);
	// Check that its decreasing to the left in the same coord.
	while ( not (next == KDTREE_END) ){

		v = next->getNode();
		currv = v.at(dim);

		TT_assert_True( currv <= oldv );

		next = next->getLeft();
	}


	next = tt;
	v = tt->getNode();
	dim = tt->getDim();
	oldv = v.at(dim);
	// Check that its INCREASING to the RIGHT by each dim.
	while ( not (next == KDTREE_END) ){

		v = next->getNode();
		currv = v.at(dim);
		dim = next->getDim();

		TT_assert_True( currv >= oldv );

		oldv = v.at(dim);

		next = next->getRight();
	}

	next = tt;
	v = tt->getNode();
	dim = tt->getDim();
	oldv = v.at(dim);
	// Check that its INCREASING to the RIGHT in the same coord.
	while ( not (next == KDTREE_END) ){

		v = next->getNode();
		currv = v.at(dim);

		TT_assert_True( currv >= oldv );
		
		next = next->getRight();
	}

	// We do not check everything in between !

	delete tt;

}

void testNearestNeighbourSmall(){
	vector<vector<int>> set;

	int iA[] = {1,9,2};
	int iB[] = {2,7,32};
	int iC[] = {3,5,8};
	int iD[] = {4,3,16};
	int iE[] = {5,1,4};

	vector<int> pA ( iA, iA + sizeof(iA)/sizeof(int));
	vector<int> pB ( iB, iB + sizeof(iB)/sizeof(int));
	vector<int> pC ( iC, iC + sizeof(iC)/sizeof(int));
	vector<int> pD ( iD, iD + sizeof(iD)/sizeof(int));
	vector<int> pE ( iE, iE + sizeof(iE)/sizeof(int));

	set.push_back(pA);
	set.push_back(pB);
	set.push_back(pC);
	set.push_back(pD);
	set.push_back(pE);

	KDtree<int>* t = new KDtree<int>( set, 0 );

	vector<int> closest = t->nearestNeighbour( pA );
	TT_assert_EQ( closest, pA );

	closest = t->nearestNeighbour( pB );
	TT_assert_EQ( closest, pB );

	closest = t->nearestNeighbour( pC );
	TT_assert_EQ( closest, pC );

	closest = t->nearestNeighbour( pD );
	TT_assert_EQ( closest, pD );

	closest = t->nearestNeighbour( pE );
	TT_assert_EQ( closest, pE );

	delete t;
}

void testNearestNeighbourDifferent(){

	vector<vector<int>> set;

	int iA[] = {1,9,2};
	int iB[] = {2,7,32};
	int iC[] = {3,5,8};
	int iD[] = {4,3,16};
	int iE[] = {5,1,4};

	vector<int> pA ( iA, iA + sizeof(iA)/sizeof(int));
	vector<int> pB ( iB, iB + sizeof(iB)/sizeof(int));
	vector<int> pC ( iC, iC + sizeof(iC)/sizeof(int));
	vector<int> pD ( iD, iD + sizeof(iD)/sizeof(int));
	vector<int> pE ( iE, iE + sizeof(iE)/sizeof(int));

	set.push_back(pA);
	set.push_back(pB);
	set.push_back(pC);
	set.push_back(pD);
	set.push_back(pE);

	KDtree<int>* t = new KDtree<int>( set, 0 );

	// cerr << *t << endl;

	vector<int> different ({0,10,0});
	vector<int>	closest = t->nearestNeighbour( different ); 

	TT_assert_EQ( closest, pA );


	vector<int> different2 ({-100,100,-130});
	closest = t->nearestNeighbour( different2 );

	TT_assert_EQ( closest, pA );


	vector<int> different3 ({130,-10,5});
	closest = t->nearestNeighbour( different3 ); 

	TT_assert_EQ( closest, pE );

	delete t;

}

void testNearestLarge(){

	vector<vector<double>> set;

	minstd_rand0 gen;
	int siz = 22;

	double a, b, c, d,e;
	for (int i = 0; i < siz; ++i)
	{

		a =gen();
		b =gen();
		c =gen();
		d =gen();
		e =gen();
		vector<double> vv;
		vv.push_back(a);
		vv.push_back(b);
		vv.push_back(c);
		vv.push_back(d);
		vv.push_back(e);
		set.push_back(vv);
	}

	KDtree<double>* tt = new KDtree<double>( set, 0 );


	a =gen();
	b =gen();
	c =gen();
	d =gen();
	e =gen();
	vector<double> target;
	target.push_back(a);
	target.push_back(b);
	target.push_back(c);
	target.push_back(d);
	target.push_back(e);


	double currdist;
	vector<double> currpos;
	double mindist = numeric_limits<double>::infinity();
	for ( int i = 0; i< siz ; i++){
		currpos = set.at(i);
		currdist = dissimilarityMeassure( currpos, target );
		if ( currdist < mindist ) mindist = currdist;
	}

	currpos = tt->nearestNeighbour(target);
	currdist = dissimilarityMeassure( currpos, target );

	// cerr << currdist << endl << mindist;

	TT_assert_True( FLOAT_EQ( currdist, mindist, 0.00000001 ) );

	delete tt;
}



int main(int argc, char const *argv[])
{
	
	cerr << "Test the selection function:" << endl;
	TT_SETUP;
	TT_TEST(testSelectSimple);
	TT_TEST(testSelectBigger);
	TT_TEST(testSelectVector);
	TT_TEST(testSelectEdge);
	TT_TEST(testSelectError);
	TT_TEST(testSelectLarge);
	TT_FINAL;

	cerr << "Test the discerning function:" << endl;
	TT_SETUP;
	TT_TEST(testDiscernError);
	TT_TEST(testDiscernRange);
	TT_FINAL;


	cerr << "Test the dissimilarity meassure:" << endl;
	TT_SETUP;
	TT_TEST(testTriangleInequality);
	TT_FINAL;

	cerr << "Test the tree creation:" << endl;
	TT_SETUP;
	TT_TEST(testKDTreeSimple);
	TT_TEST(testKDTreeError);
	TT_TEST(testKDTreeSmall);
	TT_TEST(testKDTreeLarge);
	TT_FINAL;


	cerr << "Test the nearest neighbour method:" << endl;
	TT_SETUP;
	TT_TEST(testNearestNeighbourSmall);
	TT_TEST(testNearestNeighbourDifferent);
	TT_TEST(testNearestLarge);
	TT_FINAL;

	return 0;
}

#endif


#endif