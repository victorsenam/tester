#include <bits/stdc++.h>

using namespace std;

const int S = 300;

vector<pair<int, string> > v;
string aux;
char str[S];
int f;

int main () {
    while (scanf(" %s %d", str, &f) != EOF) {
        aux = str;
        v.push_back(make_pair(-f, aux));
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++)
        printf("%s %d\n", v[i].second.c_str(), -v[i].first);
}
