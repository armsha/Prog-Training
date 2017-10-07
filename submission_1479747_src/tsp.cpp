#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<algorithm>
#include<vector>
#include<deque>
#include<set>
#include<map>
#include<climits>
#include<bitset>
#include<limits>

//Macros for minimum and maximum
#define min(a,b) (a<b ? (a):(b))
#define max(a,b) (a>b ? (a):(b))

using namespace std;

//Struct describing the boxes used in Karp's algorithm
typedef struct{
	vector<int> points;
	vector<int> tour;
	double xmin,xmax,ymin,ymax;
	
	vector< vector<double> > cost;
	vector< vector<int> > prev;
}box;

//Read in all xy-coordinates
void readPoints(int n, double (*points)[2]);

//Print a tour
void printTour(int n, int* tour);

//Make all entries of an array zero
void zeroIntArray(int n, int* array);

//Euclidean distance between points n1 and n2
double dist(int n1, int n2, double (*points)[2]);

//Greedy TSP algorithm (same as given on Kattis)
void Greedy(int n, double (*points)[2], int* tour);

//2-OPT optimization
void OPT2(int n, double (*points)[2], int* tour);

//2-OPT step (necessary for the OPT2 routine)
void OPT2Step(int n, int i, int j, int* tour);

//3-OPT optimization
void OPT3(int n, double (*points)[2], int* tour);

//3-OPT step (necessary for the OPT3 routine)
void OPT3Step(int n, int i, int j, int h, int whichcase, int* tour);

//Randomized 2-OPT optimization
void RandomOPT2(int n, double (*points)[2], int* tour);

//Randomized 3-OPT optimization
void RandomOPT3(int n, double (*points)[2], int* tour);

//Random selection of a tour
void RandomTour(int n, double (*points)[2], int* tour);

//Repeated random selection of a tour, outputs the best one found
void RandomRepeat(int n, double (*points)[2], int* tour);

//Copies the contents of tour into newTour
void copyTour(int n, int* tour, int* newTour);

//Computes the total cost of a given tour
double cost(int n, double (*points)[2], int* tour);

//Christophides algorithm
void Christophides(int n, double (*points)[2], int* tour);

//Minimum Spanning Tree, obtained using Prim's algorithm
void MST(int n, double (*points)[2], vector< vector<int> > &tree);

//Filters out odd vertices from mintree, stores in O
void oddVert(int n, vector< vector<int> > &mintree, vector<int> &O);

//Converts a given Euler tour to a valid TSP tour by shortcutting
void EulerToHamilton(int n, int* tour, vector<int> &Euler,double (*points)[2]);

//Computes an Euler tour of an Eulerian graph, using Hierholzer's algorithm
void Hierholzer(int n, vector< vector<int> > G, vector<int> &Euler);

//Returns the nodes of odd degree of an adjacency list
void oddNodes(vector< vector<int> > &adjlist, vector<int> * odd);

//Minimum cost perfect matching on the odd nodes of a graph
void matching(vector< vector<int> > &adjlist, double (*points)[2]);

//Random matching of odd vertices in a MST
void randmatching(vector< vector<int> > &adjlist, double (*points)[2]);

//Doubles the edges of an input graph (usage here: the graph is a tree)
void doubleEdge(vector< vector<int> > &adjlist);

//Karps algorithm, implemented using dynamic programming and Christophides
void Karp(int n, double (*points)[2], int* tour);

//Karps algorithm, implemented using only Christophides as subroutine
void APKarp(int n, double (*points)[2], int* tour);

//Karps algorithm, implemented using only Random3OPT as subroutine
void OPTKarp(int n, double (*points)[2], int* tour);

//Held-Karp dynamic programming algorithm for exactly solving the TSP problem
void DP(double (*points)[2], box &subbox);

//Fills in the DP table of the Held-Karp algorithm
double pathCost(int subset, int endpoint, box & subbox, double (*points)[2]);

//Computes tour by constructing a minimum spanning tree and traversing it in preorder
void mstsp(int n, double (*points)[2], int* tour);

//Computes number of bits set to 1 in the integer i
int numbits(int i);

int main(){
	//Read number of points
	int n;
	scanf("%d",&n);
	
	double points[n][2]; //Point coordinates
	int tour[n];		 //The indices of the final tour will be stored here
	
	double (*pointer)[2]=points; //Pointer to the points
	
	readPoints(n,pointer); //Read the point coordinates
	
	if(n<=3){ //Special case that breaks some of the algorithms if left unchecked
		tour[0]=0;
		tour[1]=1;
		tour[2]=2;
		printTour(n,tour);
		return 0;
	}
	
	/* Choose solution method here */
	
	//Greedy(n,points,tour);
	//OPT2(n,points,tour);
	//OPT3(n,points,tour);
	//RandomOPT2(n,points,tour);
	//RandomOPT3(n,points,tour);
	//RandomTour(n,points,tour);
	//RandomRepeat(n,points,tour);
	//Christophides(n,points,tour);
	//APKarp(n,points,tour);
	RandomOPT3(n,points,tour);
	//OPTKarp(n,points,tour);
	//mstsp(n,points,tour);
	
	/* Choose solution method above */
	
	printTour(n,tour); //Print the final tour
	
	return 0;
}

