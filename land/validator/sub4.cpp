#include "common.h"

int main() {
	Checker c{}; c.validate();
	ensuref(c.N <= 100000, "N does not match sub4 bounds");
	ensuref(c.S <= 100000, "S does not match sub4 bounds");
	return 0;
}
