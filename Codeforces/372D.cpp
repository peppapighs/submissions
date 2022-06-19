#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k;
int pre[N], inv[N], par[N][18], dep[N];
vector<int> g[N];

void dfs(int u, int p) {
    static int idx = 0;
    inv[pre[u] = ++idx] = u;
    dep[u] = dep[p] + 1, par[u][0] = p;
    for (int i = 1; i <= 17; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

int d(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }

int sz;
set<int> active;

int get_cost(int u) {
    if (active.empty())
        return 1;
    if (active.size() == 1)
        return d(inv[*active.begin()], u);
    auto it = active.lower_bound(pre[u]);
    if (it != active.begin() && it != active.end())
        return min(d(u, lca(u, inv[*it])), d(u, lca(u, inv[*prev(it)])));
    else {
        int rot = lca(inv[*active.begin()], inv[*active.rbegin()]);
        if (rot == lca(u, rot)) {
            if (it == active.begin())
                return d(u, lca(u, inv[*it]));
            else
                return d(u, lca(u, inv[*prev(it)]));
        } else
            return d(u, rot);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 1, j = 1; i <= n; i++) {
        sz += get_cost(i);
        active.emplace(pre[i]);
        while (sz > k) {
            active.erase(pre[j]);
            sz -= get_cost(j++);
        }
        ans = max(ans, i - j + 1);
    }
    printf("%d\n", ans);

    return 0;
}