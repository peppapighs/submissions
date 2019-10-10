#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

struct PersistentLiChaoTree {
    struct item {
        pii val;
        item *l, *r;
        item(pii val, item *l, item *r) : val(val), l(l), r(r) {}
    };
    item *ver[N];

    long f(long x, pii l) { return l.x * x + l.y; }

    item* newleaf(pii val) { return new item(val, NULL, NULL); }
    item* newpar(pii val, item* l, item *r) { return new item(val, l, r); }

    item* update(pii k, item *p, int l = 1, int r = 1e9) {
        if(!p) return newleaf(k);

        if(f(l, k) < f(l, p->val) && f(r, k) < f(r, p->val)) return newpar(k, p->l, p->r);
        if(f(l, k) > f(l, p->val) && f(r, k) > f(r, p->val)) return p;

        int m = (l + r) >> 1;
        bool lef = f(l, k) < f(l, p->val);
        bool mid = f(m, k) < f(m, p->val);

        if(l == r) return newleaf(mid ? k : p->val);
        if(lef != mid) return newpar(mid ? k : p->val, update(mid ? p->val : k, p->l, l, m), p->r);
        else return newpar(mid ? k : p->val, p->l, update(mid ? p->val : k, p->r, m+1, r));
    }

    long get(int x, item *p, int l = 1, int r = 1e9) {
        int m = (l + r) >> 1;
        if(!p) return 1e18;
        if(l == r) return f(x, p->val);
        if(x < m) return min(f(x, p->val), get(x, p->l, l, m));
        else return min(f(x, p->val), get(x, p->r, m+1, r));
    }
} t;

int n;
vector<pii> g[N];
long S[N], V[N], d[N], ans[N];

void dfs(int u, int p) {
    if(u != 1) ans[u] = t.get(V[u], t.ver[p]) + V[u] * d[u] + S[u];
    if(u != 1) t.ver[u] = t.update(pii(-d[u], ans[u]), t.ver[p]);
    else t.ver[u] = t.newleaf(pii(0, 0));
    for(pii v : g[u]) if(v.x != p) {
        d[v.x] = d[u] + v.y;
        dfs(v.x, u);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    for(int i = 2; i <= n; i++) scanf("%lld %lld", S+i, V+i);
    dfs(1, 1);

    for(int i = 2; i <= n; i++) printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}