#include "../testlib.h"
#include <cstdio>
#include <map>
#include <algorithm>
#include <cassert>
#include <random>

typedef long long int ll;

const int N = 10000000;

// params
ll n, m, r;
int p[N];
int cn;
int isconn;
int ed[N][2];

// edges
std::set<std::pair<int, int> > s;
std::pair<int, int> edge;


int get_int (char ** argv) {
    int res;
    sscanf(argv[0], "%d", &res);
    return res;
}

bool add_edge (int i, int j) {
    edge.first = i;
    edge.second = j;
    if (s.find(edge) != s.end()) {
        return 0;
    }
    s.insert(edge);
    return 1;
}

void make_ssc (int n) {
    if (n <= 1) return;

    int k = 0;
    while (k <= 1)
        k = rnd.next(n)+1;

    for (int i = 0; i < k; i++) {
        assert(add_edge(i, (i+1)%k));
    }

    while (k < n) {
        int a = rnd.next(k);
        int b = a;
        while (b == a) {
            b = rnd.next(k);
        }
        
        int q = rnd.next(k, n);

        if (k < q || !add_edge(a, b)) {
            q = rnd.next(k+1, n);

            add_edge(a, k);
            add_edge(q-1, b);
            k++;
            while (k < q) {
                add_edge(k-1, k);
                k++;
            }
        }
    }
}

int main (int argc, char ** argv) {
    registerGen(argc, argv, 1);
    
    n = rnd.next(get_int(argv+1), get_int(argv+2));
    m = rnd.next(get_int(argv+3), get_int(argv+4));
    isconn = get_int(argv+5);

    r = rnd.next(n);
    make_ssc(r);

    for (int i = r; isconn && i < n; i++)
        add_edge(rnd.next(r), rnd.next(r, n-1));

    m -= s.size();
    while (m-- > 0)
        add_edge(rnd.next(n), rnd.next(r, n-1));

    m = 0;
    for (std::pair<int, int> v : s) {
        ed[m][0] = v.first;
        ed[m][1] = v.second;
        m++;
    }

    for (int i = 0; i < n; i++)
        p[i] = i;

    for (int i = 1; i < n; i++)
        std::swap(p[rnd.next(0, i)], p[i]);
    for (int i = 1; i < m; i++)
        std::swap(ed[rnd.next(0, i)], ed[i]);

    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++)
        printf("%d %d\n", p[ed[i][0]], p[ed[i][1]]);
}