void readPoints(int n, double (*points)[2]){
	for(int i=0;i<n;i++){
		scanf("%lf %lf", &points[i][0], &points[i][1]);
	}
}

void printTour(int n, int* tour){
	for(int i=0;i<n;i++){
		printf("%d\n",tour[i]);
	}
}

void zeroIntArray(int n, int* array){
	for(int i=0;i<n;i++){
		array[i]=0;
	}
}

double dist(int n1, int n2, double (*points)[2]){
	double xdist=points[n1][0]-points[n2][0];
	double ydist=points[n1][1]-points[n2][1];
	return ceil(sqrt(xdist*xdist + ydist*ydist));
}

//Actually NearestNeighbor?
void Greedy(int n, double (*points)[2], int* tour){
	int best;
	int used[n];
	zeroIntArray(n,used);
	
	tour[0]=0;
	used[0]=1;
	
	for(int i=1;i<n;i++){
		best=-1;
		for(int j=0;j<n;j++){
			if(!used[j] && (best==-1 || dist(tour[i-1],j,points) < dist(tour[i-1],best,points))){
				best=j;
			}
		}
		tour[i]=best;
		used[best]=1;
	}
}

/* 2OPT-algorithm for modifying a constructed tour */
void OPT2(int n, double (*points)[2], int* tour){
	//Greedy(n,points,tour);
	//Christophides(n,points,tour);
	
	int numchecks=1000001;
	
	int suboptimal=1;
	double currentcost, newcost;
	while(suboptimal){
		suboptimal=0;
		for(int i=0;i<n;i++){ //Edge 1 - starting point
			for(int j=i+1;j<n;j++){ //Edge 2 - starting point
				numchecks--;
				if(numchecks<=0){
					return;
				}
				currentcost=dist(tour[i],tour[(i+1)%n],points) + 
				            dist(tour[j],tour[(j+1)%n],points);
				newcost=dist(tour[i],tour[j],points) + 
				            dist(tour[(i+1)%n],tour[(j+1)%n],points);
				
				if(currentcost > newcost){ //Not 2-Optimal
					suboptimal=1;
					//Perform 2Opt-step here
					OPT2Step(n,i,j,tour);
					break;
				}
			}
			
			if(suboptimal){
				break;
			}
		}
	}
}

/* 2OPT-step */
void OPT2Step(int n, int i, int j, int* tour){
	int tour2[n];
	int k=0;
	int index=0;
	int break1=min(i,j), break2=max(i,j);
	
	while(k<=break1){
		tour2[index]=tour[k];
		k++;
		index++;
	}
	
	k=break2;
	
	while(k>break1){
		tour2[index]=tour[k];
		k--;
		index++;
	}
	
	k=break2+1;
	
	while(k<n){
		tour2[index]=tour[k];
		k++;
		index++;
	}
	
	for(k=0;k<n;k++){
		tour[k]=tour2[k];
	}
}

/* 3OPT-algorithm for modifying a constructed tour */
void OPT3(int n, double (*points)[2], int* tour){
	//Greedy(n,points,tour); //Just for debugging purposes
	OPT2(n,points,tour); //We need OPT2-optimality to try OPT3
	
	int numchecks=11000000;
	
	int suboptimal=1;
	double currentcost, newcost;
	while(suboptimal){
		suboptimal=0;
		for(int i=0;i<n;i++){ //Edge 1 - starting point
			for(int j=i+1;j<n;j++){ //Edge 2 - starting point
				for(int h=j+1;h<n;h++){ //Edge 3 - starting point
					numchecks--;
					if(numchecks<=0){
						return;
					}
					
					
					currentcost=dist(tour[i],tour[(i+1)%n],points) + 
					            dist(tour[j],tour[(j+1)%n],points) +
					            dist(tour[h],tour[(h+1)%n],points);
					// Case 1: [i]->[j]->i+1->[h]->j+1->h+1
					newcost=dist(tour[i],tour[j],points) + 
					            dist(tour[(i+1)%n],tour[h],points)+
					            dist(tour[(j+1)%n],tour[(h+1)%n],points);
					
					if(currentcost > newcost){ //Not 3-Optimal
						suboptimal=1;
						//Perform 3Opt-step here
						OPT3Step(n,i,j,h,1,tour);
						break;
					}
					
					// Case 2: [i]->[j+1]->h->[j]->i+1->h+1
					newcost=dist(tour[i],tour[(j+1)%n],points) + 
					            dist(tour[h],tour[j],points)+
					            dist(tour[(i+1)%n],tour[(h+1)%n],points);
					
					if(currentcost > newcost){ //Not 3-Optimal
						suboptimal=1;
						//Perform 3Opt-step here
						OPT3Step(n,i,j,h,2,tour);
						break;
					}
					
					// Case 3: [i]->[j+1]->h->[i+1]->j->h+1
					newcost=dist(tour[i],tour[(j+1)%n],points) + 
					            dist(tour[h],tour[(i+1)%n],points)+
					            dist(tour[j],tour[(h+1)%n],points);
					
					if(currentcost > newcost){ //Not 3-Optimal
						suboptimal=1;
						//Perform 3Opt-step here
						OPT3Step(n,i,j,h,3,tour);
						break;
					}
					
					// Case 4: [i]->[h]->j+1->[i+1]->j->h+1
					newcost=dist(tour[i],tour[h],points) + 
					            dist(tour[(j+1)%n],tour[(i+1)%n],points)+
					            dist(tour[j],tour[(h+1)%n],points);
					
					if(currentcost > newcost){ //Not 3-Optimal
						suboptimal=1;
						//Perform 3Opt-step here
						OPT3Step(n,i,j,h,4,tour);
						break;
					}
				}
			}
			
			if(suboptimal){
				break;
			}
		}
	}
}

