#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct UnionFind {
    int par[N];

    UnionFind() { iota(par, par + N, 0); }

    int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return;
        par[a] = b;
    }
} d1, d2;

int n, m, idx;
vector<vector<int>> g;
vector<int> pre, low, l, r;

void tarjan(int u, int p) {
    pre[u] = low[u] = ++idx;
    bool chk = false;
    for (int v : g[u]) {
        if (v == p && !chk)
            chk = true;
        else if (!pre[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > pre[u])
                l.emplace_back(u), r.emplace_back(v);
        } else
            low[u] = min(low[u], pre[v]);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    g.resize(n + 1), pre.resize(n + 1), low.resize(n + 1);

    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        if (d1.find(a) != d1.find(b)) {
            d1.unite(a, b);
            g[a].emplace_back(b), g[b].emplace_back(a);
        } else if (d2.find(a) != d2.find(b)) {
            d2.unite(a, b);
            g[a].emplace_back(b), g[b].emplace_back(a);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!pre[i])
            tarjan(i, 0);
    for (int i = 0; i < l.size(); i++)
        printf("%d %d\n", l[i], r[i]);

    return 0;
}