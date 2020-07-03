#ifndef __PANTHER_H
#define __PANTHER_H

#include <vector>

/*
You must implement this function!
- N is the number of members.
- S is the subtask number (see below).
supervisors should return a vector A of N values where A[i] is the member who is the supervisors of
member i. If member i is the boss then A[i] = -1
*/
std::vector<int> supervisors(int N, int S);

/*
Implemented by grader.
query will return the member ID that is the answer of the question.
- a,b are the member IDs of the aforementioned question.
*/
int query(int a, int b);

#endif
