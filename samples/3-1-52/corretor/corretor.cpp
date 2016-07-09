#include <bits/stdc++.h>

using namespace std;

const int S = 300;

vector<pair<int, string> > v;
string aux;
char str[S];

int main () {
    while (scanf(" %s", str) != EOF) {
        for (int i = 0; str[i]; i++)
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] = str[i] - 'A' + 'a';
        aux = str;
        v.push_back(make_pair(0, aux));
    }

    sort(v.begin(), v.end());

    int c = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[c].second != v[i].second)
            v[++c].second = v[i].second;
        v[c].first--;
    }

    v.resize(c+1);
    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++)
        printf("%s %d\n", v[i].second.c_str(), -v[i].first);
}
