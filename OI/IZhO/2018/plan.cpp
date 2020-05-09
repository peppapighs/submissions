#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, k, q, d[N], dsu[N];
vector<pii> g[N];
vector<int> t[N];
priority_queue<pii, vector<pii>, greater<pii> > Q;

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int dep[N], par[N][18];

void dfs(int u, int p) {
    dep[u] = dep[p] + 1, par[u][0] = p;
    for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
    for(int v : t[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    return par[a][0];
}

int main() {
    fill_n(d, N, 1e9), iota(dsu, dsu + N, 0);

    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    scanf("%d", &k);
    for(int i = 1, a; i <= k; i++) {
        scanf("%d", &a);
        Q.emplace(d[a] = 0, a);
    }
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(d[u.y] != u.x) continue;
        for(pii v : g[u.y]) if(u.x + v.y < d[v.x])
            Q.emplace(d[v.x] = u.x + v.y, v.x);
    }

    vector<int> vec;
    for(int i = 1; i <= n; i++) vec.emplace_back(i);
    sort(vec.begin(), vec.end(), [&](int a, int b) {
        return pii(d[a], a) > pii(d[b], b);
    });
    for(int u : vec) for(pii v : g[u]) if(pii(d[v.x], v.x) > pii(d[u], u)) {
        int pv = find(v.x);
        if(pv == u) continue;
        t[u].emplace_back(pv), t[pv].emplace_back(u);
        dsu[pv] = u;
    }
    dfs(vec.back(), 0);
    
    scanf("%d", &q);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", d[lca(a, b)]);
    }

    return 0;
}