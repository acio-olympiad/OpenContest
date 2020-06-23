#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 100005
#define LL long long
using namespace std;
struct line {LL m,c;};
class CHT {
    vector <line> S;
    int pt = 0;
public:
    bool bad(line L) {
        line L2 = S[S.size() - 2], L1 = S[S.size() - 1];
        if (L1.m == L.m) {return(L.c >= L1.c);}
        return((L2.c - L1.c)*(L.m - L2.m) >= (L1.m - L2.m)*(L2.c - L.c));
    }
    LL eval(LL x, line L) {
        return(L.m * x + L.c);
    }
    void put(line New) {
        while (S.size() > 1 && bad(New)) {S.pop_back();}
        S.push_back(New);
    }
    LL ask(LL x) {
        while (pt < S.size()-1 && eval(x, S[pt+1]) > eval(x, S[pt])) {pt++;}
        return(eval(x, S[pt]));
    }
} Q[2]; //even, odd

int N, M, V[MAXN], D[MAXN], P[MAXN];
LL Dist[MAXN], Grad[MAXN], Val[MAXN], PathMax[MAXN]; //path max gradient
LL Ans;
vector <int> adj[MAXN];
vector <line> Lines[2]; //even, odd

void dfs(int u) {
    Grad[u] = V[P[u]];
    for (int v: adj[u]) {
        Grad[u] = max(Grad[u], (LL) V[v]);
        Dist[v] = Dist[u] + 1;
        Val[v] = Val[u] + V[u];
        PathMax[v] = max(PathMax[u], (LL) V[u] + V[v]);
        dfs(v);
    }
    Grad[u] += V[u];
    if (PathMax[u] <= Grad[u]) {
        Lines[Dist[u]%2].push_back(line {Grad[u], -Grad[u] * ((Dist[u]+1)/2) + Val[u]});
    }
}

int main() {
    freopen("vibein.txt","r",stdin);
    scanf("%d %d",&N,&M);
    for (int i=1; i<=N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i=1; i<=M; i++) {
        scanf("%d", &D[i]);
    }
    for (int i=2; i<=N; i++) {
        scanf("%d", &P[i]);
        adj[P[i]].push_back(i);
    }

    dfs(1);
    sort(D+1, D+M+1);
    sort(Lines[0].begin(), Lines[0].end(), [](line a, line b) {return(a.m < b.m);});
    sort(Lines[1].begin(), Lines[1].end(), [](line a, line b) {return(a.m < b.m);});
    for (int i=0; i<=1; i++) {
        for (auto l: Lines[i]) {
            //printf("%d %lld %lld\n",i,l.m,l.c);
            Q[i].put(l);
        }
    }

    for (int i=1; i<=M; i++) {
        if (D[i] == 1) {Ans += V[1];}
        else {
            Ans += Q[D[i]%2].ask((D[i]+1)/2);
            //printf("%d %lld\n",D[i], Q[D[i]%2].ask((D[i]+1)/2));
        }
    }

    printf("%lld", Ans);
}
