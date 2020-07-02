#include <bits/stdc++.h>
#define int long long

using namespace std;

#define MXN 30001
#define MXM 100001

int n,m,ans,val[MXN],d[MXM],cache[3001][1001];
vector<int> edges[MXN];

int dp(int u, int d){
    if(d<1)return 0;
    if(!cache[u][d]){
        for(int v: edges[u])
            cache[u][d] = max(cache[u][d], dp(v,d-1));
        cache[u][d]+=val[u];
    }
    return cache[u][d];
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i = 1; i <= n; ++i)
        cin>>val[i];

    for(int i = 1; i <= m; ++i)
        cin>>d[i];

    for(int i = 2,a; i <= n; ++i){
        cin>>a;
        edges[i].push_back(a);
        edges[a].push_back(i);
    }
    
    for(int i = 1; i <= m; ++i)
        ans += dp(1, d[i]);
    cout<<ans;
}
