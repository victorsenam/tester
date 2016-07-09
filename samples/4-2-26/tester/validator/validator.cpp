#include "../testlib.h"
#include <bits/stdc++.h>

typedef long long int ll;

int main () {
    registerValidation();

    ll n = inf.readInt();
    inf.readSpace();
    ll m = inf.readInt();
    ensuref(m >= 0, "A expressão não pode ter menos que zero cláusulas");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        ensuref(a != 0 && std::max(a, -a) <= n, "Literal inválido %d. n = %lld\n", a, n);
        inf.readSpace();
        int b = inf.readInt();
        ensuref(b != 0 && std::max(b, -b) <= n, "Literal inválido %d. n = %lld\n", b, n);
        inf.readEoln();

    }
    inf.readEof();

    return 0;
}
