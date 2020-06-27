#include "common.h"

int main() {
	Checker c{}; c.validate();
	ensuref(c.N <= 2000, "N does not match sub2 bounds");
	ensuref(c.S <= 2000, "S does not match sub2 bounds");
	return 0;
}
