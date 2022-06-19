#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 2e5 + 5;

int n, k;
int cen, ptr;
long ans;
vector<pii> g[N];

void leaf(int u, int p, long d, ordered_set<pii> &S) {
    ans += S.size() - S.order_of_key(pii(d - k, 0));
    S.insert(pii(d, ++ptr));
    for (pii v : g[u])
        if (v.x != p && g[v.x].size() <= 2)
            leaf(v.x, u, d + v.y, S);
}

void dfs(int u, int p, long d, ordered_set<pii> &S, bool fill) {
    if (d > k)
        return;
    if (fill)
        S.insert(pii(d, ++ptr));
    else
        ans += S.order_of_key(pii(k - d + 1, 0));
    for (pii v : g[u])
        if (v.x != p)
            dfs(v.x, u, d + v.y, S, fill);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    for (int i = 1; i <= n; i++) {
        ordered_set<pii> S;
        if (g[i].size() == 1)
            leaf(i, i, 0, S);
        if (g[i].size() > 2)
            cen = i;
    }
    if (!cen)
        return !printf("%lld\n", ans / 2ll);

    ordered_set<pii> S;
    S.insert(pii(0, ++ptr));
    for (pii v : g[cen]) {
        dfs(v.x, cen, v.y, S, 0);
        dfs(v.x, cen, v.y, S, 1);
    }

    printf("%lld\n", ans);

    return 0;
}
