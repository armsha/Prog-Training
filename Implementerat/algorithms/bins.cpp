#include <iostream>
using namespace std;

int binS( int A[], int l, int r, int v ){

	// cout << l << r << v << endl;

	if ( l==r )
	{
		return A[l]==v?l:-1;
	} else if (l>r) {
		return -1;
	}

	int mid = (l+r)/2;
	if ( A[mid] == v ){
		return mid;
	} else {
		if ( A[mid] > v )
		{
			return binS(A,l,mid-1,v);
		} else {
			return binS(A,mid+1,r,v);
		}
	}
 
}

int main(int argc, char const *argv[])
{
	
	int A[] = {1,2,3,5,5};
	int B[] = {-1,3,5,7};
	int C[] = {1};

	cout << binS(A,0,4,3) << endl;
	cout << binS(A,0,4,4) << endl;
	cout << binS(B,0,3,-1) << endl;
	cout << binS(C,0,0,1) << endl;

	return 0;
}

