#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, ans;
int par[N][18], dep[N], pre[N];
vector<int> g[N];

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
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

void get_ans(int u, int p) {
    for (int v : g[u])
        if (v != p) {
            get_ans(v, u);
            pre[u] += pre[v];
        }
    ans = max(ans, pre[u]);
}

int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(1, 0);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        int l = lca(a, b);
        ++pre[a], ++pre[b];
        --pre[l], --pre[par[l][0]];
    }
    get_ans(1, 0);
    printf("%d\n", ans);

    return 0;
}
