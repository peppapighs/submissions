#include "catdog.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;
const int INF = 1e9 + 1;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

struct node {
    vector<int> v;
    node() {
        v = vector<int>(4, INF);
        v[0] = v[3] = 0;
    }
    node(int a) { v = vector<int>(4, a); }
    int ans() {
        int ret = INF;
        for (int i = 0; i < 4; i++)
            ret = min(ret, v[i]);
        return ret;
    }
    friend node operator+(const node &a, const node &b) {
        node ret(INF);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                int bit = (i & 2) + (j & 1);
                bool dif = (i & 1) != (j >> 1 & 1);
                ret.v[bit] = min(ret.v[bit], a.v[i] + b.v[j] + dif);
            }
        return ret;
    }
} t[N << 1];

int n, col[N];
int par[N], rot[N], spi[N], pos[N], lev[N];
pii pv[N];
vector<int> g[N];

int dfs(int u, int p) {
    par[u] = p;
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u])
        if (v != p) {
            int z = dfs(v, u);
            sz += z, ret = max(ret, pii(z, v));
        }
    spi[u] = ret.y;
    return sz;
}

void build(var) {
    if (l == r)
        return;
    build(lb), build(rb);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void update(int x, pii k, var) {
    if (l == r) {
        t[p].v[0] += k.x, t[p].v[3] += k.y;
        return;
    }
    if (x <= mid)
        update(x, k, lb);
    else
        update(x, k, rb);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

node query(int x, int y, var) {
    if (x <= l && r <= y)
        return t[p];
    if (y <= mid)
        return query(x, y, lb);
    if (x > mid)
        return query(x, y, rb);
    return query(x, y, lb) + query(x, y, rb);
}

void hld() {
    for (int i = 1, idx = 0; i <= n; i++)
        if (spi[par[i]] != i)
            for (int j = i; j != -1; j = spi[j])
                rot[j] = i, lev[i] = j, pos[j] = ++idx;
    build();
}

void initialize(int _n, vector<int> A, vector<int> B) {
    n = _n;
    for (int i = 0; i < n - 1; i++) {
        g[A[i]].emplace_back(B[i]);
        g[B[i]].emplace_back(A[i]);
    }
    dfs(1, 0), hld();
}

void update(int v, int a, int b) {
    while (v) {
        update(pos[v], pii(a, b));
        node now = query(pos[rot[v]], pos[lev[rot[v]]]);
        int x = min(now.v[0], now.v[1]), y = min(now.v[2], now.v[3]);
        pii upd(min(x, y + 1), min(x + 1, y));
        a = upd.x - pv[rot[v]].x, b = upd.y - pv[rot[v]].y;
        pv[rot[v]] = upd;
        v = par[rot[v]];
    }
}

int cat(int v) {
    col[v] = 1;
    update(v, 0, INF);
    return query(pos[1], pos[lev[1]]).ans();
}

int dog(int v) {
    col[v] = 2;
    update(v, INF, 0);
    return query(pos[1], pos[lev[1]]).ans();
}

int neighbor(int v) {
    if (col[v] == 1)
        update(v, 0, -INF);
    if (col[v] == 2)
        update(v, -INF, 0);
    col[v] = 0;
    return query(pos[1], pos[lev[1]]).ans();
}