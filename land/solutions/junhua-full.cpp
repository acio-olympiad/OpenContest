#include <iostream>
#include <vector>
#include <utility>
#define MAXN 1000005
#define fi first
#define se second
using namespace std;
int N, S, Ans, Val[MAXN];
int LoVal[MAXN], HiVal[MAXN], Prev[MAXN], H[MAXN];
vector <pair<int,int> > CS[MAXN], CS2[MAXN]; //count sort
vector <pair<int,int> > St;

void work(int l, int r) { //for a given side find best structure
    for (int j=l; j <= r; j++) {
        int curval = LoVal[j-1];
        while (St.size() && H[St.back().fi] >= H[j]) {
            curval -= St.back().se;
            St.pop_back();
        }
        int prevpos = St.size() ? St.back().fi : l-1;
        St.push_back({j, H[j] * (j - prevpos)});
        LoVal[j] = curval + H[j] * (j - prevpos);
    }
    St.clear();
    for (int j=r; j >= l; j--) {
        int curval = HiVal[j+1];
        while (St.size() && H[St.back().fi] >= H[j]) {
            curval -= St.back().se;
            St.pop_back();
        }
        int prevpos = St.size() ? St.back().fi : r + 1;
        St.push_back({j, H[j] * (prevpos - j)});
        HiVal[j] = curval + H[j] * (prevpos - j);
    }
    St.clear();
}

void Set(int l, int r, bool b) { //set vals and upd H
    int dir = b ? -1 : 1; //b = 1 means left to right
    for (int j=l; j <= r; j++) {
        LoVal[j] = HiVal[j] = 0;
        if (Prev[j] == c + dir) {
            H[j]++;
        } else {
            H[j] = 1;
        }
        Prev[j] = c;
    }
    LoVal[l-1] = LoVal[r+1] = 0;
    HiVal[l-1] = HiVal[r+1] = 0;
}

int main() {
    freopen("landin.txt","r",stdin);
    scanf("%d %d",&N,&S);
    for (int i=1; i<=S; i++) {
        int r,c;
        scanf("%d %d",&r,&c);
        CS[r].push_back({c,i});
    }
    for (int r=1; r <= N; r++) {
        for (auto c: CS[r]) {
            CS2[c.fi].push_back({r, c.se});
        }
    }
    for (int c=1; c <= N; c++) { //eval left side
        if (CS2[c].empty()) {continue;} //current row included in left to right pass but not right to left
        int prev = 0;
        for (int i=0; i<CS2[c].size(); i++) {
            if (i+1 == CS2[c].size() || CS2[c][i].fi + 1 != CS2[c][i+1].fi) {
                Set(CS2[c][prev].fi, CS2[c][i].fi, 1);
                work(CS2[c][prev].fi, CS2[c][i].fi);
                int bestval = 0;
                for (int j=CS2[c][prev].fi; j <= CS2[c][i].fi; j++) {
                    bestval = max(bestval, LoVal[j] + HiVal[j] - H[j]);
                }
                Val[CS2[c][prev].second] = bestval;
                //end computation of left
                prev = i + 1;
            }
        }
    }

    for (int i=0; i <= N+1; i++) {
        Prev[i] = S+1;
        H[i] = 0;
    }

    for (int c=N; c >= 1; c--) { //calculate best right side
        if (CS2[c].empty()) {continue;} //current row included in left to right pass but not right to left
        int prev = 0;
        for (int i=0; i<CS2[c].size(); i++) {
            if (i+1 == CS2[c].size() || CS2[c][i].fi + 1 != CS2[c][i+1].fi) {
                Set(CS2[c][prev].fi, CS2[c][i].fi, 0);
                work(CS2[c][prev].fi, CS2[c][i].fi);
                int bestval = 0;
                for (int j=CS2[c][prev].fi; j <= CS2[c][i].fi; j++) {
                    bestval = max(bestval, LoVal[j] + HiVal[j] - H[j]);
                }
                Val[CS2[c][prev].second] += bestval - CS2[c][i].fi + CS2[c][prev].fi - 1;
                //end computation of left
                prev = i + 1;
            }
        }
    }
    for (int i=1; i<=S; i++) {
        Ans = max(Ans, Val[i]);
    }
    printf("%d", Ans);
}
