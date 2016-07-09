#include "../testlib.h"

int main () {
    registerValidation();

    int n = inf.readInt();
    inf.readSpace();
    inf.readDouble(0.00001, 1./0.);
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readDouble(0., 1.);
        inf.readSpace();
        inf.readDouble(0., 1.);
        inf.readEoln();
    }

    inf.readEof();
}
