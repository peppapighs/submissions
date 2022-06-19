#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, q;
map<int, vector<int>> mp;

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        mp[a].emplace_back(i);
    }
    for (int i = 1, l, r, c; i <= q; i++) {
        scanf("%d %d %d", &l, &r, &c);
        auto it1 = lower_bound(mp[c].begin(), mp[c].end(), l);
        auto it2 = upper_bound(mp[c].begin(), mp[c].end(), r);
        printf("%d\n", it2 - it1);
    }

    return 0;
}