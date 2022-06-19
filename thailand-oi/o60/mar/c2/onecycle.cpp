#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e3 + 5;

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    friend bool operator<(const edge &a, const edge &b) { return a.w < b.w; }
};

int n;
int dsu[N], par[N][12], dep[N], dist[N];
vector<edge> E;
vector<pii> g[N];

int find(int x) { return dsu[x] = dsu[x] == x ? x : find(dsu[x]); }

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i < 12; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (pii v : g[u])
        if (v.x != p) {
            dist[v.x] = dist[u] + v.y;
            dfs(v.x, u);
        }
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 11; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 11; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

int d(int a, int b) { return dist[a] + dist[b] - 2 * dist[lca(a, b)]; }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            int w;
            scanf("%d", &w);
            if (i > j)
                continue;
            E.emplace_back(i, j, w);
        }
    }
    sort(E.begin(), E.end());
    int cnt = 0;
    for (edge e : E) {
        int pu = find(e.u), pv = find(e.v);
        if (pu != pv) {
            dsu[pu] = pv;
            cnt++;
            g[e.u].emplace_back(e.v, e.w), g[e.v].emplace_back(e.u, e.w);
        }
        if (cnt == n - 1)
            break;
    }
    dfs(1, 1);
    for (edge e : E)
        if (e.w < d(e.u, e.v)) {
            g[e.u].emplace_back(e.v, e.w), g[e.v].emplace_back(e.u, e.w);
            break;
        }
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
        for (pii p : g[i])
            if (i < p.x)
                printf("%d %d %d\n", i, p.x, p.y);
    }

    return 0;
}
