#include <iostream>
#include <time.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <cassert>
using namespace std;

int rng() { 
        return(rand()); // for use on linux
	/*
    int r1 = rand() % (1 << 15), r2 = rand() % (1 << 15);
    return(r1*(1 << 15) + r2);
	*/ // Uncomment for windows
}

//grid
bool Grid[2005][2005];

void output(int N, int S, vector <pair<int,int> > Squares) {
    printf("%d %d\n",N,S);
    for (auto p : Squares) {
        printf("%d %d\n",p.first,p.second);
    }
}

vector <pair<int,int> > grid(int n, int x, int y) {
    //grid[x][y] = 1 with probability x/y, size n grid
    int S = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            int k = rng()%y;
            Grid[i][j] = 0;
            if (k < x) {
                Grid[i][j] = 1;
                S++;
            }
        }
    }
    vector <pair<int,int> > Res;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if (Grid[i][j] && (((int) Res.size()) < x)) {
                Res.push_back({i,j});
            }
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if (!Grid[i][j] && Res.size() < x) {
                Grid[i][j] = 1;
                Res.push_back({i,j});
            } else if (Res.size() == x) {
                break;
            }
        }
        if (Res.size() == x) {
                break;
        }
    }
    return(Res);
}

//histogram
int H[100005];
vector <pair<int,int> > histogram(int s, int W) {
    //Require s >= 100 preferably
    int cap = 2*s/W, S=0;
    assert(cap >= 10);
    for (int i=1; i<=W; i++) {
        H[i] = (rng() % cap) + 1;
        S += H[i];
        if (S > s) {
            W = i;
            break;
        }
    }
    H[W] += s - S;
    vector <pair<int,int> > Res;
    for (int i=1; i<=W; i++) {
        for (int j=1; j<=H[i]; j++) {
            Res.push_back({i,j});
        }
    }
    return(Res);
}

//random
long long hsh(int x, int y) {
    long long res = (((long long ) x) << 22) + y;
    return(res);
}

vector <pair<int,int> > Rand(int N, int S) {
    assert(N >= S); //otherwise doesn't work well
    unordered_set <long long> In;
    vector <pair<int,int> > Res;
    for (int i=1; i<=S; i++) {
        while (true) {
            int x = rng()%N + 1, y = rng()%N + 1;
            if (In.find(hsh(x,y)) == In.end()) {
                In.insert(hsh(x,y));
                Res.push_back({x,y});
                break;
            }
        }
    }
    return(Res);

}

//segments: long segments, few columns i.e house of 100k blades
vector <pair<int,int> > Segments(int S) {
    //input number of segments per column
    int curx = 1, cury = 1;
    vector <pair<int,int> > Res;
    while (S) {
        int cur = rng()%min(S, 1000) + 1;
        if (cur % 4 == 1 || cur + cury >= S) {
            curx++;
            cury = 1;
        }
        for (int i=1; i <= cur; i++) {
            Res.push_back({curx, cury});
            cury++;
        }
        cury++;
        S -= cur;
    }
    return(Res);
}

//frankeinstein: large testcases with smaller cases on diagonal
vector <pair<int,int> > Select(int ti, int si) {
    if (ti == 1) {
        return(Rand(si,si));
    } else if (ti == 2) {
        return(histogram(si, si/(rng()%10 + 10)));
    } else if (ti == 3) {
        return(Segments(si));
    } else if (ti == 4) {
        return(grid(500, si, 500*500));
    } else if (ti == 5) {
        return(grid(1000, si, 1000*1000));
    } else if (ti == 6) {
        return(grid(2000, si, 2000*2000));
    }
}
void Frankeinstein(int T, int SB, vector <pair<int,int> > tk) {
    vector <pair<int,int> > Res;
    int S = 0;
    for (int i=0; i<T; i++) {
        vector <pair<int,int> > tmp = Select(tk[i].first, tk[i].second);
        for (auto p: tmp) {
            Res.push_back({p.first + S, p.second + S});
        }
        S += tk[i].second;
    }
    if (SB == 3) {
        printf("%d %d\n",2000,S);
    } else {
        printf("%d %d\n",S,S);
    }
    for (auto p: Res) {
        printf("%d %d\n",p.first, p.second);
    }
}

/*user guide:
Program will read in input format
T SB
t1 s1
t2 s2
...
tT sT

1 <= T <= 10 is the number of testcases in input case to generate
1 <= SB <= 6 is the subtask number
Let S = s1 + s2 + ... + sT
If SB != 5 then N = S
Else N = 2000
ti is the gen type of the ith case in the batch
si is the number of allocated squares to the ith test case
ti = 1: random
ti = 2: histogram
ti = 3: segments
ti = 4: grid of size 500
ti = 5: grid of size 1000
ti = 6: grid of size 2000

The program will write to stdout
N S
x1 y1
...
xS yS
*/

int main() {
    //freopen("largein.txt","w",stdout);
    srand(time(NULL));
    int T, SB, Sum = 0, mingentype=7;
    cin >> T >> SB;
    vector <pair<int,int> > testcases;
    for (int i=0; i<T; i++) {
        int ti,si;
        mingentype = min(mingentype, ti);
        cin >> ti >> si;
        assert(1 <= ti && ti <= 6);
        Sum += si;
        testcases.push_back({ti, si});
    }
    if (SB == 1) {
        assert(Sum <= 200);
    } else if (SB == 2) {
        assert(Sum <= 2000);
    } else if (SB == 3) {
        assert(mingentype >= 4); //otherwise too large grid
    } else if (SB == 4) {
        assert(Sum <= 100000);
    } else {
        assert(Sum <= 1000000);
    }
    Frankeinstein(T, SB, testcases);
}
