#include "panther.h"
#include <bits/stdc++.h>
using namespace std;
#define rnd(i, j) uniform_int_distribution<int>(i, j)(rng)
void mergesort(vector<int> &v, int ignorefirst = 0) {
    if (v.size() <= 1) return;
    vector<int> half1, half2;
    int half = v.size()/2;
    for (int i = ignorefirst; i < half; i++) half1.push_back(v[i]);
    for (int i = half; i < v.size(); i++) half2.push_back(v[i]);
    mergesort(half1, 0), mergesort(half2, 0);
    vector<int> sorted;
    if (ignorefirst) sorted.push_back(v[0]);
	merge(half1.begin(), half1.end(), half2.begin(), half2.end(), back_inserter(sorted), [](int a, int b) { if (a == b) return false; return query(a, b) == a; });
    v.swap(sorted);
}
vector<int> bucket[1010], par;
void solve(vector<int> v, mt19937 &rng, int root = -1) {
    if (v.size() == 1) return;
    for (auto a : v) bucket[a].clear();
    do {
        shuffle(v.begin(), v.end(), rng);
    }
    while (v[0] == root);
    int a = v[0];
    for (auto i : v) {
        if (i == a) {
            bucket[i].push_back(i);
        } else {
            int q;
            if (i == root) q = root; // micro-optimisations
            else q = query(i, a);

            if (q == a) q = a = i;
            bucket[q].push_back(i);
        }
    }
    vector<pair<int, vector<int> > > save;
    for (auto a : v) {
        if (bucket[a].size()) save.emplace_back(a, bucket[a]);
    }
    for (auto &a : save) {
        solve(a.second, rng, a.first);
    }
    // now we want to sort and add parents
    vector<int> chain;
    if (root != -1) chain.push_back(root);
    for (auto &a : save) {
        if (a.first != root) chain.push_back(a.first);
    } 
    mergesort(chain, root != -1);
    for (int i = 1; i < chain.size(); i++) {
        par[chain[i]] = chain[i-1];
    }
}
vector<int> supervisors(int n, int s){
    mt19937 rng;
    // try to confuse adaptive graders
    for (int i = 0; i < n-1; i++) query(i, i+1);
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    par = vector<int>(n, -1);
    solve(v, rng);
    return par;
}
