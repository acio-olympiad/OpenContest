#include "panther.h"
#include <cstdio>

#define MAXN 1005

using namespace std;
typedef pair<int,int> pii;

static int N,S,Q,po[MAXN],rt,cnt,mcnt;
static vector<int> childs[MAXN];
static pii st[MAXN*4];

void dfs(int u, int d){
    po[u]=mcnt+cnt;
    st[mcnt+cnt++] = {d,u};
    for(int v: childs[u]){
        dfs(v, d+1);
        st[mcnt+cnt++] = {d,u};
    }
}

int main(){
    scanf("%d%d",&N,&S);

    vector<int> ans(N), res;
    for(int i = 0; i < N; ++i){
        scanf("%d",&ans[i]);
        if(ans[i]==-1)
            rt = i;
        else
            childs[ans[i]].push_back(i);
    }

    mcnt=2*N-1;
    dfs(rt, 0);   
    for(int i = mcnt; i-->1;)st[i]=min(st[i*2+1],st[i*2]);

    res = handlers(N,S);

    printf("Queries: %d\n", Q);
    for(int i = 0; i < N; ++i)printf("%d ",res[i]);
    puts("");
    if(ans == res)
        puts("AC");
    else
        puts("WA");       
}

int getQ(){return Q;}

int query(int a, int b){
    Q++;
    pii res = {N,N};
    if(po[a]>po[b])swap(a,b);
    for(a=po[a],b=po[b]+1; a<b; a>>=1,b>>=1){
        if(a&1)res=min(res,st[a++]);
        if(b&1)res=min(res,st[--b]);
    }
    return res.second;
}