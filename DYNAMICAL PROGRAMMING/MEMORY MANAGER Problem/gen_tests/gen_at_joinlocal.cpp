
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

int N, M, m, line_count;
unsigned seed;

#define V(x) if (x) ; else {assert (false);}
#define VE(n, x) if ((n) == (x)) ; else {assert (false);}
#define for if(false) ; else for

typedef pair<int,int> Pair;
typedef list<Pair> List;

List::iterator getnth (List &li, int x) {
    List::iterator cur = li.begin ();
    for (int k = 0; k < x; k++) {
        ++cur;
    }
    return cur;
}

unsigned urand () {
    return ((unsigned) rand ()) << 16 + (unsigned) rand ();
}

int main (int argc, char **argv) {
    if (argc != 5) {
        cerr << "usage: " << argv [0] << " randseed N M line_count" << endl;
        return 1;
    }
    VE (1, sscanf (argv [1], "%u", &seed));
    VE (1, sscanf (argv [2], "%d", &N));
    VE (1, sscanf (argv [3], "%d", &M));
    VE (1, sscanf (argv [4], "%d", &line_count));

    srand (seed);

    List allocs;
    int sum_size = 0;
    int max_frag, rem_frags, size;

    out << N << " " << M << endl;

    sum_size = 0;
    for (int i = 0; i < line_count; ++i) {
        rem_frags = line_count - i;
        max_frag = (N - sum_size) / rem_frags;
        size = 1 + urand () % max_frag;
        out << size << endl;
        allocs.push_back (Pair (i+1, size));
        sum_size += size;
    }
    int requests = line_count;
    while (requests < M-1) {
        int a = urand () % allocs.size ();
        int mx = allocs.size () - a;
        if (mx > (M-requests)/2)
            mx = (M-requests)/2;
        int b = a + urand () % mx;
        int count = b-a+1;
        int thissize = 0;
        for (int j = 0; j < count; j++) {
            int x = a + urand () % (b - a + 1);
            List::iterator cur = getnth (allocs, x);
            out << -cur->first << endl;
            thissize += cur->second;
            allocs.erase (cur);
            --b;
        }
        List added;
        sum_size = 0;
        for (int i = 0; i < count; ++i) {
            rem_frags = count - i;
            max_frag = (thissize - sum_size) / rem_frags;
            size = 1 + urand () % max_frag;
            out << size << endl;
            allocs.push_back (Pair (requests+count+i+1, size));
            sum_size += size;
        }
        allocs.insert (getnth (allocs, a), added.begin (), added.end ());
        requests += 2*count;
        assert (count>0);
    }

    cerr << endl;
    cerr << "size = " << N << "x" << requests  << endl;

    return 0;
}
