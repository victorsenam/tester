#include "../testlib.h"
#include <cstdio>
#include <map>
#include <algorithm>
#include <cassert>

// limits
const int N = 1000007;
const int level_N = 4;
const int operation_N = 12;

// aux structures
struct BIT {
    int bit[N];
    int n;

    BIT (int siz)
    { n = siz; memset(bit, 0, sizeof bit); }

    void add (int i, int x) {
        for (i += 2; i <= n+2; i+=(i&-i))
            bit[i] += x;
    }

    int get (int i) {
        int res = 0;
        for (i += 2; i > 0; i-=(i&-i))
            res += bit[i];
        assert(res >= 0);
        return res;
    }
};

// operations
struct Operation {
    char name;
    int cnt;

    Operation () : name(0), cnt(0) {}
    Operation (char n, double c, int m) : name(n), cnt(c*m) {}
};

Operation operation[operation_N];
int operation_queue[operation_N];
int operation_queue_s;

int buildOperations (char ** argv) {
    int level, m_lo, m_hi;
    sscanf(argv[1], "%d", &level);
    sscanf(argv[2], "%d", &m_lo);
    sscanf(argv[3], "%d", &m_hi);

    operation_queue_s = 0;

    int m = rnd.next(m_lo, m_hi);
    int used = 0;

    // valores positivos são relativos
    // valores negativos são absolutos
    const double proportions[operation_N][level_N] = {
        {0., 0., 0., 0.},
        {0.2, 0.2, 0.1, 0.03},
        {0.3, 0.3, 0.3, 0.3},
        {0., -500., 0., 0.},
        {0., -500., 0., 0.},
        {0., -100., 0., 0.},
        {0., -100., 0., 0.},
        {0., 0., 0.09, 0.04},
        {0., 0., 0.01, 0.01},
        {0., 0., 0, 0.05},
        {0., 0., 0, 0.07},
        {0., 0., -1., -1.}
    };

    const char names[operation_N] = {'a', 'd', 'g', 'f', 'b', 'F', 'B', 's', 'e', 'c', 'D', 'i'};
        
    for (int i = 0; i < operation_N; i++) {
        if (proportions[i][level] >= 0.) {
            operation[i] = Operation(names[i], proportions[i][level], m);
        } else {
            operation[i] = Operation(names[i], 1., -proportions[i][level]);
            m += operation[i].cnt;
        }
        used += operation[i].cnt;
    }

    operation[0] = Operation(names[0], 1., m-used);

    for (int i = 0; i < operation_N; i++) {
        if (operation[i].cnt)
            operation_queue[operation_queue_s++] = i;
    }

    return m;
}

// order
int order[N]; 

bool checkOrder () {
    int n = operation[0].cnt;
    std::map<int, double> mp;
    std::map<int, double>::iterator lo_b, up_b;
    float lo_k = 1., hi_k = 1.;

    for (int i = 0; i < n; i++) {
        lo_b = mp.upper_bound(order[i]);

        if (lo_b == mp.end()) {
            mp[order[i]] = hi_k;
            hi_k += 1.;
        } else if (lo_b == mp.begin()) {
            lo_k -= 1.;
            mp[order[i]] = lo_k;
        } else {
            up_b = lo_b--;
            float lo = lo_b->second;
            float hi = up_b->second;
            float val = lo + (hi-lo)*.5;
            if (val <= lo || val >= hi)
                return 0;
            mp[order[i]] = val;
        }
    }
    return 1;
}

void setOrder () {
    long long n = operation[0].cnt;
    int pref = operation[3].cnt;
    int posf = operation[4].cnt;

    for (int i = 0; i < pref; i++)
        order[i] = pref - i - 1;

    for (int i = pref; i < n + pref + posf; i++)
        order[i] = i;

    do {
        int i, j;
        for (long long k = 0; k*k*k < n*n; k++) {
            i = rnd.next(n) + pref;
            j = rnd.next(n) + pref;
            std::swap(order[i], order[j]);
        }
    } while (!checkOrder());
}

