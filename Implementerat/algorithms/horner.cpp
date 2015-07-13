#include <iostream>

using namespace std;

int horner(int *p, int n, int x){
	if(n==0){
		return *p;
	}
	return *p+x*horner(p+1,n-1,x);
}

int main(){
	int A[]={1,3,2,0,7};
	cout<<horner(A,4,1)<<endl;
	cout<<horner(A,4,0)<<endl;
	cout<<horner(A,4,2)<<endl;
	return 0;
}