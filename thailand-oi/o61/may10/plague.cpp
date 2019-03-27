#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

struct item {
    int key, prio, sz;
    item *l, *r;
    item(int key) : key(key), prio(rand()), sz(1), l(NULL), r(NULL) { }
};

typedef item* pitem;

int size(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) { if(t) t->sz = size(t->l) + 1 + size(t->r); }

void split(pitem t, pitem &l, pitem &r, int key) {
    if(!t) return void(l = r = NULL);
    if(t->key < key) split(t->r, t->r, r, key), l = t;
    else split(t->l, l, t->l, key), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if(!l || !r) return void(t = l ? l : r);
    if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updt(t);
}

void insert(pitem &t, int key) {
    pitem r;
    split(t, t, r, key);
    merge(t, t, new item(key));
    merge(t, t, r);
}

int get(pitem &t, int key) {
    int ret; pitem l;
    split(t, l, t, key);
    ret = size(t);
    merge(t, l, t);
    return ret; 
}

int n, m, sz[N], d[N][18];
int par[N], dep[N];
bitset<N> chk;
vector<int> g[N];
pitem t1[N], t2[N];

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(v != p && !chk[v]) sz[u] += getsz(v, u); return sz[u]; }

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int k) {
    for(int v : g[u]) if(v != p && !chk[v]) {
        d[v][k] = d[u][k] + 1;
        dfs(v, u, k);
    }
}

void centroid(int u, int p) {
    getsz(u, u);
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    par[u = ret.y] = p, dep[u] = dep[p] + 1, chk[u] = true;
    dfs(u, u, dep[u]);
    for(int v : g[u]) if(!chk[v]) centroid(v, u);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    centroid(1, 0);  
    for(int i = 1, T, a, b; i <= m; i++) {
        scanf("%d %d", &T, &a);
        if(T == 1) {
            scanf("%d", &b);
            insert(t1[a], b);
            for(int i = par[a], pv = a; i; pv = i, i = par[i]) if(b - d[a][dep[i]] >= 0)
                insert(t1[i], b - d[a][dep[i]]), insert(t2[pv], b - d[a][dep[i]]);
        } else {
            int ans = size(t1[a]);
            for(int i = par[a], pv = a; i; pv = i, i = par[i])
                ans += get(t1[i], b - d[a][dep[i]]) - get(t2[pv], b - d[a][dep[i]]);
            printf("%d\n", ans);
        }
    }

    return 0;
}