/* 3OPT-step */
void OPT3Step(int n, int i, int j, int h, int whichcase, int* tour){
	int tour2[n];
	
	zeroIntArray(n,tour2);
	
	int k=0;
	int index=0;
	int stop1=i, start2, stop2, start3, stop3;
	int incr1, incr2;
	
	switch(whichcase){
		case(1): // [i]->[j]->i+1->[h]->j+1->h+1
			start2=j;
			incr1=-1;
			stop2=i+1;
			start3=h;
			incr2=-1;
			stop3=j+1;
			break;
		case(2): // [i]->[j+1]->h->[j]->i+1->h+1
			start2=j+1;
			incr1=1;
			stop2=h;
			start3=j;
			incr2=-1;
			stop3=i+1;
			break;
		case (3): // [i]->[j+1]->h->[i+1]->j->h+1
			start2=j+1;
			incr1=1;
			stop2=h;
			start3=i+1;
			incr2=1;
			stop3=j;
			break;
		case (4): // [i]->[h]->j+1->[i+1]->j->h+1
			start2=h;
			incr1=-1;
			stop2=j+1;
			start3=i+1;
			incr2=1;
			stop3=j;
			break;
		default:
			break;
	}
	
	while(k<=stop1){
		tour2[index]=tour[k];
		k++;
		index++;
	}
	
	k=start2;
	
	while(k!=stop2){
		tour2[index]=tour[k];
		k+=incr1;
		index++;
	}
	
	tour2[index]=tour[k];
	index++;
	
	k=start3;
	
	while(k!=stop3){
		tour2[index]=tour[k];
		k+=incr2;
		index++;
	}
	
	tour2[index]=tour[k];
	index++;
	
	k=h+1;
	
	while(k<n){
		tour2[index]=tour[k];
		k++;
		index++;
	}
	
	for(k=0;k<n;k++){
		tour[k]=tour2[k];
	}
}


void RandomOPT2(int n, double (*points)[2], int* tour){
	//Greedy(n,points,tour);
	//RandomTour(n,points,tour);
	//APKarp(n,points,tour);
	Christophides(n,points,tour);
	
	int numchecks=1000000;
	
	int suboptimal=1;
	double currentcost, newcost;
	srand(time(NULL));
	int e1, e2;
	for(int i=0;i<numchecks;i++){
		e1=rand()%n;
		e2=rand()%n;
			
		currentcost=dist(tour[e1],tour[(e1+1)%n],points) + 
			            dist(tour[e2],tour[(e2+1)%n],points);
		newcost=dist(tour[e1],tour[e2],points) + 
			            dist(tour[(e1+1)%n],tour[(e2+1)%n],points);
			
		if(currentcost > newcost){ //Not 2-Optimal
			suboptimal=1;
			//Perform 2Opt-step here
			OPT2Step(n,e1,e2,tour);
		}
	}
}


void RandomOPT3(int n, double (*points)[2], int* tour){
	//Greedy(n,points,tour); //Just for debugging purposes
	RandomOPT2(n,points,tour); //We need OPT2-optimality to try OPT3
	//OPT2(n,points,tour); //We need OPT2-optimality to try OPT3
	
	if(n<=3) return;
	
	int numchecks=8700000;
	
	srand(time(NULL));
	
	int e[3];
	int i,j,h;
	
	int suboptimal=1;
	double currentcost, newcost;
	
	for(int ml=0;ml<numchecks;ml++){
		e[0]=rand()%n;
		do{
			e[1]=rand()%n;
		}while(e[1]==e[0]);
		do{
			e[2]=rand()%n;
		}while(e[2]==e[0] || e[2]==e[1]);
		
		sort(e,e+3);
		
		i=e[0];
		j=e[1];
		h=e[2];
		
		currentcost=dist(tour[i],tour[(i+1)%n],points) + 
		            dist(tour[j],tour[(j+1)%n],points) +
		            dist(tour[h],tour[(h+1)%n],points);
		// Case 1: [i]->[j]->i+1->[h]->j+1->h+1
		newcost=dist(tour[i],tour[j],points) + 
		            dist(tour[(i+1)%n],tour[h],points)+
		            dist(tour[(j+1)%n],tour[(h+1)%n],points);
					
		if(currentcost > newcost){ //Not 3-Optimal
			suboptimal=1;
			//Perform 3Opt-step here
			OPT3Step(n,i,j,h,1,tour);
			continue;
		}
					
		// Case 2: [i]->[j+1]->h->[j]->i+1->h+1
		newcost=dist(tour[i],tour[(j+1)%n],points) + 
		            dist(tour[h],tour[j],points)+
		            dist(tour[(i+1)%n],tour[(h+1)%n],points);
					
		if(currentcost > newcost){ //Not 3-Optimal
			suboptimal=1;
			//Perform 3Opt-step here
			OPT3Step(n,i,j,h,2,tour);
			continue;
		}
					
		// Case 3: [i]->[j+1]->h->[i+1]->j->h+1
		newcost=dist(tour[i],tour[(j+1)%n],points) + 
		         dist(tour[h],tour[(i+1)%n],points)+
		            dist(tour[j],tour[(h+1)%n],points);
					
		if(currentcost > newcost){ //Not 3-Optimal
			suboptimal=1;
			//Perform 3Opt-step here
			OPT3Step(n,i,j,h,3,tour);
			continue;
		}
					
		// Case 4: [i]->[h]->j+1->[i+1]->j->h+1
		newcost=dist(tour[i],tour[h],points) + 
		            dist(tour[(j+1)%n],tour[(i+1)%n],points)+
		            dist(tour[j],tour[(h+1)%n],points);
					
		if(currentcost > newcost){ //Not 3-Optimal
			suboptimal=1;
			//Perform 3Opt-step here
			OPT3Step(n,i,j,h,4,tour);
			continue;
		}

	}
}

