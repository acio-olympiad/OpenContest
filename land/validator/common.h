#ifndef COMMON_H
#define COMMON_H
#include "testlib.h"
#include "bounds.h"
#include <set>
#include <utility>
using namespace std;

struct Checker {
	int N, S;
	vector<pair<int, int>> pts;
	void validate() {
		registerValidation();
		N = inf.readInt(MIN_N, MAX_N, "N");
		inf.readSpace();
		S = inf.readInt(MIN_S, MAX_S, "S");
		inf.readEoln();
		for (int i = 0; i < S; i++) {
			int r = inf.readInt(1, N, "r_i");
			inf.readSpace();
			int c = inf.readInt(1, N, "c_i");
			inf.readEoln();
			pts.emplace_back(r, c);
		}
		inf.readEof();
		ensuref(set<pair<int, int>>(pts.begin(), pts.end()).size() == pts.size(), "Duplicate point");
	}
};

#endif
