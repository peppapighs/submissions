#include "beauty.h"
#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, q;
int a[N];
vector<vector<int>> g(N), cc;

int pre[N], low[N];
bitset<N> art;

void tarjan(int u, int p) {
    static int idx = 0;
    static stack<int> S;

    pre[u] = low[u] = ++idx;
    S.emplace(u);
    int child = 0;
    for (int v : g[u])
        if (v != p) {
            if (!pre[v]) {
                ++child;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if ((!p && child > 1) || (p && low[v] >= pre[u]))
                    art[u] = true;
                if (low[v] >= pre[u]) {
                    cc.emplace_back(vector<int>(1, u));
                    while (cc.back().back() != v) {
                        cc.back().emplace_back(S.top());
                        S.pop();
                    }
                }
            } else
                low[u] = min(low[u], pre[v]);
        }
}

bitset<N> idart;
int id[N], cost[N];

void gen_bct() {
    g.clear();
    g.emplace_back(vector<int>());
    for (int i = 1; i <= n; i++)
        if (art[i]) {
            idart[id[i] = g.size()] = true;
            cost[id[i]] = a[i];
            g.emplace_back(vector<int>());
        }
    for (vector<int> &c : cc) {
        g.emplace_back(vector<int>());
        for (int v : c) {
            if (art[v])
                g[g.size() - 1].emplace_back(id[v]),
                    g[id[v]].emplace_back(g.size() - 1);
            else
                id[v] = g.size() - 1;
            cost[g.size() - 1] = max(cost[g.size() - 1], a[v]);
        }
    }
}

int dep[N], par[N][18], mx[N][18];

void gen_lca(int u, int p) {
    dep[u] = dep[p] + 1, par[u][0] = p, mx[u][0] = cost[u];
    for (int i = 1; i <= 17; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[par[u][i - 1]][i - 1]);
    }
    for (int v : g[u])
        if (v != p)
            gen_lca(v, u);
}

int solve(int a, int b) {
    int ret = 0;
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b]) {
            ret = max(ret, mx[a][i]);
            a = par[a][i];
        }
    if (a == b)
        return max(ret, mx[a][0]);
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i]) {
            ret = max({ret, mx[a][i], mx[b][i]});
            a = par[a][i], b = par[b][i];
        }
    return max({ret, mx[a][1], mx[b][1]});
}

vector<int> getMaximumBeauty(int _n, int _m, int _q, vector<int> T,
                             vector<int> U, vector<int> V, vector<int> A,
                             vector<int> B) {
    n = _n, m = _m, q = _q;

    for (int i = 1; i <= n; i++)
        a[i] = T[i - 1];
    for (int i = 0; i < m; i++)
        g[U[i]].emplace_back(V[i]), g[V[i]].emplace_back(U[i]);
    tarjan(1, 0), gen_bct(), gen_lca(1, 0);

    vector<int> ans;
    for (int i = 0; i < q; i++) {
        if (id[A[i]] == id[B[i]])
            ans.emplace_back(cost[id[A[i]]]);
        else
            ans.emplace_back(solve(id[A[i]], id[B[i]]));
    }
    return ans;
}
