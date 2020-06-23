// n log n, due to sort 
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000010
vector<int> inrow[MAXN];
struct Data {
    int above, below, leftam, rightam;
};
unordered_map<int, Data> info[MAXN]; // use of struct rather than 4 unordered_maps to avoid 20s compile time
int n, s, x[MAXN], y[MAXN], ans;
void processStack(int val, vector<pair<int, int> > &sta, int &am) { // val is value to be added to stack, am is sum of values in stack
    int total = 1;
    while (sta.size() && sta.back().first >= val) {
        am -= sta.back().first*sta.back().second;
        total += sta.back().second;
        sta.pop_back();
    }
    am += val*total;
    sta.emplace_back(val, total);
}
int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < s; i++) {
        scanf("%d%d", &x[i], &y[i]);
        inrow[x[i]].push_back(y[i]);
    }
    for (int i = 1; i <= n; i++) {
        sort(inrow[i].begin(), inrow[i].end());
    }
    // precomp number of squares directly above/below
    for (int i = 1; i <= n; i++) {
        for (auto j : inrow[i]) {
            info[i][j].above = info[i-1][j].above+1;
        }
    }
    for (int i = n; i >= 1; i--) {
        for (auto j : inrow[i]) {
            info[i][j].below = info[i+1][j].below+1;
        }
    }
    // do storted stack thing for left
    for (int i = 1; i <= n; i++) {
        vector<pair<int, int> > upsta, downsta;
        int upam = 0, downam = 0, pre = 0;
        for (auto j : inrow[i]) {
            if (pre+1 != j) processStack(0, upsta, upam), processStack(0, downsta, downam);
            pre = j; 
            processStack(info[i][j].above, upsta, upam);
            processStack(info[i][j].below-1, downsta, downam);
            info[i][j].leftam = upam+downam;
        }
    }
    // do storted stack thing for right
    for (int i = 1; i <= n; i++) {
        vector<pair<int, int> > upsta, downsta;
        int upam = 0, downam = 0, pre = 0;
        reverse(inrow[i].begin(), inrow[i].end());
        for (auto j : inrow[i]) {
            if (pre-1 != j) processStack(0, upsta, upam), processStack(0, downsta, downam);
            pre = j; 
            processStack(info[i][j].above, upsta, upam);
            processStack(info[i][j].below-1, downsta, downam);
            info[i][j].rightam = upam+downam;
        }
    }
    // find answer
    for (int i = 1; i <= n; i++) {
        for (auto j : inrow[i]) {
            if (info[i][j].above == 1) {
                int mxleft = 0, mxright = 0;
                for (int k = i; k < i+info[i][j].below; k++) {
                    mxleft = max(mxleft, info[k][j].leftam);
                    mxright = max(mxright, info[k][j].rightam);
                }
                ans = max(ans, mxleft+mxright-info[i][j].below);
            }
        }
    }
    printf("%d\n", ans);
}