#include <bits/stdc++.h>
using namespace std;

#include "../testlib.h"

int main (int argc, char ** argv) {
    registerGen(argc, argv, 1);
    int lo_n, hi_n;
    sscanf(argv[1], "%d", &lo_n);
    sscanf(argv[2], "%d", &hi_n);

    double lo_d, hi_d;
    sscanf(argv[3], "%lf", &lo_d);
    sscanf(argv[4], "%lf", &hi_d);

    int n = rnd.next(lo_n, hi_n);
    double d = rnd.next(lo_d, hi_d);

    printf("%d %.20f\n", n, d);

    for (int i = 0; i < n; i++)
        printf("%.20f %.20f\n", rnd.next(0., 1.), rnd.next(0., 1.));
}
