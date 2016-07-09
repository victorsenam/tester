#include "../testlib.h"
#include <bits/stdc++.h>

typedef long long int ll;

std::set<std::pair<int, int> > s;
std::pair<int, int> aux;

int main () {
    registerValidation();

    inf.readToken("[a-z]*");
    inf.readEoln();
    ll n = inf.readInt();
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readToken("[a-z]*");
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
