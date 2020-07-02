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

namespace adversarial_input_tree {
	int N, S, end_state, qcnt;
	int par[1005], ind[1005], sz[1005], c1[1005], c2[1005], fp[1005];
	int taken[1005], cur[1005], stuck[1005];
	int root, cnt;
	void dfs(int x) {
		ind[x] = cnt++;
		sz[x] = 1;
		if (c1[x] != -1) {
			dfs(c1[x]);
			sz[x] += sz[c1[x]];
		}
		if (c2[x] != -1) {
			dfs(c2[x]);
			sz[x] += sz[c2[x]];
		}
	}
	void main() {
		scanf("%d %d", &N, &S);
		for (int i = 0; i < N; i++) c1[i] = c2[i] = -1;
		for (int i = 0; i < N; i++) {
			scanf("%d", par+i);
			if (par[i] != -1) {
				if (c1[par[i]] == -1) c1[par[i]] = i;
				else c2[par[i]] = i;
			} else {
				root = i;
			}
		}
		dfs(root);
		taken[0] = N;
		for (int i = 0; i < N; i++) cur[i] = root;
		vector<int> output = handlers(N, S);
		if (!end_state) {
			printf("WA: End state not achieved.\n");
		} else {
			vector<int> expected;
			for (int i = 0; i < N; i++) {
				fp[i] = -1;
			}
			for (int i = 0; i < N; i++) {
				assert(fp[cur[i]] == -1);
				fp[cur[i]] = i;
			}
			for (int i = 0; i < N; i++) {
				if (par[cur[i]] == -1) expected.push_back(-1);
				else expected.push_back(fp[par[cur[i]]]);
			}
			if (expected != output) {
				printf("WA: Incorrect output\n");
			} else {
				printf("AC\n");
			}
		}
		printf("%d queries\n", qcnt);
		printf("Result:");
		for (int x : output) printf(" %d", x);
		printf("\n");
	}
	int isanc(int a, int b) {
		return ind[a] <= ind[b] && ind[a] + sz[a] > ind[b];
	}
	int lca(int u, int v) {
		// haha linear time lca go brrr
		int res = u;
		if (isanc(u, v)) return u;
		if (isanc(v, u)) return v;
		while (!isanc(res, v)) {
			res = par[res];
		}
		assert(res != -1);
		return res;
	}
	// Reassign attempts to split u and v up so they are not ancestors of each other
	int reassign(int x, int &u, int &v) {
		printf("reassign(%d)\n", x);
		int l = sz[c1[x]] - taken[c1[x]];
		int r = sz[c2[x]] - taken[c2[x]];
		// Case 1: Perfect split
		if (l > 0 && r > 0) {
			u = c1[x];
			v = c2[x];
			taken[c1[x]]++;
			taken[c2[x]]++;
			return 1;
		}
		// Case 2: Defer split to subtrees
		if (l > 1) {
			taken[c1[x]] += 2;
			return reassign(c1[x], u, v);
		}
		if (r > 1) {
			taken[c2[x]] += 2;
			return reassign(c2[x], u, v);
		}
		// Case 3: Make one parent of other
		if (l > 0) {
			taken[c1[x]]++;
			u = c1[x];
			return 1;
		}
		if (r > 0) {
			taken[c2[x]]++;
			u = c2[x];
			return 1;
		}
		// Case 4: This should never happen under any cirumstance
		return 0;
	}
	void check_end_state() {
		for (int i = 0; i < N; i++) {
			assert(taken[i] <= sz[i]);
			if (taken[i] < sz[i]) return;
		}
		end_state = 1;
		printf("End state achieved!\n"); // TODO: REMOVE
	}
	void dump_state() {
		for (int i = 0; i < N; i++) {
			printf("Node %d: (%d/%d)\n", i, taken[i], sz[i]);
		}
		for (int i = 0; i < N; i++) {
			printf("cur[%d]: %d\n", i, cur[i]);
		}
	}
	int query(int a, int b) {
		printf("query(%d, %d)\n", a, b);
		qcnt++;
		if (isanc(cur[b], cur[a])) {
			swap(a, b);
		}
		if (isanc(cur[a], cur[b])) {
			if (cur[a] == cur[b]) {
				// We can only split
				int thisshouldbetrue = reassign(cur[a], cur[a], cur[b]);
				assert(thisshouldbetrue);
			} else {
				int res = cur[a];
				while (isanc(res, cur[b]) && res != cur[b]) {
					int opt1 = c1[res], opt2 = c2[res];
					if (isanc(c1[res], cur[b])) {
						swap(opt1, opt2);
					}
					// Try move to opt1
					if (taken[opt1] < sz[opt1]) {
						// Move successful
						res = opt1;
						taken[opt1]++;
					} else if (taken[opt2] < sz[opt2]) {
						res = opt2;
						taken[opt2]++;
					} else {
						// rip i guess we're trapped, no use moving
						printf("Trapped at res=%d\n", res);
						break;
					}
				}
				// If we can't keep b where it is, then we have to move over
				if (res == cur[b]) {
					int thisshouldbetrue = reassign(cur[b], res, cur[b]);
					assert(thisshouldbetrue);
				}
				cur[a] = res;
			}
		}
		int l = lca(cur[a], cur[b]);
		printf("Returning %d\n", l);
		dump_state();
		check_end_state();
		return l;
	}
}


//grader switcher

enum GRADER{
    INPUT_TREE,
    ADVERSARIAL_SPIKEY,
	ADVERSARIAL_INPUT_TREE
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
		case ADVERSARIAL_INPUT_TREE:
			adversarial_input_tree::main();
			break;
    }      
}

int query(int a, int b){
    switch (g){
        case INPUT_TREE:
            return input_tree::query(a,b);
        case ADVERSARIAL_SPIKEY:
            return adversarial_spikey::query(a,b);
		case ADVERSARIAL_INPUT_TREE:
			return adversarial_input_tree::query(a,b);
    }
    return a;
}
