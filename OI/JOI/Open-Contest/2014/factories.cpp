#include "factories.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e5+5;

int n;
vector<pii> g[N];

int par[N], dep[N], sz[N];
long d[N][20];
bitset<N> chk;

int get_sz(int u, int p) {
    sz[u] = 1;
    for(pii v : g[u]) if(v.x != p && !chk[v.x])
        sz[u] += get_sz(v.x, u);
    return sz[u];
}

int find_cen(int u, int p, int all, int &ret) {
    int mx = all - sz[u];
    for(pii v : g[u]) if(v.x != p && !chk[v.x])
        mx = max(mx, find_cen(v.x, u, all, ret));
    if(mx <= (all + 1) / 2) ret = u;
    return sz[u];
}

void dfs(int u, int p, int i) {
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) {
        d[v.x][i] = d[u][i] + v.y;
        dfs(v.x, u, i);
    }
}

void process(int u, int p) {
    get_sz(u, u), find_cen(u, u, sz[u], u);
    dep[u] = dep[p] + 1, par[u] = p, chk[u] = 1;
    dfs(u, u, dep[u]);
    for(pii v : g[u]) if(!chk[v.x]) process(v.x, u);
}

long dp[N];

void update(int x, bool fill) {
    dp[x] = fill ? 0 : 1e18;
    for(int u = par[x]; u; u = par[u]) {
        if(fill) dp[u] = min(dp[u], d[x][dep[u]]);
        else dp[u] = 1e18;
    }
}

long query(int x) {
    long ret = dp[x];
    for(int u = par[x]; u; u = par[u])
        ret = min(ret, dp[u] + d[x][dep[u]]);
    return ret;
}

void Init(int _n, int A[], int B[], int D[]) {
    n = _n;
    for(int i = 0; i < n-1; i++) {
        g[++A[i]].emplace_back(++B[i], D[i]);
        g[B[i]].emplace_back(A[i], D[i]);
    }
    process(1, 0);

    fill_n(dp, N, 1e18);
}

long Query(int S, int X[], int T, int Y[]) {
    long ans = 1e18;

    for(int i = 0; i < S; i++) update(++X[i], 1);
    for(int i = 0; i < T; i++) ans = min(ans, query(++Y[i]));
    for(int i = 0; i < S; i++) update(X[i], 0);

    return ans;
}