// generator
int getNewValue (std::map<int, int> & used, int element) {
    int value;
    do {
        value = rnd.next(INT_MAX);
    } while (used.find(value) != used.end());
    used[value] = element;
    return value;
}

int getUsedValue (std::map<int, int> & used) {
    int ref = rnd.next(INT_MAX);

    std::map<int, int>::iterator it = used.lower_bound(ref);
    if (it == used.end())
        it = used.begin();
    return it->first;
}

void generate (int m) {
    BIT positions = BIT(operation[0].cnt + operation[3].cnt + operation[4].cnt);
    std::map<int, int> used;
    int assigned[N];

    int size = 0;

    int ini[3], fim[3];
    ini[0] = 0; // front
    ini[1] = operation[3].cnt; // mid
    ini[2] = operation[3].cnt + operation[0].cnt; // back
    for (int i = 0; i < 3; i++) fim[i] = ini[i];
    
    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        std::swap(operation_queue[operation_queue_s-1], operation_queue[rnd.next(operation_queue_s)]);
        Operation & current = operation[operation_queue[operation_queue_s-1]];
        
        if ( !size && (current.name != 'a' && current.name != 'f' && current.name != 'b') ) {
            i--;
            continue;
        }
        if ( i != m-1 && current.name == 'i' ) {
            i--;
            continue;
        }

        putchar(current.name);
        putchar(' ');

        if (current.name == 'a' || current.name == 'f' || current.name == 'b') {
            int element;
            if (current.name == 'a')
                element = order[fim[1]++];
            else if (current.name == 'f')
                element = order[fim[0]++];
            else
                element = order[fim[2]++];

            int position = positions.get(element);
            positions.add(element, 1);
            
            int value = getNewValue(used, element);
            assigned[element] = value;
            
            if (current.name == 'a')
                printf("%d ", position);

            printf("%d", value);
            size++;
        } else if (current.name == 'd' || current.name == 'F' || current.name == 'B' || current.name == 'D') {
            int chosen;
            int k;
            if (current.name == 'd' || current.name == 'D') {
                int which = rnd.next(size);
                
                for (k = 0; k < 3 && which >= fim[k] - ini[k]; k++)
                    which -= fim[k] - ini[k];
                assert(k < 3);

                chosen = which + ini[k];
            } else if (current.name == 'F') {
                if (fim[0] - ini[0]) {
                    k = 0;
                    chosen = fim[0]-1;
                } else if (fim[1] - ini[1]) {
                    k = 1;
                    chosen = ini[1];
                } else if (fim[2] - ini[2]) {
                    k = 2;
                    chosen = ini[2];
                } else {
                    assert(false);
                }
            } else if (current.name == 'B') {
                if (fim[2] - ini[2]) {
                    k = 2;
                    chosen = fim[2] - 1;
                } else if (fim[1] - ini[1]) {
                    k = 1;
                    chosen = fim[1] - 1;
                } else if (fim[0] - ini[0]) {
                    k = 0;
                    chosen = ini[0];
                } else {
                    assert(false);
                }
            }

            std::swap(order[chosen], order[ini[k]]);

            int element = order[ini[k]];
            int position = positions.get(element) - 1;
            if (current.name == 'd') {
                printf("%d", position);
            } else if (current.name == 'D') {
                printf("%d", assigned[element]);
            }
            positions.add(element, -1);

            size--;
            ini[k]++;
        } else if (current.name == 'g') {
            printf("%d", rnd.next(size));
        } else if (current.name == 'c') {
            int value = getUsedValue(used);
            printf("%d", value);
        }

        current.cnt--;
        if (current.cnt <= 0)
            operation_queue_s--;

        putchar('\n');
    }
}

int main (int argc, char ** argv) {
    int m = buildOperations(argv);
    setOrder();
    generate(m);
}
