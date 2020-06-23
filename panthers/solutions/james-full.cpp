#include "panther.h"
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

#define MAXN 1005
vector<int> P, childs[MAXN];
int done[MAXN], grt, sz[MAXN], best, bestv;

// get all nodes in segtree of u and add it to st (does not include u)
void get_subtree(int u, vector<int>& st){
    sz[u] = 1;
    for(int v: childs[u]){
        st.push_back(v);
        get_subtree(v, st);
        sz[u] += sz[v];
    }
}

void find_best(int u, multiset<int> &par_st, int dep){
    int sc = max({sz[u], *--par_st.end(), dep});
    if(sc < best){
        best = sc;
        bestv = u;
    }
    if(childs[u].size()==2){
        auto ins = par_st.insert(sz[childs[u][1]]);
        find_best(childs[u][0], par_st, dep+1);
        par_st.erase(ins);
        ins = par_st.insert(sz[childs[u][0]]);
        find_best(childs[u][1], par_st, dep+1);
        par_st.erase(ins);
    }else if(childs[u].size())
        find_best(childs[u][0], par_st, dep+1);
}

// insert node into an ancestor line from t down to b, is above b, less than t (unless inc)
void insert_line(int t, int b, int u, bool inc){ 
    vector<int> line;
    for(int p = b; p!=t; p=P[p])
        if(p!=b)line.push_back(p);

    if(!line.size()){
        if(inc && query(t,u)==u){
            if(P[t]!=-1){
                childs[P[t]].erase(find(childs[P[t]].begin(), childs[P[t]].end(), t));
                childs[P[t]].push_back(u);
            }else grt = u;
            P[u]=P[t];
            childs[u].push_back(t);            
            P[t]=u;
        }else{
            //printf("op2\n");
            childs[t].erase(find(childs[t].begin(), childs[t].end(), b));
            childs[t].push_back(u);
            P[u]=t;
            childs[u].push_back(b);
            P[b]=u;
        }
        done[u]=1;
    }else{
        int v = line[line.size()/2];
        int p = query(u,v);
        if(p==u){
            insert_line(t,v,u,inc);
        }else{
            insert_line(v,b,u,0);
        }
    }
}

// insert node u into subtree of rt (must be less than rt unless inc is set)
void insert_subtree(int rt, int u, bool inc = 0){
    vector<int> subtree;
    get_subtree(rt, subtree);

    if(!subtree.size()){
        if(inc){
            int p = query(rt,u);
            if(p==rt){
                childs[rt].push_back(u);
                P[u]=rt;
            }else if(p==u){
                if(P[rt]!=-1){
                    childs[P[rt]].erase(find(childs[P[rt]].begin(), childs[P[rt]].end(), rt));
                    childs[P[rt]].push_back(u);
                }else grt = u;
                P[u]=P[rt];
                childs[u].push_back(rt);            
                P[rt]=u;
            }else{
                done[p]=1;
                childs[p].push_back(u);
                childs[p].push_back(rt);
                if(P[rt]!=-1){
                    childs[P[rt]].erase(find(childs[P[rt]].begin(), childs[P[rt]].end(), rt));
                    childs[P[rt]].push_back(p);
                }else grt = p;
                P[p]=P[rt];
                P[rt]=p;
                P[u]=p;
            }
        }else{
            childs[rt].push_back(u);
            P[u]=rt;
        }
        done[u]=1;
    }else{
        //find node that minimises size of subtree and size of subtree of any parent
        multiset<int> pst;
        pst.insert(0);
        best = 99999;
        find_best(rt, pst, 0);
        int v = bestv;
        
        int p = query(u,v);
        if(p==v) // u in subtree of v
            insert_subtree(v,u);
        else if(p==u) // u is an ancestor of v 
            insert_line(rt,v,u,inc);
        else if(p == rt || find(subtree.begin(), subtree.end(), p) != subtree.end()){ // u is in or directly above the subtree of p that does not contain v
            if(childs[p].size()<2){
                childs[p].push_back(u);
                P[u]=p;
                done[u]=1;  
            }else{
                int pv = v;
                for(v = P[v]; v!=p; v = P[v])pv=v;
                if(childs[p][0]!=pv)
                    insert_subtree(childs[p][0], u, 1);
                else
                    insert_subtree(childs[p][1], u, 1);
            }
        }else{ // p is ancestor of v and u is child of p
            P[u]=p;
            childs[p].push_back(u);
            done[u]=1;
            insert_line(rt,v,p,inc);
        }
    }
}

vector<int> handlers(int N, int S){
    P.resize(N);
    // Implement your solution here
    
    done[0]=1;
    grt = 0;
    P[0]=-1;
    for(int i = 1; i < N; ++i)
        if(!done[i])
            insert_subtree(grt,i,1);
        
    return P;
}