#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

long ans[N];
vector<int> coord;

struct item {
    pii val;
    int l, r;
    item() {}
    item(pii val, int l, int r) : val(val), l(l), r(r) {}
} t[9 * N];

long f(int x, pii l) { return 1ll * l.x * x + ans[l.y]; };

int ptr;

int newleaf(pii x) {
    t[++ptr].val = x;
    t[ptr].l = -1, t[ptr].r = -1;
    return ptr;
}

int newpar(pii x, int l, int r) {
    t[++ptr].val = x;
    t[ptr].l = l, t[ptr].r = r;
    return ptr;
}

int m, L, M, R;

int add(pii k, int p, int l = 1, int r = coord.size()) {
    m = (l + r) >> 1;
    L = coord[l-1], M = coord[m-1], R = coord[r-1];
    if(p == -1 || p > ptr) return newleaf(k);
    if(f(L, k) <= f(L, t[p].val) && f(R, k) <= f(R, t[p].val)) return newpar(k, t[p].l, t[p].r);
    if(f(L, k) >= f(L, t[p].val) && f(R, k) >= f(R, t[p].val)) return p;

    bool lef = f(L, k) < f(L, t[p].val);
    bool mid = f(M, k) < f(M, t[p].val);
    pii ret = t[p].val;
    if(mid) swap(ret, k);
    if(lef != mid) return newpar(ret, add(k, t[p].l, l, m), t[p].r);
    else return newpar(ret, t[p].l, add(k, t[p].r, m + 1, r));
}

long get(int x, int p, int l = 1, int r = coord.size()) {
    m = (l + r) >> 1;
    L = coord[l-1], M = coord[m-1], R = coord[r-1];
    if(p == -1 || p > ptr) return 1e18;
    if(x <= M) return min(f(x, t[p].val), get(x, t[p].l, l, m));
    else return min(f(x, t[p].val), get(x, t[p].r, m + 1, r));
}

int n;
vector<pii> g[N];
int S[N], V[N], ver[N];

void dfs(int u, int p, int d) {
    if(u != 1) ans[u] = get(V[u], ver[p]) + 1ll * d * V[u] + S[u];
    if(u != 1) ver[u] = add(pii(-d, u), ver[p]);
    else ver[u] = newleaf(pii(0, 0));

    for(pii v : g[u]) if(v.x != p) dfs(v.x, u, d + v.y);

    ptr = ver[u];
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    for(int i = 2; i <= n; i++) {
        scanf("%d %d", S + i, V + i);
        coord.emplace_back(V[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    dfs(1, 0, 0);

    for(int i = 2; i <= n; i++) printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}