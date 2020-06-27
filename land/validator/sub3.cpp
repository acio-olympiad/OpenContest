#include "common.h"

int main() {
	Checker c{}; c.validate();
	ensuref(c.N <= 2000, "N does not match sub3 bounds");
	ensuref(c.S <= 100000, "S does not match sub3 bounds");
	return 0;
}
