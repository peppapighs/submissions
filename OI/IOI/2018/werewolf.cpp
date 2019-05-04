#include "werewolf.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, m, q;

struct node {
    int d;
    node *l, *r;
    node(int d, node *l, node *r) : d(d), l(l), r(r) { }
};

node* newleaf(int d) { return new node(d, nullptr, nullptr); }
node* newpar(node *l, node *r) { return new node(l->d + r->d, l, r); }

node* build(int l = 1, int r = n) {
    if(l == r) return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid+1, r));
}

node* update(node *p, int x, int l = 1, int r = n) {
    if(l == r) return newleaf(p->d + 1);
    int mid = (l + r) >> 1;
    if(x <= mid) return newpar(update(p->l, x, l, mid), p->r);
    else return newpar(p->l, update(p->r, x, mid+1, r));
}

int query(node *pl, node *pr, int x, int y, int l = 1, int r = n) {
    if(x > r || l > y) return 0;
    if(x <= l && r <= y) return pr->d - pl->d;
    int mid = (l + r) >> 1;
    return query(pl->l, pr->l, x, y, l, mid) + query(pl->r, pr->r, x, y, mid+1, r);
}

node* t[N];

int dsu[N], hpar[N][18], wpar[N][18];
int hin[N], hout[N], hpos[N];
int win[N], wout[N], wpos[N];
vector<int> g[N], hg[N], wg[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

void gen_human(int u, int p) {
    static int hidx = 0;
    hin[u] = ++hidx, hpos[hidx] = u;
    hpar[u][0] = p;
    for(int i = 1; i <= 17; i++) hpar[u][i] = hpar[hpar[u][i-1]][i-1];
    for(int v : hg[u]) if(v != p) gen_human(v, u);
    hout[u] = hidx;
}

void gen_werewolf(int u, int p) {
    static int widx = 0;
    win[u] = ++widx, wpos[widx] = u;
    wpar[u][0] = p;
    for(int i = 1; i <= 17; i++) wpar[u][i] = wpar[wpar[u][i-1]][i-1];
    for(int v : wg[u]) if(v != p) gen_werewolf(v, u);
    wout[u] = widx;
}

vector<int> check_validity(int _n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
    n = _n, m = X.size(), q = S.size();

    for(int i = 0; i < m; i++) {
        g[X[i]+1].emplace_back(Y[i]+1);
        g[Y[i]+1].emplace_back(X[i]+1);
    }
    iota(dsu, dsu+N, 0);
    for(int u = n; u; u--) for(int v : g[u]) if(v > u) {
        int pv = find(v);
        if(pv == u) continue;
        hg[u].emplace_back(pv), hg[pv].emplace_back(u);
        dsu[pv] = u;
    }
    iota(dsu, dsu+N, 0);
    for(int u = 1; u <= n; u++) for(int v : g[u]) if(v < u) {
        int pv = find(v);
        if(pv == u) continue;
        wg[u].emplace_back(pv), wg[pv].emplace_back(u);
        dsu[pv] = u;
    }

    gen_human(1, 0), gen_werewolf(n, 0);
    t[0] = build();
    for(int i = 1; i <= n; i++) t[i] = update(t[i-1], win[hpos[i]]);

    vector<int> ret;
    for(int T = 0; T < q; T++) {
        int s = S[T]+1, e = E[T]+1;
        for(int i = 17; ~i; i--) if(hpar[s][i] && hpar[s][i] >= L[T]+1) s = hpar[s][i];
        for(int i = 17; ~i; i--) if(wpar[e][i] && wpar[e][i] <= R[T]+1) e = wpar[e][i];
        if(query(t[hin[s]-1], t[hout[s]], win[e], wout[e])) ret.emplace_back(1);
        else ret.emplace_back(0);
    }

    return ret;
}