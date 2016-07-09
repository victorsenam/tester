#include "../testlib.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <random>
#include <string>

const int N = 1000007;
const int Q = 200;

// params
int n; // pattern size
int m; // mean for strings size - 1
int k; // inverse of pattern escape probability
int a; // alphabet size

// vars
char pat[N];
int fail[N];

int get_int (char ** argv) {
    int res;
    sscanf(argv[0], "%d", &res);
    return res;
}

void genString () {
    int p = 0;
    char c;
    do {
        if (p == n) p = fail[p-1];

        if (rnd.next(k)) {
            c = pat[p++];
        } else {
            c = rnd.next(a)+'a';
            while (p && pat[p] != c)
                p = fail[p-1];
            if (pat[p] == c)
                p++;
        }
        putchar(c);
    } while (rnd.next(m));
    putchar('\n');
}

int main (int argc, char ** argv) {
    registerGen(argc, argv, 1);
    
    n = get_int(argv+2);
    m = get_int(argv+3);
    k = get_int(argv+4);
    a = get_int(argv+5);

    for (int i = 0; i < n; i++) {
        pat[i] = rnd.next(a) + 'a';
        if (i) {
            int & p = fail[i];
            p = fail[i-1];
            while (p && pat[p] != pat[i])
                p = fail[p-1];
            if (pat[p] == pat[i])
                p++;
        }
    }
    pat[n] = 0;
    printf("%s\n", pat);
    printf("%d\n", Q);
    for (int q = 0; q < Q; q++)
        genString();

    return 0;
}
