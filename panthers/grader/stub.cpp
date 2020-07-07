#include "panther.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <csignal>
int _N, _S;
FILE *fifo_in, *fifo_out;

void contestant_messed_up() {
	fprintf(fifo_out, "-3\n");
	fflush(fifo_out);
	exit(0);
}

void handle_signal(int sig) {
	// guess i'll exit gracefully
	exit(0);
}

int main(int argc, char **argv) {
	signal(SIGPIPE, handle_signal);
	fifo_in = fopen(argv[2], "r");
	fifo_out = fopen(argv[1], "w");
	fscanf(fifo_in, "%d %d", &_N, &_S);
	std::vector<int> _result = supervisors(_N, _S);
	if (_result.size() != _N) {
		contestant_messed_up();
	} else {
		fprintf(fifo_out, "1");
		for (int i = 0; i < _N; i++) {
			fprintf(fifo_out, " %d", _result[i]);
		}
		fprintf(fifo_out, "\n");
		fflush(fifo_out);
	}
}

int query(int a, int b) {
	if (std::min(a, b) < 0 || std::max(a, b) >= _N) { 
		contestant_messed_up();
		return -1;
	} else {
		fprintf(fifo_out, "0 %d %d\n", a, b);
		fflush(fifo_out);
		int res = -1;
		fscanf(fifo_in, "%d", &res);
		if (res == -1) contestant_messed_up();
		return res;
	}
}