void RandomTour(int n, double (*points)[2], int* tour){
	for(int i=0;i<n;i++){
		tour[i]=i;
	}
	random_shuffle(tour, tour+n);
}

void copyTour(int n, int* tour, int* newTour){
	for(int i=0;i<n;i++){
		newTour[i]=tour[i];
	}
}

double cost(int n, double (*points)[2], int* tour){
	double ans=0;
	for(int i=0;i<n;i++){
		ans+=dist(tour[i],tour[(i+1)%n],points);
	}
	return(ans);
}

void RandomRepeat(int n, double (*points)[2], int* tour){
	int numchecks=1000;
	int tempTour[n];
	double bestCost=-1, currcost;
	zeroIntArray(n,tempTour);
	
	for(int i=0;i<numchecks;i++){
		RandomTour(n,points,tempTour);
		currcost=cost(n,points,tempTour);
		if(bestCost < 0 || currcost < bestCost){
			copyTour(n,tempTour,tour);
			bestCost=currcost;
		}
	}
}

void Christophides(int n, double (*points)[2], int* tour){
	if(n<=3){
		tour[0]=0;
		tour[1]=1;
		tour[2]=2;
	}
	vector< vector<int> > mintree(n);
	MST(n,points,mintree);
		
	matching(mintree, points);
	//doubleEdge(mintree);
	
	vector<int> Euler;
	
	Hierholzer(n,mintree,Euler);
	
	EulerToHamilton(n, tour, Euler,points);
}

//Prim's algorithm
void MST(int n, double (*points)[2], vector< vector<int> > &tree){
	double C[n];
	int E[n];
	int used[n];
	set<int> Q;
	for(int i=0;i<n;i++){
		used[i]=0;
		C[i]=INT_MAX-1; //Super big number
		E[i]=-1;
		Q.insert(i);
	}
	
	int v;
	double bestcost;
	while(!Q.empty()){
		bestcost=INT_MAX;
		for(set<int>::iterator it=Q.begin(); it!=Q.end(); it++){
			if(C[*it]<bestcost){
				bestcost=C[*it];
				v=*it;
			}
		}
		
		used[v]=1;
		
		if(E[v]>=0){
			used[E[v]]=1;
			tree[v].push_back(E[v]);
			tree[E[v]].push_back(v);
		}
		
		Q.erase(v);
		
		for(set<int>::iterator it=Q.begin(); it!=Q.end(); it++){
			if(C[*it]>dist(v,*it,points)){
				C[*it]=dist(v,*it,points);
				E[*it]=v;
			}
		}
	}
}

void oddVert(int n, vector< vector<int> > &mintree, vector<int> &O){
	for(int i=0;i<n;i++){
		if(mintree[i].size() %2 == 1){
			O.push_back(i);
		}
	}
}

void EulerToHamilton(int n, int* tour, vector<int> &Euler,double (*points)[2]){
	int counter=0;
	int used[n];
	int elen=(int) Euler.size();
	int ind=rand()%elen;
	
	int temptour[n];
	double bestcost=1000000000;
	double currcost;
	
	int jlimit=1000;
	
	for(int j=0;j<jlimit;j++){
		counter=0;
		zeroIntArray(n,used);
		ind=rand()%elen;
		
		for(int i=0;i<elen;i++){
			ind=(ind+1)%elen;
			if(used[Euler[ind]]==0){
				used[Euler[ind]]=1;
				temptour[counter]=Euler[ind];
				counter++;
			}
		}
		currcost=cost(n,points,temptour);
		if(currcost<bestcost){
			bestcost=currcost;
			copyTour(n,temptour,tour);
		}
	}
	
	for(int j=0;j<jlimit;j++){
		counter=0;
		zeroIntArray(n,used);
		ind=rand()%elen;
		
		for(int i=0;i<elen;i++){
			ind=(ind-1)%elen;
			if(ind<0) ind+=elen;
			if(used[Euler[ind]]==0){
				used[Euler[ind]]=1;
				temptour[counter]=Euler[ind];
				counter++;
			}
		}
		currcost=cost(n,points,temptour);
		if(currcost<bestcost){
			bestcost=currcost;
			copyTour(n,temptour,tour);
		}
	}
}

