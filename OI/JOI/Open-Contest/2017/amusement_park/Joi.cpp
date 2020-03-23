#include "Joi.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

static const int N = 1e4+5;

static int par[N];

static int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

static vector<pii> t[N];
static vector<int> g[N];
static int idx, pre[N], pos[N], deg[N];

static void dfs(int u, int p) {
    pre[u] = idx++;
    for(int v : g[u]) if(v != p) dfs(v, u);
}

static void extend_tree(int u, int p) {
    if(!t[u].empty()) return;
    int leaf;
    vector<pii> tree = t[p];

    for(pii e : tree) ++deg[e.x], ++deg[e.y];
    for(pii e : tree) {
        int a, b; tie(a, b) = e;
        if(deg[a] == 1 && a != p) { leaf = a; break; }
        if(deg[b] == 1 && b != p) { leaf = b; break; }
    }
    pos[u] = pos[leaf];
    for(pii e : tree) {
        --deg[e.x], --deg[e.y];
        if(e.x == leaf || e.y == leaf) continue;
        t[u].emplace_back(e);
    }
    t[u].emplace_back(u, p);
    for(int v : g[u]) if(v != p) extend_tree(v, u);
}

static void solve(int n, int m, int A[], int B[]) {
    iota(par, par+N, 0);
    vector<pii> E, ret, init;

    for(int i = 0; i < m; i++) E.emplace_back(A[i], B[i]);
    sort(E.begin(), E.end());
    for(pii e : E) {
        int a, b; tie(a, b) = e;
        if(find(a) != find(b)) {
            par[find(a)] = find(b);
            g[a].emplace_back(b), g[b].emplace_back(a);
            ret.emplace_back(a, b);
        }
    }
    dfs(0, 0);
    for(pii e : ret) if(pre[e.x] < 60 && pre[e.y] < 60) init.emplace_back(e);
    for(int i = 0; i < n; i++) if(pre[i] < 60) {
        pos[i] = pre[i];
        t[i] = init;
    }
    for(int i = 0; i < n; i++) if(pre[i] < 60) for(int v : g[i]) extend_tree(v, i);
}

void Joi(int n, int m, int A[], int B[], long X, int T) {
    solve(n, m, A, B);

    for(int i = 0; i < n; i++) MessageBoard(i, X >> pos[i] & 1);
}
