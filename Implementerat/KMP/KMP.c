
//Fills in prefix table T for search word W
void KMP_table(int *W, int *T, int Wlen){
	int pos=2, cnd=0;
	T[0]=-1;
	T[1]=0;
	
	while(pos<Wlen){
		if(W[pos-1]==W[cnd]){
			cnd+=1;
			T[pos]=cnd;
			pos+=1;
		}else if(cnd>0){
			cnd=T[cnd];
		}else{
			T[pos]=0;
			pos+=1;
		}
	}
}

//Search for W in S, last two parameters are lengths of W,S
int KMP_search(int *W, int *S,int Wlen, int Slen){
	int T[Wlen]; //This will be the prefix table, make it for W!
	int m=0,i=0;
	
	//Maybe this loop is redundant...but I don't care...
	for(int j=0;j<Wlen;j+=1){
		T[j]=0;
	}
	
	KMP_table(W,T,Wlen); //Fill in T
	
	while(m+i<Slen){ //Main loop of KMP
		if(W[i]==S[m+i]){
			if(i==Wlen-1){
				return(m);
			}
			i+=1;
		}else{
			if(T[i]>-1){
				m=m+i-T[i];
				i=T[i];
			}else{
				i=0;
				m+=1;
			}
		}
	}
	return(Slen); //Failure
}
