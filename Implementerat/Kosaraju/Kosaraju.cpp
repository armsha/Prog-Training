//Note: Uses edge-list representation of graph

#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<string>

using namespace std;

int N; //No. of vertices
int s;
set<int> V; //Vertices
vector< vector<int> > alist; //Adjacency list
vector<int> f; //f-values of vertices
vector<int> leader; //leaders of vertices
vector<int> explored; //Explored or not?
vector<int> SCC; //Store all SCC sizes at leader indices
vector<int> results; //Store only the SCC sizes
char filename[]="filename.txt"; //Use whatever file name...
                           //Format: Each row: <from> <to>
void DFS(int i, int h); //Secondary DFS, getting passed to by below

void DFS_LOOP(int h);  //Main DFS Loop, passes to DFS above

void INIT(); //Initialize stuff...

void Load_Reverse_Graph(); //Load reversed graph

void Load_Original_Graph(); //Load unreversed graph

void Empty_Graph();

void Print_Results(); //Print ALL the SCC sizes...because why not?

void Writeup_Results(); //Counts the SCC:s by size

int main(){
	INIT();
	
	Load_Reverse_Graph();
	
	DFS_LOOP(0);
	
	Empty_Graph();
	
	Load_Original_Graph();
	
	DFS_LOOP(1);
	
	Writeup_Results();
	
	Print_Results();
	return 0;
}

void DFS_LOOP(int h){
	s=0;
	if(h==0){
		for(int i=N-1;i>=0;i--){
			if(explored[i]==0){
				s=i;
				DFS(i,h);
			}
		}
	}else if(h==1){
		for(int i=N-1;i>=0;i--){
			if(explored[f[i]]==1){
				s=f[i];
				DFS(f[i],h);
			}
		}
	}
}

void DFS(int i, int h){
	if(h==0){
		explored[i]=1;
		for(int j=0;j<alist[i].size();j++){
			if(explored[alist[i][j]]==0){
				DFS(alist[i][j],h);
			}
		}
		f.push_back(i);
	}else{
		explored[i]=0;
		leader[i]=s;
		for(int j=0;j<alist[i].size();j++){
			if(explored[alist[i][j]]==1){
				DFS(alist[i][j],h);
			}
		}
	}
}

void INIT(){
	int i,j;
	//Count no. of vertices
	FILE* fil=fopen(filename,"r");
	while(fscanf(fil,"%d %d",&i,&j)!=EOF){
		V.insert(i);
		V.insert(j);
	}
	fclose(fil);
	N=V.size();
	
	for(int k=0;k<N;k++){
		vector<int> l;
		alist.push_back(l);
		leader.push_back(0);
		explored.push_back(0);
		SCC.push_back(0);
	}
}

void Load_Reverse_Graph(){
	int i,j;
	//Fill in the REVERSE graph
	FILE* fil=fopen(filename,"r");
	while(fscanf(fil,"%d %d",&i,&j)!=EOF){
		alist[j-1].push_back(i-1);
	}
	fclose(fil);
}

void Load_Original_Graph(){
	int i,j;
	//Fill in the ORIGINAL graph
	FILE* fil=fopen(filename,"r");
	while(fscanf(fil,"%d %d",&i,&j)!=EOF){
		alist[i-1].push_back(j-1);
	}
	fclose(fil);
}

void Empty_Graph(){
	for(int k=0;k<N;k++){
		alist[k].clear();
	}
}

void Print_Results(){
	for(int p=0;p<results.size();p++){
		printf("%d ",results[p]);
	}
	printf("\n");
}

void Writeup_Results(){
	for(int p=0;p<N;p++){
		SCC[leader[p]]++;
	}
	for(int p=0;p<N;p++){
		if(SCC[p]>0){
			results.push_back(SCC[p]);
		}
	}
	sort(results.begin(),results.end());
}
