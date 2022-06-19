#include <bits/stdc++.h>

using namespace std;

char sub[100], ret[100];

void solve(vector<int> &v) {
    if (v.size() == 1) {
        printf("0 %d\n", v[0]);
        fflush(stdout);
        return;
    }
    int n = v.size(), sz = 3;
    while (sz < n)
        sz *= 3;

    int a = sz / 3, b = min(sz / 3, n - a);
    vector<int> ask, v1, v2, v3;
    for (int i = 0; i < n; i++) {
        if ((i % 2 == 0 || !b) && a) {
            ask.emplace_back(v[i]), --a;
            v1.emplace_back(v[i]);
        } else if ((i & 1) && b) {
            ask.emplace_back(v[i] - 1), --b;
            v2.emplace_back(v[i]);
        } else
            v3.emplace_back(v[i]);
    }
    sort(ask.begin(), ask.end());
    ask.resize(unique(ask.begin(), ask.end()) - ask.begin());
    printf("%d ", ask.size());
    for (int i : ask)
        printf("%d ", i);
    printf("\n"), fflush(stdout);

    scanf(" %s", ret);
    if (ret[0] == 'Y')
        solve(v1);
    else if (ret[0] == 'B')
        solve(v2);
    else
        solve(v3);
}

int n, k;

int main() {
    scanf("%s", sub);
    scanf("%d %d", &n, &k);
    vector<int> v;
    for (int i = 1; i <= n; i++)
        v.emplace_back(i);
    solve(v);

    return 0;
}