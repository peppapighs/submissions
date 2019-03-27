#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

struct cht {
    struct line {
        long m, c;
        line(long m, long c) : m(m), c(c) { }
        long f(long x) { return m*x + c; }
    };
    vector<line> l;
    bool bad(line a, line b, line c) { return (c.c - a.c) * (a.m - b.m) <= (b.c - a.c) * (a.m - c.m); }
    void add(long m, long c) {
        line now(m, c);
        while(l.size() > 1 && bad(l[l.size() - 2], l[l.size() - 1], now)) l.pop_back();
        if(!l.empty()) {
            if(l.back().m == now.m && now.c <= l.back().c) l.pop_back();
            if(l.back().c == now.c && now.m <= l.back().m) l.pop_back();
        }
        l.emplace_back(now);
    }
    long query(long x) {
        if(l.empty()) return 1e18;
        int L = 0, R = l.size() - 1;
        while(L < R) {
            int mid = (L + R) >> 1;
            if(l[mid].f(x) < l[mid + 1].f(x)) R = mid;
            else L = mid + 1;
        }
        return l[R].f(x);
    }
} hull[N];

int n, k;
int sz[N], chk[N], par[N], dep[N], d[N][18];
vector<int> g[N];
vector<pii> vec;

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(v != p && !chk[v]) sz[u] += getsz(v, u); return sz[u]; }

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int i) {
    for(int v : g[u]) if(v != p && !chk[v]) {
        d[v][i] = d[u][i] + 1;
        dfs(v, u, i);
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
    scanf("%d %d", &n, &k);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for(int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        vec.emplace_back(b, a);
    }
    centroid(1, 0);
    sort(vec.begin(), vec.end(), greater<pii>());
    for(pii v : vec) {
        int a = v.y, b = v.x;
        hull[a].add(b, 0);
        for(int i = par[a]; i; i = par[i])
            hull[i].add(b, 1ll * b * d[a][dep[i]]);
    }
    long ans = 0;
    for(int a = 1; a <= n; a++) {
        long ret = hull[a].query(0);
        for(int i = par[a]; i; i = par[i]) 
            ret = min(ret, hull[i].query(d[a][dep[i]]));
        ans = max(ans, ret);
    }
    printf("%lld\n", ans);

    return 0;
}