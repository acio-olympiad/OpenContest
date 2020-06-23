#include <bits/stdc++.h>

using namespace std;

#define MXN 100001
#define MXM 100001

typedef long long ll;
typedef pair<ll, ll> pll;

ll N,M,ans,val[MXN],d[MXM],m[MXN],c[MXN],pe,po;
vector<int> child[MXN];
vector<pll> oddp, evenp, oddc, evenc;

void dfs(int u, int dep, ll vib, ll bavg){
    if(child[u].size()){
        ll b = 0;
        for(int v: child[u])
            b = max(b,val[v]);

        for(int v: child[u])
            dfs(v,dep+1,vib+2*val[u],max(b+val[u],bavg));

        if(b+val[u] >= bavg){
            if(dep&1){
                oddp.push_back({b+val[u],vib-(b+val[u])*dep+2*val[u]});
                evenp.push_back({b+val[u],vib-(b+val[u])*(dep-1)});
            }
            else{
                evenp.push_back({b+val[u],vib-(b+val[u])*dep+2*val[u]});
                oddp.push_back({b+val[u],vib-(b+val[u])*(dep-1)});
            }
        }        
    }
}

ll eval(pll p, int x){return p.first*x+p.second;}
ll sect(pll a, pll b){return (a.second-b.second)/(b.first-a.first);}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //ifstream cin ("cases/sample.in");
    cin>>N>>M;
    for(int i = 1; i <= N; ++i)
        cin>>val[i];

    for(int i = 0; i < M; ++i)
        cin>>d[i];

    for(int i = 2,a; i <= N; ++i){
        cin>>a;
        child[a].push_back(i);
    }
    
    //printf("here\n");
    dfs(1,1,0,0);

    sort(oddp.begin(),oddp.end());
    sort(evenp.begin(),evenp.end());
    sort(d,d+M);

    //printf("here\n");

    for(pll p: oddp){
        while((oddc.size() && oddc.back().first == p.first) || (oddc.size() > 1 && sect(oddc.back(), p) <= sect(oddc.back(), oddc[oddc.size()-2])))
            oddc.pop_back();
        oddc.push_back(p);
    }

    for(pll p: evenp){
        while((evenc.size() && evenc.back().first == p.first) || (evenc.size() > 1 && sect(evenc.back(), p) <= sect(evenc.back(), evenc[evenc.size()-2])))
            evenc.pop_back();
        evenc.push_back(p);
    }
    
    for(int i = 0; i < M; ++i){
        if(d[i]&1){
            while(po < oddc.size()-1 && eval(oddc[po], d[i]) < eval(oddc[po+1], d[i]))po++;
            ans+=eval(oddc[po], d[i])/2;
        }else{
            while(pe < evenc.size()-1 && eval(evenc[pe], d[i]) < eval(evenc[pe+1], d[i]))pe++;
            ans+=eval(evenc[pe], d[i])/2;
        }
    }
    cout<<ans;
}