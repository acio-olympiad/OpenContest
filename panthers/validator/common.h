#ifndef H_COMMON
#define H_COMMON
#include "testlib.h"
#include <iostream>
#include <string>
using namespace std;

void error(string msg) {
    cout << msg;
    exit(0);
}

class DSU {
public:
    int Set[1005];
    void init(int n) {
        for (int i=0; i<n; i++) {Set[i]=i;}
    }
    int Find(int x) {
        return(Set[x] == x ? x : Set[x] = Find(Set[x]));
    }
    void Union(int x, int y) {
        Set[Find(x)] = y;
    }
};

int validate(int subtask) {
    registerValidation();
    int G = inf.readInt(0,2, "G");
    inf.readSpace();
    int minN = 1, maxN = subtask == 1 ? 200 : 1000;
    int n = inf.readInt(minN, maxN, "n");
    inf.readSpace();
    int SB = inf.readInt(subtask, subtask, "s");
    inf.readEoln();
    if (G == 1) {
        int num_spikey = inf.readInt(0,n/2, "P");
        inf.readEoln();
        inf.readEof();
        return(0);
    }
    int P[1005], deg[1005] = {};
    DSU UF;
    UF.init(n);
    int rt = -1;
    for (int i = 0; i < n; i++) {
        P[i] = inf.readInt(-1,n-1, "P");
        if (i != n-1) {inf.readSpace();}
        if (P[i] == -1) {
            if (rt != -1) {error("too many roots");}
            rt = i;
            continue;
        }
        deg[P[i]]++;
        if (UF.Find(i) == UF.Find(P[i])) {
            error("Not Tree");
        } else {
            UF.Union(i, P[i]);
        }
        //  printf("Read %d\n",i);
    }
    inf.readEoln();
    inf.readEof();
    if (rt == -1) {
        error("No root");
    }
    for (int i=0; i<n; i++) {
        if (deg[i] > 2) {
            error("Not Binary Tree");
        } else if (deg[i] > 1 && SB == 2) {
            error("Subtask 2 and not line");
        } else if (P[i] > i && SB == 3) {
            error("Subtask 3 and P[i]>i");
        }
    }
    return 0;
}

#endif // COMMON_H
