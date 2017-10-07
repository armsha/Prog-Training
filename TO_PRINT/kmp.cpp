#include<cstdio>
#include<string>

using namespace std;

int T[100];

void build_table(string W){
    int pos=1;
    int cnd=0;
    T[0]=-1;

    while(pos<W.length()){
        if(W[pos]==W[cnd]){
            T[pos]=T[cnd];
            pos++;
            cnd++;
        }else{
            T[pos]=cnd;
            cnd=T[cnd];
            while(cnd>=0 && W[pos] != W[cnd]){
                cnd=T[cnd];
            }
            pos++;
            cnd++;
        }
    }

    T[pos] = cnd;
}

int kmp(string S, string W){
    int m=0, i=0;

    while(m+i<S.length()){
        if(W[i]==S[m+i]){
            i++;
            if(i==W.length()){
                return m;
                //m = m+i-T[i];
                //i=T[i];
            }
        }else{
            if(T[i]>-1){
                m=m+i-T[i];
                i=T[i];
            }else{
                m=m+i+1;
                i=0;
            }
        }
    }
    return -1;
}

int main(){
    string S = "aaabbaabbaba";
    string W = "aabbaba";

    build_table(W);

    int ans = kmp(S,W);

    printf("%d\n", ans);

    return 0;
}