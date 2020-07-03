#include "panther.h"
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1005
using namespace std;

vector<int> supervisors(int n, int s){
    vector <int> order, res(n);
    for (int i=0; i<n; i++) {order.push_back(i);}
    make_heap(order.begin(), order.end(), [](int a, int b) {return(query(a,b) == a);});
    sort_heap(order.begin(), order.end(), [](int a, int b) {return(query(a,b) == a);});
    for (int i=0; i<n; i++) {
        res[order[i]] = i ? order[i-1] : -1;
    }
    return(res);
}
