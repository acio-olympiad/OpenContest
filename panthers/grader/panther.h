#ifndef __PANTHER_H
#define __PANTHER_H

#include <vector>

/* 
You must implement this function!
- N is the number of members.
- S is the subtask number (see below).
handlers should return a vector A of N values where A[i] is the member who is the handler of
member i. If member i is the boss then A[i] = -1
*/
std::vector<int> handlers(int N, int S);

/* 
Implemented by grader.
query will return the LCA of members a and b.
*/
int query(int a, int b);

#endif