#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, q;
int pre[N], low[N], ap[N], id[N];
vector<vector<int>> g(N), bcc;
vector<int> sz;

void tarjan(int u, int p) {
    static int idx = 0;
    static stack<int> S;
    pre[u] = low[u] = ++idx, S.emplace(u);
    int cnt = 0;
    for (int v : g[u])
        if (v != p) {
            if (!pre[v]) {
                ++cnt;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if ((!p && cnt > 1) || (p && low[v] >= pre[u]))
                    ap[u] = true;
                if (low[v] >= pre[u]) {
                    bcc.emplace_back(vector<int>(1, u));
                    while (bcc.back().back() != v) {
                        bcc.back().emplace_back(S.top());
                        S.pop();
                    }
                }
            } else
                low[u] = min(low[u], pre[v]);
        }
}

bitset<N> idart;

void gen_bct() {
    g.clear();
    g.emplace_back(vector<int>());
    sz.emplace_back(0);
    for (int i = 1; i <= n; i++)
        if (ap[i]) {
            idart[id[i] = g.size()] = true;
            g.emplace_back(vector<int>());
            sz.emplace_back(1);
        }
    for (vector<int> &cc : bcc) {
        g.emplace_back(vector<int>());
        sz.emplace_back(cc.size());
        for (int v : cc) {
            if (ap[v])
                g[id[v]].emplace_back(g.size() - 1),
                    g[g.size() - 1].emplace_back(id[v]);
            else
                id[v] = g.size() - 1;
        }
    }
}

int par[N][18], sum[N], dep[N];

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    sum[u] = sum[p] + (sz[u] - 2 * !idart[u]);
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

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    tarjan(1, 0);
    gen_bct();
    dfs(1, 0);

    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        a = id[a], b = id[b];
        if (a == b)
            printf("%d\n", sz[a] - 2);
        else {
            int lc = lca(a, b);
            int ans = sum[a] + sum[b] - sum[lc] - sum[par[lc][0]];
            ans -= (idart[a] + idart[b]);
            printf("%d\n", ans);
        }
    }

    return 0;
}