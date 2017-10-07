#include<cstdio>
#include<deque>

using namespace std;

int maxarr(deque<int> arr, deque<int> &res);

int main(){
	int n;
	scanf("%d",&n);
	
	deque<int> arr;
	int k;
	
	for(int i=0;i<n;i++){
		scanf("%d",&k);
		arr.push_back(k);
	}
	
	deque<int> res;
	int ans=maxarr(arr,res);
	
	printf("\nMAXIMUM: %d\n\nSUBARRAY: ",ans);
	for(int i=0;i<res.size();i++){
		printf("%d ",res[i]);
	}
	printf("\n\n");
	
	return 0;
}

int maxarr(deque<int> arr, deque<int> &res){
	int len=(int)arr.size();
	
	int currstart=0;
	int currans=0;
	
	int optstart=-1;
	int optstop=-1;
	int optans=0;
	
	for(int i=0;i<len;i++){
		if(currans+arr[i]>0){
			currans+=arr[i];
			if(currans>optans){
				optstart=currstart;
				optstop=i;
				optans=currans;
			}
		}else{
			if(currans>optans){
				optstart=currstart;
				optstop=i-1;
				optans=currans;
			}
			currans=0;
			currstart=i+1;
		}
	}
	
	if(currans>optans){
		optstart=currstart;
		optstop=len-1;
		optans=currans;
	}
	
	if(optstart>=0){
		for(int i=optstart;i<=optstop;i++){
			res.push_back(arr[i]);
		}
	}
	
	return optans;
}






