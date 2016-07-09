#include <cstdio>
#include <climits>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

/* Globals */
// reference sizes
const int N = 1000003;

// IO
const char filePattern[] = "input/in%03d";
FILE * fileBuffer;
char fileName[80];

// counters
int genCounter;

// structures
typedef __gnu_pbds::tree<
    unsigned,
    __gnu_pbds::null_type,
    std::less<unsigned>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update> ordered_set;
ordered_set used;

/* Functions */
unsigned getUnusedVal (unsigned val) {
    unsigned lo = val;
    unsigned hi = UINT_MAX;

    while (lo < hi) {
        unsigned y = lo + ((long long)hi-lo)/2;

        if (y < val + used.order_of_key(y+1))
            lo = y+1;
        else
            hi = y;
    }

    return lo;
}

void setName () {
    sprintf(fileName, filePattern, genCounter);
    fileBuffer = fopen(fileName, "w");
}

unsigned int getRandom ()
{ return (rand()^(rand()<<1)); }

void generateCase (unsigned n, unsigned m, int min_val, unsigned val_range) {
    setName();

    used.clear();
    fprintf(fileBuffer, "%u %u\n", n, m);
    for (unsigned i = 0; i < n; i++) {
        unsigned pos = getRandom();
        if (val_range - i)
            pos %= (val_range-i);
        
        unsigned x = getUnusedVal(pos);
        
        if(used.find(x) != used.end()) {
            printf("FAILED unused[%d] = %d\n", pos, min_val+x);
            for (unsigned v : used)
                printf("%d ", v+min_val);
            printf("\n");
            assert(false);
        }
        used.insert(x);

        fprintf(fileBuffer, "%d ", min_val + x);
    }
    fprintf(fileBuffer, "\n");

    for (int i = 0; i < m; i++) {
        unsigned pos = rand()%(n-i);
        unsigned x = *(used.find_by_order(pos));
        used.erase(x);
        
        fprintf(fileBuffer, "%d ", min_val + x);
    }
    fprintf(fileBuffer, "\n");
    fflush(fileBuffer);
    fclose(fileBuffer);

    printf("Done %03d\n", genCounter++);
}

void generateRandomCase (unsigned min_size, unsigned max_size, int min_val, unsigned val_range) {
    assert(!val_range || val_range >= max_size-min_size);
    assert(max_size >= min_size);

    unsigned n = getRandom()%((long long)max_size - min_size + 1) + min_size;
    unsigned m = getRandom()%((long long)n - min_size + 1) + min_size;

    generateCase(n, m, min_val, val_range);
}

int main () {
    srand(1337); rand(); rand();

    // permutations : cases [0..10)
    for (int i = 1; i <= 10000; i *= 10) {
        generateCase(i, i, 0, i);
        if (i > 1)
            generateCase(i, i, 0, i);
    }
    generateCase(10000, 100, 0, 10000);

    // tiny cases : cases [10..30)
    for (int i = 0; i < 20; i++) {
        generateRandomCase(5, 20, -(1<<(i+4)), (1<<(i+5)));
    }

    // small cases tiny-range : cases [30..35)
    int tmp = 50;
    for (int i = 0; i < 5; i++) {
        generateRandomCase(10, 100, -tmp, 2*tmp);
        tmp += tmp/2;
    }

    // small cases full-range : cases [35..55)
    for (int i = 0; i < 20; i++)
        generateRandomCase(10, 100, INT_MIN, 0);

    // medium cases only positives : cases [55..85)
    for (int i = 0; i < 30; i++) 
        generateRandomCase(1000, 10000, INT_MIN, 0);

    // large cases : cases [85..100)
    for (int i = 0; i < 15; i++)
        generateCase(100000, 10000, INT_MIN, 0);
}
