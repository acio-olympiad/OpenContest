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
        //for(int i = 0; i < N; ++i)printf("%d ",res[i]);
        //puts("");
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
        //for(int i = 0; i < N; ++i)printf("%d ",res[i]);
        //puts("");
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
	vector<int> qa, qb, qr;
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
	void reg(int x, int n) {
		assert(taken[x] < sz[x]);
		taken[x]++;
		cur[n] = x;
		if (fp[x] == -1) {
			fp[x] = n;
			stuck[n] = 1;
		}
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
	void check_end_state() {
		for (int i = 0; i < N; i++) {
			if (taken[i] + 1 < sz[i]) return;
		}
		end_state = 1;
	}
	void dump_state() {
		for (int i = 0; i < N; i++) {
			printf("Node %d: (%d/%d)\n", i, taken[i], sz[i]);
		}
		for (int i = 0; i < N; i++) {
			printf("cur[%d] (stuck %d): %d\n", i, stuck[i], cur[i]);
		}
	}
	void main() {
		srand(34958349);
		scanf("%d %d", &N, &S);
		for (int i = 0; i < N; i++) c1[i] = c2[i] = fp[i] = -1;
		for (int i = 0; i < N; i++) {
			scanf("%d", par+i);
			if (par[i] != -1) {
				if (c1[par[i]] == -1) c1[par[i]] = i;
				else c2[par[i]] = i;
			} else {
				root = i;
			}
		}
		for (int i = 0; i < N; i++) {
			if (c2[i] != -1 && (rand()&1)) {
				swap(c1[i], c2[i]);
			}
		}
		dfs(root);
		assert(sz[root] == N);
		for (int i = 0; i < N; i++) reg(root, i);
		for (int i = 0; i < N; i++) cur[i] = root;

		vector<int> output = handlers(N, S);
		if (output.size() != N) printf("WA: Output size wrong\n");
		check_end_state();
		//dump_state();
		if (!end_state) {
			printf("WA: End state not achieved.\n");
		} else {
			int fine = 1;
			for (int i = 0; i < N; i++) {
				if (stuck[i]) {
					if (par[cur[i]] == -1) {
						fine &= (output[i] == -1);
					} else {
						fine &= (fp[par[cur[i]]] == output[i]);
					}
				} else {
					fine &= isanc(cur[i], cur[output[i]]);
				}
			}
			if (!fine) {
				printf("WA: Incorrect output\n");
			} else {
				printf("AC\n");
			}
		}
		printf("%d queries\n", qcnt);
		//printf("Result:");
		//for (int x : output) printf(" %d", x);
		//printf("\n");
		for (int i = 0; i < qa.size(); i++) {
			int l2 = lca(cur[qa[i]], cur[qb[i]]);
			if (fp[l2] != qr[i]) {
				printf("Query %d inconsistent! lca(%d, %d) = %d, expected %d\n", i+1, qa[i], qb[i], qr[i], fp[l2]);
			} else {
				printf("Query %d consistent. lca(%d, %d) = %d, expected %d\n", i+1, qa[i], qb[i], qr[i], fp[l2]);
			}
		}
	}
	// Either find a splitting subtree, or completely determine the position of one of the nodes
	int query(int a, int b) {
		if (a == b) return a; // smh contestant, sanitise your query inputs
		//printf("query(%d, %d)\n", a, b);
		qcnt++;
		// Code here
		if (isanc(cur[b], cur[a])) swap(a, b);
		// Only problematic case is (WLOG) A is ancestor of B
		if (isanc(cur[a], cur[b])) {
			// Do stuff
			// Case 1: Move a somewhere above b
			while (isanc(cur[a], cur[b]) && cur[a] != cur[b] && !stuck[a]) {
				int opt1 = c1[cur[a]], opt2 = c2[cur[a]];
				assert(opt1 != -1);
				if (isanc(c1[cur[a]], cur[b]) && opt2 != -1) {
					swap(opt1, opt2);
				}
				if (taken[opt1] < sz[opt1]) {
					// Move to non-ancestor child
					reg(opt1, a);
				} else if (opt2 != -1 && taken[opt2] < sz[opt2]) {
					// Move to ancestor child
					reg(opt2, a);
				} else {
					// Wait this case should never happen right?
					assert(false);
				}
			}
			// Case 2: A and B are the same now I guess, so we gotta either make one of them stuck or split em up
			while (!stuck[a] && !stuck[b] && cur[a] == cur[b]) {
				int d1 = 0, d2 = 0;
				assert(c1[cur[a]] != -1);
				if (c1[cur[a]] != -1) d1 = sz[c1[cur[a]]] - taken[c1[cur[a]]];
				if (c2[cur[a]] != -1) d2 = sz[c2[cur[a]]] - taken[c2[cur[a]]];
				if (d1 > 0 && d2 > 0) {
					reg(c1[cur[a]], a);
					reg(c2[cur[b]], b);
				} else if (d1 >= 2) {
					reg(c1[cur[a]], a);
					reg(c1[cur[b]], b);
				} else if (d2 >= 2) {
					reg(c2[cur[a]], a);
					reg(c2[cur[b]], b);
				} else {
					// This should literally never happen :/
					assert(false);
				}
			}
			// If either one is stuck, then we reveal no additional information from LCAing
		}
		// End code
		int l = lca(cur[a], cur[b]);
		//printf("Returning %d\n", fp[l]);
		//dump_state();
		check_end_state();
		qa.push_back(a);
		qb.push_back(b);
		qr.push_back(fp[l]);
		return fp[l];
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
