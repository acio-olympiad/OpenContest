#include "panther.h"
using namespace std;

#include <queue>
#include <cstdio>
#include <algorithm>

#define MAXN 1005
vector<int> P, childs[MAXN];
int sz[MAXN];

int dfs(int u){
    int res = 1;
    for(int v:childs[u])res+=dfs(v);
    return res;
}


int merge_tree(int a, int b, int qu = -1){
    if(qu == -1)qu = query(a,b);
    if(qu==b)swap(a,b);
    int nq;
    if(qu==a){
        P[b]=a;
        if(childs[a].size()){
            nq = query(b,childs[a][0]);
            if(nq==a){ //must be in childs[a][1] subtree
                if(childs[a].size()==2)
                    childs[a][1] = merge_tree(b,childs[a][1]);                 
                else 
                    childs[a].push_back(b);
            }else
                childs[a][0] = merge_tree(b,childs[a][0],nq);
        }else
            childs[a].push_back(b);
        for(;;){
            auto p = find(childs[a].begin(), childs[a].end(), -1);
            if(p != childs[a].end())childs[a].erase(p);
            else break;
        }
        return a;
    }else{
        // a and b must be in separate subtrees of p, which is actually in a seperate subtree
        // this can be exploited to cause O(bad) behaviour, as you can't guranatee that a small tree won't be merged with a large tree
        P[a]=qu;
        P[b]=qu;
        if(childs[qu].size()){
            nq = query(a,childs[qu][0]);
            if(nq == qu)swap(a,b);
            childs[qu][0] = merge_tree(childs[qu][0],a,nq!=qu?nq:-1);
            if(childs[qu].size()==2)
                childs[qu][1] = merge_tree(childs[qu][1],b);
            else
                childs[qu].push_back(b);         
        }else{
            childs[qu].push_back(a);
            childs[qu].push_back(b);
        }
        for(;;){
            auto p = find(childs[qu].begin(), childs[qu].end(), -1);
            if(p != childs[qu].end())childs[qu].erase(p);
            else break;
        }
        return -1; //indicate thes trees have been merged into some other tree
    }    
}

vector<int> handlers(int N, int S){
    P.assign(N,-1);
    vector<int> rts;
    for(int i = 0; i < N; ++i)
        rts.push_back(i);

    while(rts.size()>1){
        for(int r:rts){sz[r]=dfs(r);}

        //random_shuffle(rts.begin(), rts.end());

        sort(rts.begin(), rts.end(), [&](int a, int b){return sz[a]>sz[b];});
        
        int a,b,c;
        a=rts.back();
        rts.pop_back();
        b=rts.back();
        rts.pop_back();
        c = merge_tree(a,b,-1);
        if(c==a || c==b)rts.push_back(c);
    }

    return P;
}