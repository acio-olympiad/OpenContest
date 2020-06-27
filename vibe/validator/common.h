#ifndef H_COMMON
#define H_COMMON
#include "testlib.h"
#include "bounds.h"
#include <iostream>

using namespace std;

int validate(int maxN, int maxM, int maxD, bool graphIsLine) {
    registerValidation();
    int n = inf.readInt(MIN_N, maxN, "n");
    inf.readSpace();
    int m = inf.readInt(MIN_M, maxM, "m");
    inf.readEoln();
    
    inf.readInts(n, MIN_V, MAX_V);
    inf.readEoln();

    inf.readInts(m, MIN_D, maxD);
    inf.readEoln();

    for (int i = 2; i <= n; i++) {
        int a = inf.readInt(1, i-1);
        if (graphIsLine) {
            ensuref(a == i-1, "Graph must form a line (a_i == i-1)");
        }
        if (i != n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}

#endif // COMMON_H
