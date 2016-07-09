#include "../testlib.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <random>
#include <string>

typedef long long int ll;

// params
ll n, m, p;
int siz;
std::vector<std::string> strs;

int get_int (char ** argv) {
    int res;
    sscanf(argv[0], "%d", &res);
    return res;
}

void genString () {
    strs.push_back("");
    do {
        strs[siz].push_back(rnd.next(26)+'a');
    } while (rnd.next(m));
    printf("%s\n", strs[siz].c_str());
    siz++;
}

int main (int argc, char ** argv) {
    registerGen(argc, argv, 1);
    
    n = rnd.next(get_int(argv+1), get_int(argv+2));
    m = rnd.next(get_int(argv+3), get_int(argv+4));
    siz = 0;

    printf("%lld\n", n);
    for (int i = 0; i < n; i++) {
        p = rnd.next(10);

        if (!siz || p < 5) {
            printf("a ");
            genString();
        } else if (p < 7) {
            printf("r ");
            printf("%s\n", strs[rnd.next(siz)].c_str());
        } else if (p < 8) {
            printf("f ");
            genString();
            siz--;
        } else if (p < 9) {
            printf("c ");
            genString();
            siz--;
        } else {
            printf("s %d\n", rnd.next(siz));
        }
    }

    return 0;
}