void Hierholzer(int n, vector< vector<int> > G, vector<int> &Euler){
	int currv=0,localv,prevlocalv;
	
	int degree[n];
	for(int i=0;i<n;i++){
		degree[i]=(int) G[i].size();
	}
	
	map< pair<int, int> , int> ecount;
	
	for(int i=0;i<G.size();i++){
		for(int j=0;j<G[i].size();j++){
			ecount.insert(make_pair(make_pair(min(i,G[i][j]),max(i,G[i][j])),0));
			ecount[make_pair(min(i,G[i][j]),max(i,G[i][j]))]++;
		}
	}
	
	for(map< pair<int,int> , int >::iterator it=ecount.begin();it!=ecount.end();it++){
		ecount[it->first]/=2;
	}
	
	deque<int> temptour;
	deque<int> cycle;
	temptour.push_back(0);
	
	while(!temptour.empty()){
		localv=temptour.front();
		prevlocalv=localv;
		Euler.push_back(localv);
		temptour.pop_front();
		
		while(degree[Euler.back()] > 0){
			prevlocalv=localv;
			while(1){
				localv=G[prevlocalv].back();
				G[prevlocalv].pop_back();
				
				if(ecount.find(make_pair(min(prevlocalv,localv),max(prevlocalv,localv)))!=ecount.end() && ecount[make_pair(min(prevlocalv,localv),max(prevlocalv,localv))] > 0){
					degree[prevlocalv]--;
					degree[localv]--;
					ecount[make_pair(min(prevlocalv,localv),max(prevlocalv,localv))]--;
					break;
				}
			}
			cycle.push_back(localv);
		}
		
		while(!cycle.empty()){
			temptour.push_front(cycle.back());
			cycle.pop_back();
		}
	}
}


/* OddNodes */
void oddNodes(vector< vector<int> > &adjlist, vector<int> &odd){
  for (int i = 0; i < adjlist.size(); i++) {
    if (adjlist[i].size() % 2 != 0) {
      odd.push_back(i);
    }
  }
}

/* matching */
void matching(vector< vector<int> > &adjlist, double (*points)[2]) {
  /* Compute the list of nodes of odd degree for the given graph */
  vector<int> odd;
  oddNodes(adjlist, odd);
  
  /* for each odd node u, find the minimum cost edge that matches u with 
     another odd node v */
     
  vector<int>::iterator first;
  vector<int>::iterator iterator;
  vector<int>::iterator bestNode;
  double best;
  
  while(!odd.empty()) {
    first = odd.begin();
    iterator = first +1;
    best = -1.0;
    
    /* greedily find the best edge */
    while(iterator < odd.end()) {
      if ((best == -1.0 || dist(*first,*iterator,points) < best)) {
        best = dist(*first,*iterator,points);
        bestNode = iterator;
      }
      iterator++;
    }
    
    /* complete the graph */
    adjlist[*first].push_back(*bestNode);
    adjlist[*bestNode].push_back(*first);
    
    /* remove the used nodes from the odd list */
    odd.erase(first);
    
    odd.erase(bestNode-1);
  }
}

/* random matching */
void randmatching(vector< vector<int> > &adjlist, double (*points)[2]) {
  /* Compute the list of nodes of odd degree for the given graph */
  vector<int> odd;
  oddNodes(adjlist, odd);
  
  random_shuffle(odd.begin(), odd.end());
  
  for(int i=0;i<odd.size(); i+=2){
  	adjlist[odd[i]].push_back(odd[i+1]);
  	adjlist[odd[i+1]].push_back(odd[i]);
  }
  
}

/* double the edges */
void doubleEdge(vector< vector<int> > &adjlist) {
  int s;
  for(int i=0;i<adjlist.size();i++){
  	s=(int) adjlist[i].size();
  	for(int j=0;j<s;j++){
  		adjlist[i].push_back(adjlist[i][j]);
  	}
  }
}

