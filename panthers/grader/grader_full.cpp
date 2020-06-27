#include "panther.h"
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005

namespace input_tree{
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
        return 0;      
    }

    int getQ(){return Q;}

    int query(int a, int b){
        Q++;
        //printf("%d %d %d",Q,a,b);
        pii res = {N,N};
        if(po[a]>po[b])swap(a,b);
        for(a=po[a],b=po[b]+1; a<b; a>>=1,b>>=1){
            if(a&1)res=min(res,st[a++]);
            if(b&1)res=min(res,st[--b]);
        }
        //printf(" %d\n",res.second);
        return res.second;
    }
}

namespace adversarial_spikey{
    static int N,S,Q,gtc[MAXN],wa,spikes,is_spike[MAXN];
    static bitset<1024> gt[MAXN], lt[MAXN];
    static vector<int> ans, res;

    int main(){
        scanf("%d%d%d",&N,&S,&spikes);
        ans.resize(N);

        vector<int> shuffle(N);
        iota(shuffle.begin(), shuffle.end(), 0);
        random_shuffle(shuffle.begin(), shuffle.end());

        
        //make random nodes spikes and assign random parents
        for(int i = 0; i < spikes; ++i){
            int spike = shuffle.back();
            shuffle.pop_back();
            is_spike[spike] = 1;
            ans[spike] = shuffle.back(); 
            shuffle.pop_back();
        }

        fill(gtc, gtc+N+1, -1);

        res = handlers(N,S);

        for(int i = 0; i < N; ++i)if(!is_spike[i]){
            if(~gtc[lt[i].count()])wa = 1;
            gtc[lt[i].count()] = i;
        }

        for(int i = N-spikes; i-->0;)
            ans[gtc[i]] = gtc[i+1];

        printf("Queries: %d\n", Q);
        for(int i = 0; i < N; ++i)printf("%d ",res[i]);
        puts("");
        //for(int i = 0; i < N; ++i)printf("%d ",ans[i]);
        //puts("");
        if(ans != res)wa = 1;
        if(wa)
            puts("WA");
        else
            puts("AC"); 
        return 0;      
    }

    int query_h(int a, int b){
        if(a==b)return a;
        int deltaA=0, deltaB=0, res;
        bitset<1024> ngt, nlt, ngta = gt[a], nltb = lt[b], ngtb = gt[b], nlta = lt[a];
        ngta.set(a);
        nltb.set(b);
        ngtb.set(b);
        nlta.set(a);

        for(int i = 0; i < N; ++i)if(ngta[i]){
            nlt = nltb | lt[i];
            deltaA += nlt.count() - lt[i].count();
        }

        for(int i = 0; i < N; ++i)if(ngtb[i]){
            nlt = nlta | lt[i];
            deltaB += nlt.count() - lt[i].count();
        }

        if(deltaA < deltaB || (deltaA == deltaB && rand() & 1)){
            nlt = nltb;
            ngt = ngta;
            res = a;
        }else{
            nlt = nlta;
            ngt = ngtb;
            res = b;
        }

        for(int i = 0; i < N; ++i)if(ngt[i])
            lt[i] |= nlt;

        for(int i = 0; i < N; ++i)if(nlt[i])
            gt[i] |= ngt;

        //printf("%d %d %d\n",a,b,res);
        return res;
    }

    int query(int a, int b){
        Q++;
        if(a==b)return a;
        return query_h(is_spike[a]?ans[a]:a,is_spike[b]?ans[b]:b);    
    }
}


//grader switcher

enum GRADER{
    INPUT_TREE,
    ADVERSARIAL_SPIKEY
};

static GRADER g;

int main(){
    scanf("%d",&g);

    switch (g){
        case INPUT_TREE:
            input_tree::main();
            break;
        case ADVERSARIAL_SPIKEY:
            adversarial_spikey::main();
            break;
    }      
}

int query(int a, int b){
    switch (g){
        case INPUT_TREE:
            return input_tree::query(a,b);
        case ADVERSARIAL_SPIKEY:
            return adversarial_spikey::query(a,b);
    }
    return a;
}