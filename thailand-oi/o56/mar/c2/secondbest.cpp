#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m;
int dsu[N], par[N][18], mx[N][18], dep[N];
long ans = LLONG_MAX, cost;
vector<pii> g[N];
vector<iii> mst, E;

int find(int x) { return dsu[x] == x ? x : find(dsu[x]); }

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i < 18; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[par[u][i - 1]][i - 1]);
    }
    for (pii v : g[u])
        if (v.x != p)
            mx[v.x][0] = v.y, dfs(v.x, u);
}

int lca(int a, int b) {
    int ret = 0;
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b]) {
            ret = max(ret, mx[a][i]);
            a = par[a][i];
        }
    if (a == b)
        return ret;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i]) {
            ret = max({ret, mx[a][i], mx[b][i]});
            a = par[a][i], b = par[b][i];
        }
    return max({ret, mx[a][0], mx[b][0]});
}

int main() {
    iota(dsu, dsu + N, 0);
    scanf("%d %d", &n, &m);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        mst.emplace_back(c, a, b);
    }
    sort(mst.begin(), mst.end());
    for (iii e : mst) {
        int a, b, c;
        tie(c, a, b) = e;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            cost += c;
            dsu[pa] = pb;
            g[a].emplace_back(b, c), g[b].emplace_back(a, c);
        } else
            E.emplace_back(a, b, c);
    }
    dfs(1, 0);
    long ans = LLONG_MAX;
    for (iii e : E) {
        int a, b, c;
        tie(a, b, c) = e;
        ans = min(ans, cost - lca(a, b) + c);
    }
    printf("%lld\n", ans);

    return 0;
}