void Karp(int n, double (*points)[2], int* tour){
	if(n==3){
        tour[0]=0;
        tour[1]=1;
        tour[2]=2;
        return;
    }
	
	deque< box > boxes(1);
	deque< box > finalboxes;
	
	//Find biggest box
	double xmax=-100000,xmin=100000,ymax=-100000,ymin=100000;
	for(int i=0;i<n;i++){
		xmax=max(xmax,points[i][0]);
		xmin=min(xmin,points[i][0]);
		ymax=max(ymax,points[i][1]);
		ymin=min(ymin,points[i][1]);
		boxes[0].points.push_back(i);
	}
	boxes[0].xmax=xmax;
	boxes[0].xmin=xmin;
	boxes[0].ymax=ymax;
	boxes[0].ymin=ymin;
	
	int target_size=(int) log2(n);
	
	//Stream the boxes, split and preserve if necessary, else store
	while(boxes.size()>0){
		if(boxes[0].points.size()<=target_size){
			finalboxes.push_back(boxes[0]);
			boxes.pop_front();
		}else{
			box box1,box2;
			box1.xmin=100000;
			box1.xmax=-100000;
			box1.ymin=100000;
			box1.ymax=-100000;
			box2.xmin=100000;
			box2.xmax=-100000;
			box2.ymin=100000;
			box2.ymax=-100000;
			double xmean,ymean;
			//Choose how to split
			if(boxes[0].xmax-boxes[0].xmin <= boxes[0].ymax-boxes[0].ymin){
				ymean=(boxes[0].ymax+boxes[0].ymin)/2;
				box1.xmax=boxes[0].xmax;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=boxes[0].xmin;
				
				box1.ymax=ymean;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=ymean;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][1]<=ymean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}else{
				xmean=(boxes[0].xmax+boxes[0].xmin)/2;
				box1.xmax=xmean;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=xmean;
				
				box1.ymax=boxes[0].ymax;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=boxes[0].ymin;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][0]<=xmean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}
			
			if(box1.points.size()>0) boxes.push_back(box1);
			if(box2.points.size()>0) boxes.push_back(box2);
			boxes.pop_front();
		}
	}
	
	//Run DP on all boxes
	/*
	for(int i=0;i<finalboxes.size();i++){
		DP(points,finalboxes[i]);
	}
	*/
	
	//Fake enabled
	for(int i=0;i<finalboxes.size();i++){
		for(int j=0;j<finalboxes[i].points.size();j++){
			finalboxes[i].tour.push_back(finalboxes[i].points[j]);
		}
	}
	
	//Find tour between first points of all boxes
	double firstpoints[(int) finalboxes.size()][2];
	int firsttour[(int) finalboxes.size()];
	for(int i=0;i<finalboxes.size();i++){
		firstpoints[i][0]=points[finalboxes[i].tour[0]][0];
		firstpoints[i][1]=points[finalboxes[i].tour[0]][1];
	}
	
	Christophides((int) finalboxes.size(),firstpoints,firsttour);
	
	//Merge tours
	int totalcount=0;
	for(int i=0;i<finalboxes.size();i++){
		for(int j=0;j<finalboxes[firsttour[i]].tour.size();j++){
			tour[totalcount]=finalboxes[firsttour[i]].tour[j];
			totalcount++;
		}
	}
}


void APKarp(int n, double (*points)[2], int* tour){
	if(n==3){
        tour[0]=0;
        tour[1]=1;
        tour[2]=2;
        return;
    }
	
	deque< box > boxes(1);
	deque< box > finalboxes;
	
	//Find biggest box
	double xmax=-100000,xmin=100000,ymax=-100000,ymin=100000;
	for(int i=0;i<n;i++){
		xmax=max(xmax,points[i][0]);
		xmin=min(xmin,points[i][0]);
		ymax=max(ymax,points[i][1]);
		ymin=min(ymin,points[i][1]);
		boxes[0].points.push_back(i);
	}
	boxes[0].xmax=xmax;
	boxes[0].xmin=xmin;
	boxes[0].ymax=ymax;
	boxes[0].ymin=ymin;
	
	int target_size=(int) log2(n);
	int coin;
	
	//Stream the boxes, split and preserve if necessary, else store
	while(boxes.size()>0){
		if(boxes[0].points.size()<=target_size){
			finalboxes.push_back(boxes[0]);
			boxes.pop_front();
		}else{
			box box1,box2;
			box1.xmin=100000;
			box1.xmax=-100000;
			box1.ymin=100000;
			box1.ymax=-100000;
			box2.xmin=100000;
			box2.xmax=-100000;
			box2.ymin=100000;
			box2.ymax=-100000;
			double xmean,ymean;
			//Choose how to split
			coin=rand()%2;
			if(boxes[0].xmax-boxes[0].xmin <= boxes[0].ymax-boxes[0].ymin){
				ymean=(boxes[0].ymax+boxes[0].ymin)/2;
				box1.xmax=boxes[0].xmax;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=boxes[0].xmin;
				
				box1.ymax=ymean;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=ymean;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][1]<=ymean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}else{
				xmean=(boxes[0].xmax+boxes[0].xmin)/2;
				box1.xmax=xmean;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=xmean;
				
				box1.ymax=boxes[0].ymax;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=boxes[0].ymin;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][0]<=xmean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}
			
			if(box1.points.size()>0) boxes.push_back(box1);
			if(box2.points.size()>0) boxes.push_back(box2);
			boxes.pop_front();
		}
	}
	
	//Run DP on all boxes
	
	//Fake
	/*
	for(int i=0;i<finalboxes.size();i++){
		for(int j=0;j<finalboxes[i].points.size();j++){
			finalboxes[i].tour.push_back(finalboxes[i].points[j]);
		}
	}
	*/
	
	//Fake with Christophides
	
	for(int i=0;i<finalboxes.size();i++){
		
		int tour2[finalboxes[i].points.size()];
		double points2[finalboxes[i].points.size()][2];
		
		for(int i2=0;i2<finalboxes[i].points.size();i2++){
			points2[i2][0]=points[finalboxes[i2].points[0]][0];
			points2[i2][1]=points[finalboxes[i2].points[0]][1];
		}
		Christophides((int) finalboxes[i].points.size(), points2,tour2);
		//RandomOPT3((int) finalboxes[i].points.size(), points2,tour2);
		for(int j=0;j<finalboxes[i].points.size();j++){
			finalboxes[i].tour.push_back(finalboxes[i].points[tour2[j]]);
		}
	}
	
	
	//Find tour between first points of all boxes
	double firstpoints[(int) finalboxes.size()][2];
	int firsttour[(int) finalboxes.size()];
	for(int i=0;i<finalboxes.size();i++){
		firstpoints[i][0]=points[finalboxes[i].tour[0]][0];
		firstpoints[i][1]=points[finalboxes[i].tour[0]][1];
	}
	
	Christophides((int) finalboxes.size(),firstpoints,firsttour);
	
	//Merge tours
	int totalcount=0;
	for(int i=0;i<finalboxes.size();i++){
		for(int j=0;j<finalboxes[firsttour[i]].tour.size();j++){
			tour[totalcount]=finalboxes[firsttour[i]].tour[j];
			totalcount++;
		}
	}
}


