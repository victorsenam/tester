#include <bits/stdc++.h>

using namespace std;


char c;
int main () {
    while (c = getchar()) {
        if (c == EOF) break;
        if (isalpha(c) || isspace(c) || c == '-')
            putchar(c);
    }
}
