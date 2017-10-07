#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<cstdio>

using namespace std;

bool comp(int a, int b){
    return a<b;
}

int main(){

    vector<int> vec;
    for(int i=0;i<10;i++){
        vec.push_back(10-i);
    }

    for(int i=0;i<10;i++){
        printf("%d ",vec[i]);
    }
    printf("\n");

    sort(vec.begin(), vec.end(), comp);

    for(int i=0;i<10;i++){
        printf("%d ",vec[i]);
    }
    printf("\n");


    map<int,char> m;
    m.insert(pair<int,char>(2,'f'));
    m.insert(pair<int,char>(5,'m'));

    for(map<int,char>::iterator it = m.begin(); it!= m.end(); it++){
        printf("%d %c\n",it->first, it->second);
    }


    return 0;
}