void OPTKarp(int n, double (*points)[2], int* tour){
	if(n==3){
        tour[0]=0;
        tour[1]=1;
        tour[2]=2;
        return;
    }
	
	deque< box > boxes(1);
	deque< box > finalboxes;
	
	//Find biggest box
	double xmax=-100000,xmin=100000,ymax=-100000,ymin=100000;
	for(int i=0;i<n;i++){
		xmax=max(xmax,points[i][0]);
		xmin=min(xmin,points[i][0]);
		ymax=max(ymax,points[i][1]);
		ymin=min(ymin,points[i][1]);
		boxes[0].points.push_back(i);
	}
	boxes[0].xmax=xmax;
	boxes[0].xmin=xmin;
	boxes[0].ymax=ymax;
	boxes[0].ymin=ymin;
	
	int target_size=(int) log2(n);
	
	//Stream the boxes, split and preserve if necessary, else store
	while(boxes.size()>0){
		if(boxes[0].points.size()<=target_size){
			finalboxes.push_back(boxes[0]);
			boxes.pop_front();
		}else{
			box box1,box2;
			box1.xmin=100000;
			box1.xmax=-100000;
			box1.ymin=100000;
			box1.ymax=-100000;
			box2.xmin=100000;
			box2.xmax=-100000;
			box2.ymin=100000;
			box2.ymax=-100000;
			double xmean,ymean;
			//Choose how to split
			if(boxes[0].xmax-boxes[0].xmin <= boxes[0].ymax-boxes[0].ymin){
				ymean=(boxes[0].ymax+boxes[0].ymin)/2;
				box1.xmax=boxes[0].xmax;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=boxes[0].xmin;
				
				box1.ymax=ymean;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=ymean;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][1]<=ymean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}else{
				xmean=(boxes[0].xmax+boxes[0].xmin)/2;
				box1.xmax=xmean;
				box1.xmin=boxes[0].xmin;
				
				box2.xmax=boxes[0].xmax;
				box2.xmin=xmean;
				
				box1.ymax=boxes[0].ymax;
				box1.ymin=boxes[0].ymin;
				
				box2.ymax=boxes[0].ymax;
				box2.ymin=boxes[0].ymin;
				for(int i=0;i<boxes[0].points.size();i++){
					if(points[boxes[0].points[i]][0]<=xmean){
						box1.points.push_back(boxes[0].points[i]);
						box1.xmax=max(box1.xmax,points[boxes[0].points[i]][0]);
						box1.xmin=min(box1.xmin,points[boxes[0].points[i]][0]);
						box1.ymax=max(box1.ymax,points[boxes[0].points[i]][1]);
						box1.ymin=min(box1.ymin,points[boxes[0].points[i]][1]);
					}else{
						box2.points.push_back(boxes[0].points[i]);
						box2.xmax=max(box2.xmax,points[boxes[0].points[i]][0]);
						box2.xmin=min(box2.xmin,points[boxes[0].points[i]][0]);
						box2.ymax=max(box2.ymax,points[boxes[0].points[i]][1]);
						box2.ymin=min(box2.ymin,points[boxes[0].points[i]][1]);
					}
				}
			}
			
			if(box1.points.size()>0) boxes.push_back(box1);
			if(box2.points.size()>0) boxes.push_back(box2);
			boxes.pop_front();
		}
	}
	//Run DP on all boxes
	
	//Fake with Random3OPT
	for(int i=0;i<finalboxes.size();i++){
		
		int tour2[finalboxes[i].points.size()];
		double points2[finalboxes[i].points.size()][2];
		
		for(int i2=0;i2<finalboxes[i].points.size();i2++){
			points2[i2][0]=points[finalboxes[i2].points[0]][0];
			points2[i2][1]=points[finalboxes[i2].points[0]][1];
		}
		RandomOPT3((int) finalboxes[i].points.size(), points2,tour2);
		for(int j=0;j<finalboxes[i].points.size();j++){
			finalboxes[i].tour.push_back(finalboxes[i].points[tour2[j]]);
		}
	}
	
	//Find tour between first points of all boxes
	double firstpoints[(int) finalboxes.size()][2];
	int firsttour[(int) finalboxes.size()];
	for(int i=0;i<finalboxes.size();i++){
		firstpoints[i][0]=points[finalboxes[i].tour[0]][0];
		firstpoints[i][1]=points[finalboxes[i].tour[0]][1];
	}
	
	Greedy((int) finalboxes.size(),firstpoints,firsttour);
	
	//Merge tours
	int totalcount=0;
	for(int i=0;i<finalboxes.size();i++){
		for(int j=0;j<finalboxes[firsttour[i]].tour.size();j++){
			tour[totalcount]=finalboxes[firsttour[i]].tour[j];
			totalcount++;
		}
	}
}

