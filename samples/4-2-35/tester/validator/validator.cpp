#include "../testlib.h"
#include <bits/stdc++.h>

typedef long long int ll;

std::set<std::pair<int, int> > s;
std::pair<int, int> aux;

int main () {
    registerValidation();

    ll n = inf.readInt();
    inf.readSpace();
    ll m = inf.readInt();
    ensuref(m >= 0, "Graph can't contain negative quantity of edges");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        aux.first = inf.readInt(0, n-1);
        inf.readSpace();
        aux.second = inf.readInt(0, n-1);
        ensuref(s.find(aux) == s.end(), "Repeated edge %d %d", aux.first, aux.second);
        inf.readEoln();
        s.insert(aux);
    }
    inf.readEof();

    return 0;
}
