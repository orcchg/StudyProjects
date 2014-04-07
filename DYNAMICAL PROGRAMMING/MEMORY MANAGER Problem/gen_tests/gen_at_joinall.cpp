
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;

ostream &out = cout;

const int maxm = 100000;

int N, M, m;
unsigned seed;

#define V(x) if (x) ; else {assert (false);}
#define VE(n, x) if ((n) == (x)) ; else {assert (false);}
#define for if(false) ; else for

unsigned urand () {
    return ((unsigned) rand ()) << 16 + (unsigned) rand ();
}

list<int>::iterator getnth (list<int> &li, int x) {
    list <int>::iterator cur = li.begin ();
    for (int k = 0; k < x; k++) {
        ++cur;
    }
    return cur;
}

int main (int argc, char **argv) {
    if (argc != 4) {
        cerr << "usage: " << argv [0] << " randseed N M" << endl;
        return 1;
    }
    VE (1, sscanf (argv [1], "%u", &seed));
    VE (1, sscanf (argv [2], "%d", &N));
    VE (1, sscanf (argv [3], "%d", &M));

    m = M/2;
    M = 2*m;

    srand (seed);

    list <int> allocs;
    int sum_size = 0;
    int max_frag, rem_frags, size;

    out << N << " " << M << endl;

    sum_size = 0;
    for (int i = 0; i < m; ++i) {
        rem_frags = m - i;
        max_frag = (N - sum_size) / rem_frags;
        size = 1 + urand () % max_frag;
        out << size << endl;
        allocs.push_back (i+1);
        sum_size += size;
    }
    for (int i = 0; i < m; ++i) {
        int x = urand () % allocs.size ();
        list <int>::iterator cur = getnth (allocs, x);
        out << -(*cur) << endl;
        allocs.erase (cur);
    }

    cerr << endl;
    cerr << "size = " << N << "x" << M << endl;

    return 0;
}