int numbits(int i){
	int count=0;
	do{
		count+=(i%2);
		i/=2;
	}while(i>0);
	return count;
}

/* Dynamic programming step for Karp's algorithm */

void DP(double (*points)[2], box &subbox) {
  // Get starting city
  int x = subbox.points[0];
  
  int n = subbox.points.size();
  
  printf("\nN=%d\n",n);
  
  int numsets = (int)pow(2,n);
  
  subbox.cost = vector< vector<double> >(n, vector<double>(numsets,-1.0));
  subbox.prev = vector< vector<int> >(n, vector<int>(numsets,-1));

  // initialize cost table
  
  int subset;
  
  for(int k = 1; k < n; k++) {
    subset = (1 << k);
    subbox.cost[k][subset] = pathCost(subset, k, subbox, points);
    //printf("\nK=%d subset=%d COST=%lf\n",k,subset,subbox.cost[k][subset]);
  }
  
  // compute the dynamic table
  
  vector< vector<int> > sets(10);
  
  for(int i=0;i<pow(2,n);i++){
  	sets[numbits(i)].push_back(i);
  }
  
  for(int s = 2; s < n; s++) { // size of the subsets
    int bitmask = 0;
    int S = (int) pow(2,s);
    
    for(int j = 0; j < sets[s].size(); j++){ // all subsets of size s
      subset=sets[s][j];
      for(int i = 1; i < n; i++) { // all the elements in the subset
      	printf("\nI=%d\n",i);
        if(((1 << i) & subset) != 0) { //element belongs to subset
          printf("\n HELLO %d %d %lf\n",s,i,cost);
          double cost = pathCost(subset, i, subbox, points);
        }
      }
    }  
  }
  
  /*
  for(int i=0;i<subbox.cost.size();i++){
  	for(int j=0;j<subbox.cost[i].size();j++){
  		printf("%d %d\n", );
  	}
  	printf("\n");
  }
  */

 // compute the optimal tour for all cities
 subbox.tour.push_back(x);
 
 vector<int> revtour;
 
 int start=pow(2,n)-1-1;
 int currp=1;
 
 while(start!=0){
 	if(start==1){
 		break;
 	}
 	currp=subbox.prev[currp][start];
 	revtour.push_back(subbox.points[currp]);
 	printf("\n%d %d\n",start,currp);
 	start=start-(1<<currp);
 }
 
 while(!revtour.empty()){
 	subbox.tour.push_back(revtour.back());
 	revtour.pop_back();
 }
 
}



double pathCost(int subset, int endpoint, box & subbox, double (*points)[2]) {
  int n = (int) subbox.points.size();
  if(subset == (1 << endpoint)) { // set is {1,endpoint}
  	subbox.prev[endpoint][subset]=0;
  	printf("\npathCost %d %d\n",endpoint,subset);
    return dist(subbox.points[0], subbox.points[endpoint], points);
  }
  
  printf("\nHI\n");

  if(subbox.cost[endpoint][subset] != -1.0) {
    return subbox.cost[endpoint][subset]; 
  }
  
  printf("\nHI22\n");
  
  double best = 10000000;
  int bestprev=-1;
  for(int i = 0; i < n; i++) {
    if (i != endpoint && (subset & (1 << i)) == 0)
    	printf("\nSubset = %d Shift = &d\n",subset,i);
    	best = min(best, dist(subbox.points[endpoint], subbox.points[i], points) + pathCost(subset | (1 << i), i, subbox, points));
    	bestprev = i;
    }
  
  subbox.cost[subset][endpoint] = best;
  subbox.prev[subset][endpoint] = bestprev;
  return best;
}


void mstsp(int n, double (*points)[2], int* tour){
	vector< vector<int> > mintree(n);
	MST(n,points,mintree);
	
	int used[n];
	int vnum=0;
	zeroIntArray(n,used);
	
	deque< int > states;
	states.push_back(0);
	
	int curr;
	
	while(vnum<n){
		curr=states.front();
		states.pop_front();
		if(used[curr]==1){
			continue;
		}else{
			for(int i=(int)mintree[curr].size()-1;i>=0;i--){
				states.push_front(mintree[curr][i]);
			}
			tour[vnum]=curr;
			used[curr]=1;
			vnum++;
		}
	}
}












