#include<bits/stdc++.h>

using namespace std;

const int N = 1000007;

int vl[N], nx[N][2], es = 1;
bool us[N];
int n, m;
int a;
int qu[N], qi, qf;

int find(int v) {
    int u = 0;
    while (us[u] && vl[u] != v) {
        if (vl[u] > v) u = nx[u][0];
        else u = nx[u][1];
    }
    return u;
}

void insert (int v) {
    int u = find(v);

    assert(!us[u]);
    
    us[u] = 1;
    vl[u] = v;
    nx[u][0] = es++;
    nx[u][1] = es++;
}

void printLevel (int u) {
    assert(us[u]);

    qi = qf = 0;
    qu[qf++] = u;
    while (qi < qf) {
        int v = qu[qi++];

        printf("%d ", vl[v]);

        if (us[nx[v][0]])
            qu[qf++] = nx[v][0];
        if (us[nx[v][1]])
            qu[qf++] = nx[v][1];
    }
    printf("\n");
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        insert(a);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &a);
        int u = find(a);
        printLevel(u);
    }
}
