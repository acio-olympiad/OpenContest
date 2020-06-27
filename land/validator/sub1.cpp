#include "common.h"

int main() {
	Checker c{}; c.validate();
	ensuref(c.N <= 200, "N does not match sub1 bounds");
	ensuref(c.S <= 200, "S does not match sub1 bounds");
	return 0;
}
