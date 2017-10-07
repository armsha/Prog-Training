#include<stdio.h>
#include<vector>

using namespace std;

int gcd(int a, int b){
	if(b>a) return gcd(b,a);
	if(b!=0) return gcd(b,a%b);
	return a;
}

int main(){
	
	for(int m=1;m<10;m++){
		for(int n=1;n<m;n++){
			if(gcd(m,n)==1 && !(m%2==1 && n%2==1)){
				printf("Triple: %d %d %d\n",m*m-n*n,2*m*n,m*m+n*n);
			}
		}
	}
	
	return 0;
}

