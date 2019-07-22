#include "radius.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

template<typename T>
struct segMax {
    T t[N << 1];
    void update(int x, T k) {
        for(t[x += N] = k; x != 1; x >>= 1)
            t[x>>1] = max(t[x], t[x^1]);
    }
    T query(int l, int r, T ret = -1e9) {
        for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = max(ret, t[l++]);
            if(r & 1) ret = max(ret, t[--r]);
        }
        return ret;
    }
};

int n, q;
vector<int> g[N];

int in[N], out[N], maxd[N];
int dep[N], spi[N], rot[N], par[N][18], pos[N], las[N];

int dfs(int u, int p) {
    static int idx = 0;
    in[u] = ++idx;
    dep[u] = dep[p] + 1, par[u][0] = p;
    for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        sz += z, ret = max(ret, pii(z, v));
        maxd[u] = max(maxd[u], maxd[v] + 1);
    }
    spi[u] = ret.y, out[u] = idx;
    return sz;
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    return par[a][0];
}

int d(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }

segMax<int> t1, t2;

void hld() {
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i][0]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx, las[i] = j;
    for(int i = 1; i <= n; i++) {
        t1.update(in[i], dep[i] - 1);
        int now = 0;
        for(int v : g[i]) if(v != par[i][0] && v != spi[i])
            now = max(now, maxd[v] + 1); 
        t2.update(pos[i], now - dep[i]);
    }
}

int walk(int a, int b) {
    int u = a, v = b, ret = maxd[a];
    while(rot[u] != rot[v]) {
        ret = max(ret, t2.query(pos[rot[u]], pos[u]-1) + dep[a]);
        int x = par[rot[u]][0], now = 0;
        for(int v : g[x]) if(v != par[x][0] && v != rot[u])
            now = max(now, maxd[v] + 1);
        ret = max(ret, dep[a] + now - dep[x]);
        u = x;
    }
    ret = max(ret, t2.query(pos[b], pos[u]-1) + dep[a]);
    return ret + 1;
}

vector<int> getRadius(int _n, int _q, vector<int> U, vector<int> V, vector<int> A) {
    n = _n, q = _q;
    for(int i = 0; i < n - 1; i++) {
        g[U[i]].emplace_back(V[i]);
        g[V[i]].emplace_back(U[i]);
    }
    dfs(1, 0), hld();

    vector<int> ans;
    for(int i = 0; i < q; i++) {
        int now = A[i], tmp = now;
        int ret = 0;
        for(int i = 17; ~i; i--) if(dep[par[tmp][i]] - 1 > d(now, par[tmp][i]))
            tmp = par[tmp][i];
        ret = max(t1.query(1, in[tmp]-1), t1.query(out[tmp]+1, n));
        ret = max(ret, walk(now, tmp));
        ans.emplace_back(ret);
    }
    return ans;
}