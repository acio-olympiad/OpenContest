// n^3 dp thats secretly n^2 + s^2 (with a log because map)
#include <bits/stdc++.h>
using namespace std;
#define MAXN 2002
int n, s, x[MAXN], y[MAXN], ans;
int pre[MAXN][MAXN];
map<array<int, 4>, int> memo;
int dp(int c, int a, int b, int dir) {
	if (b < a) return 0;
    array<int, 4> stuff = { c, a, b, dir };
	if (memo[stuff]) return memo[stuff]-1;
	if (pre[b][c] - pre[a-1][c] != b-a+1) {
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
        pre[x[i]][y[i]] = 1;
    }
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) {
    		pre[i][j] += pre[i-1][j];
    	}
    }
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) {
    		for (int k = j; k <= n && pre[k][i] != pre[k-1][i]; k++) {
    			ans = max(ans, dp(i, j, k, 0) + dp(i, j, k, 1) - (k-j+1));
    		}
    	}
    }
    printf("%d\n", ans);
}