#include "../testlib.h"
#include <bits/stdc++.h>

typedef long long int ll;

int main () {
    registerValidation();

    ll n = inf.readInt();
    ensuref(n >= 0, "Não pode haver uma quantidade negativa de queries");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        char c = inf.readChar();
        if (c == 'a' || c == 'f' || c == 'c' || c == 'r') {
            inf.readSpace();
            inf.readToken();
        } else if (c == 's') {
            inf.readSpace();
            inf.readInt();
        } else {
            ensuref(false, "Operação inválida");
        }
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
