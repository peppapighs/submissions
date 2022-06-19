#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, l;
    scanf("%d %d", &n, &l);

    vector<ordered_set<int>> v(n + 1);
    vector<int> par(n + 1), sz(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        v[i].insert(i);
        par[i] = i;
    }

    function<int(int)> find = [&](int u) {
        return u == par[u] ? u : find(par[u]);
    };
    for (int i = 1, T, a, b; i <= l; i++) {
        scanf("%d %d", &T, &a);
        if (T == 1) {
            scanf("%d", &b);
            a = find(a), b = find(b);
            if (sz[a] > sz[b])
                swap(a, b);
            sz[b] += sz[a], par[a] = b;
            for (int x : v[a])
                v[b].insert(x);
            v[a].clear();
        } else
            printf("%d\n", sz[find(a)] - v[find(a)].order_of_key(a));
    }
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}