// n^3 dp thats secretly s^2 (with a log because map)
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int n, s, x[MAXN], y[MAXN], ans;
map<array<int, 4>, int> memo;
vector<int> inrow[MAXN];
unordered_map<int, int> below[MAXN];
int dp(int c, int a, int b, int dir) {
	if (b < a) return 0;
    array<int, 4> stuff = { c, a, b, dir };
	if (memo[stuff]) return memo[stuff]-1;
	if (below[b][c] < b-a+1) {
		// not a range of squares
		return (memo[stuff] = max(dp(c, a+1, b, dir), dp(c, a, b-1, dir))+1)-1;
	}
	if (dir) return (memo[stuff] = dp(c-1, a, b, dir)+b-a+2)-1;
	else return (memo[stuff] = dp(c+1, a, b, dir)+b-a+2)-1;
}
int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < s; i++) {
        scanf("%d%d", &x[i], &y[i]);
        inrow[x[i]].push_back(y[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (auto j : inrow[i]) {
            below[i][j] = below[i-1][j]+1;
        }
    }
    for (int i = 1; i <= n; i++) {
    	for (auto j : inrow[i]) {
            if (below[i][j] == 1) {
                for (int k = i; below[k][j]; k++) {
                    ans = max(ans, dp(j, i, k, 0) + dp(j, i, k, 1) - (k-i+1));
                }
            }
        }
    }
    printf("%d\n", ans);
}