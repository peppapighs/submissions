#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct node {
    int d;
    node *l, *r;
    node() {}
    node(int d, node *l, node *r) : d(d), l(l), r(r) {}
};

node *newleaf(int d) { return new node(d, nullptr, nullptr); }
node *newpar(node *l, node *r) { return new node(l->d + r->d, l, r); }

int n, m, A[N];
int par[N][17], dep[N];
vector<int> g[N], coord;
node *rot[N];

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

node *build(int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

node *update(int x, node *p, int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(p->d + 1);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(x, p->l, l, mid), p->r);
    else
        return newpar(p->l, update(x, p->r, mid + 1, r));
}

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i <= 16; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    rot[u] = update(get(A[u]), rot[p]);
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}

int query(int k, node *pu, node *pv, node *pl, node *pp, int add = 0, int l = 1,
          int r = coord.size()) {
    if (l == r)
        return l;
    int sum = add + pu->l->d + pv->l->d - pl->l->d - pp->l->d;
    int mid = (l + r) >> 1;
    if (sum >= k)
        return query(k, pu->l, pv->l, pl->l, pp->l, add, l, mid);
    else
        query(k, pu->r, pv->r, pl->r, pp->r, sum, mid + 1, r);
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 16; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 16; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i), coord.emplace_back(A[i]);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    rot[0] = build();
    dfs(1, 0);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        int l = lca(a, b);
        int ret = query(c, rot[a], rot[b], rot[l], rot[par[l][0]]);
        printf("%d\n", coord[ret - 1]);
    }

    return 0;
}