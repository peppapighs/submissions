#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, q;
int par[N][18], sz[N], dep[N], ans[N];
vector<int> g[N];
vector<pii> Q[N];
map<int, int> mp;

void dfs(int u, int p) {
    sz[u] = 1, dep[u] = dep[p] + 1;
    for (int i = 1; i <= 17; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            dfs(v, u), sz[u] += sz[v];
}

void add(int u, int p) {
    mp[dep[u]]++;
    for (int v : g[u])
        if (v != p)
            add(v, u);
}

void dsu(int u, int p, bool keep) {
    int hv = -1;
    for (int v : g[u])
        if (v != p && (hv == -1 || sz[hv] < sz[v]))
            hv = v;
    for (int v : g[u])
        if (v != p && v != hv)
            dsu(v, u, 0);
    if (hv != -1)
        dsu(hv, u, 1);
    mp[dep[u]]++;
    for (int v : g[u])
        if (v != p && v != hv)
            add(v, u);
    for (pii q : Q[u])
        ans[q.x] = mp[dep[u] + q.y] - 1;
    if (!keep)
        mp.clear();
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &par[i][0]);
        if (par[i][0])
            g[i].emplace_back(par[i][0]), g[par[i][0]].emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
        if (!par[i][0])
            dfs(i, i);
    scanf("%d", &q);
    for (int i = 1, v, p; i <= q; i++) {
        scanf("%d %d", &v, &p);
        for (int b = 17; ~b; b--)
            if ((p >> b) & 1)
                v = par[v][b];
        if (v == 0)
            ans[i] = 0;
        else
            Q[v].emplace_back(i, p);
    }
    for (int i = 1; i <= n; i++)
        if (!par[i][0])
            dsu(i, i, 0);
    for (int i = 1; i <= q; i++)
        printf("%d ", ans[i]);

    return 0;
}