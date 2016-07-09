#include <bits/stdc++.h>

using namespace std;

int c;

int main () {
    int range = 1;
    int maxrange = 10000;
    int lvl = 0;

    for (int i = 0; i < 100; i++) {
        printf("%d %d %d\n", lvl, range, 4*range, c++);
        range *= 10;
        if (range >= maxrange)
            range = 1;

        if (i == 20) lvl = 1;
        if (i == 30) lvl = 2;
        if (i == 60) lvl = 3;
    }
}
