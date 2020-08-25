#include "swap.h"
#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 3e5 + 5;

int dsu[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int n, m, ptr;
int cost[N], deg[N], has_3[N], has_cycle[N], par[N][20], dep[N];
vector<int> g[N];

void onion(int a, int b) {
    has_3[ptr] = has_3[find(a)] | has_3[find(b)]; 
    has_cycle[ptr] = has_cycle[find(a)] | has_cycle[find(b)]; 

    if(deg[a] >= 3 || deg[b] >= 3) has_3[ptr] = 1;

    g[ptr].emplace_back(find(a));
    if(find(a) == find(b)) has_cycle[ptr] = 1;
    else g[ptr].emplace_back(find(b));

    dsu[find(a)] = dsu[find(b)] = ptr;
}

void dfs(int u, int p) {
    dep[u] = dep[p] + 1, par[u][0] = p;
    for(int i = 1; i <= 19; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    for(int v : g[u]) {
        dfs(v, u);
        has_3[u] |= has_3[v], has_cycle[u] |= has_cycle[v];
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 19; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 19; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    return par[a][0];
}

void init(int _n, int _m, vector<int> U, vector<int> V, vector<int> W) {
    n = ptr = _n, m = _m;
    iota(dsu, dsu + N, 0);

    vector<iii> E;
    for(int i = 0; i < m; i++) E.emplace_back(W[i], ++U[i], ++V[i]);

    sort(E.begin(), E.end());
    for(int i = 0; i < m; i++) {
        int u, v, w; tie(w, u, v) = E[i];
        cost[++ptr] = w, ++deg[u], ++deg[v];
        onion(u, v);
    }
    cost[0] = -1, has_3[0] = has_cycle[0] = 1;
    dfs(ptr, 0);
}

int getMinimumFuelCapacity(int a, int b) {
    int l = lca(++a, ++b);

    if(has_3[l] || has_cycle[l]) return cost[l];
    for(int i = 19; ~i; i--) if(!has_3[par[l][i]] && !has_cycle[par[l][i]])
        l = par[l][i];
    return cost[par[l][0]];
}
