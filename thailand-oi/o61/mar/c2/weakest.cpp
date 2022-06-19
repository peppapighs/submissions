#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, par[N][18], mn[N][18], dep[N];
int q, k, m, a1, a2;
vector<pii> g[N];

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i <= 17; i++) {
        mn[u][i] = min(mn[u][i - 1], mn[par[u][i - 1]][i - 1]);
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for (pii v : g[u])
        if (v.x != p) {
            mn[v.x][0] = v.y;
            dfs(v.x, u);
        }
}

int lca(int a, int b) {
    int ret = 1e9;
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b]) {
            ret = min(ret, mn[a][i]);
            a = par[a][i];
        }
    if (a == b)
        return ret;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i]) {
            ret = min({ret, mn[a][i], mn[b][i]});
            a = par[a][i], b = par[b][i];
        }
    return min({ret, mn[a][0], mn[b][0]});
}

int main() {
    fill_n(mn[0], N * 18, 1e9);
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(i, b), g[i].emplace_back(a, b);
    }
    dfs(0, 0);
    scanf("%d %d %d %d %d", &q, &k, &m, &a1, &a2);
    for (int i = 1; i <= q; i++) {
        int now = a1 == a2 ? 0 : lca(a1, a2);
        printf("%d\n", now);
        int nex = ((a2 * k + now) % m) % n;
        a1 = a2, a2 = nex;
    }

    return 0;
}
