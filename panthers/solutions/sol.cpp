#include "panther.h"
#include <iostream>
#include <vector>
#define MAXN 1005
using namespace std;

int N, P[MAXN], Sz[MAXN], rt; //compressed tree
bool inTree[MAXN], blocked[MAXN];
vector <int> adj[MAXN], Cand;

void getRoot() {
    for (int i=0; i<N; i++) {
        rt = query(rt, i);
    }
}

void reset() {
    for (int i=0; i<N; i++) {
        adj[i].clear();
        blocked[i] = false;
    }
    for (int i=0; i<N; i++) {
        if (i != rt && inTree[i]) {adj[P[i]].push_back(i);}
    }
}

void dfs(int u) {
    Sz[u] = 0;
    if (blocked[u]) {return;}
    Sz[u] = 1;
    Cand.push_back(u);
    for (int v: adj[u]) {
        dfs(v);
        Sz[u] += Sz[v];
    }
}

int FindPar(int v, int subtree) {
    Cand.clear();
    dfs(subtree);
    if (Cand.size() == 1) {
        return(Cand[0]);
    }
    int bestsplit = 1<<30, opt = -1;
    for (int v: Cand) {
        if (max(Sz[v], Sz[subtree] - Sz[v]) < bestsplit) {
            opt = v;
            bestsplit = max(Sz[v], Sz[subtree] - Sz[v]);
        }
    }
    int res = query(v, opt);
    if (res == opt) {
        return(FindPar(v, opt));
    } else {
        blocked[opt] = true;
        return(FindPar(v, subtree));
    }
}

vector<int> handlers(int n, int s){
    N= n;
    getRoot();
    P[rt] = -1, inTree[rt] = 1;
    for (int i=0; i<N; i++) {
        if (inTree[i]) {continue;}
        reset();
        int p = FindPar(i, rt);
        P[i] = p;
        for (int v: adj[p]) {
            int res = query(v, i);
            if (res == i) { //a is par of prexisting child
                P[v] = i;
                break;
            } else if (res != p) { //add lca if needed
                P[v] = P[i] = res;
                P[res] = p;
                inTree[res] = true;
                break;
            }
        }
        inTree[i] = true;
    }
    vector <int> res(N);
    for (int i=0; i<N; i++) {
        res[i] = P[i];
    }
    return(res);
}

/*
vector<int> handlers(int N, int S){
    vector<int> res(N);

    // Implement your solution here

    query(0,1);
    query(3,4);
    query(4,2);

    res = {-1,0,0,1,1};

    return res;
} */
