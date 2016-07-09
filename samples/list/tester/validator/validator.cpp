#include "../testlib.h"

int main () {
    registerValidation();

    int n = inf.readInt();
    inf.readEoln();
    int size = 0;

    for (int i = 0; i < n; i++) {
        char c = inf.readChar();
        inf.readSpace();
        int a, b;

        if (c == 'a') {
            a = inf.readInt();
            inf.readSpace();
            b = inf.readInt();
        } else if (c == 'd' || c == 'g' || c == 'f' || c == 'b' || c == 'c' || c == 'D') {
            a = inf.readInt();
        }

        if (c == 'a') {
            if (a < 0 || a > size) {
                printf("Invalid argument for add %d. %d not in [0,%d]\n", i, a, size);
                return -1;
            }
            size++;
        } else if (c == 'f' || c == 'b') {
            size++;
        } else if (c == 'g') {
            if (a < 0 || a >= size) {
                printf("Invalid argument for get %d. %d not in [0,%d)\n", i, a, size);
                return -1;
            }
        } else if (c == 'd') {
            if (a < 0 || a >= size) {
                printf("Invalid argument for delete %d. %d not in [0,%d)\n", i, a, size);
                return -1;
            }
            size--;
        } else if (c == 'D' || c == 'F' || c == 'B') {
            if (size <= 0) { 
                printf("Invalid delete %d. Size %d\n", i, size);
                return -1;
            }
            size--;
        }

        inf.readEoln();
    }

    inf.readEof();
}
