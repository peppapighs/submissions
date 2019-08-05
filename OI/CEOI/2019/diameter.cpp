#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

#define var int p = 1, int l = 1, int r = N
#define mid (l + r >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

const int N = 1<<17;

template<typename X>
struct seg_lazy {
    X t[N<<1];
    long lz[N<<1];
    
    void merge(pii &a, long b) { a.x += b; }
    void merge(long &a, long b) { a += b; }

    void push(var) {
        if(!lz[p]) return;
        merge(t[p], lz[p]);
        if(l != r) lz[p<<1] += lz[p], lz[p<<1|1] += lz[p];
        lz[p] = 0;
    }

    template<typename T>
    void travel(int x, int y, const T &f, var) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) return f(p, l, r);
        travel(x, y, f, lb), travel(x, y, f, rb);
        t[p] = max(t[p<<1], t[p<<1|1]);
    }
};

seg_lazy<pii> lazy;
seg_lazy<long> tmx;

int n, q;
long w;
vector<pii> g[N];
set<pii> S1[N], S2[N];

int in[N], out[N], par[N], dep[N], pos[N], mxp[N], spi[N], rot[N];
long d[N], dp[N];

int dfs(int u, int p) {
    static int idx = 0;
    in[u] = ++idx;
    par[u] = p, dep[u] = dep[p] + 1;

    int sz = 1; pii ret(0, -1);
    for(pii v : g[u]) if(v.x != p) {
        d[v.x] = d[u] + v.y;
        int z = dfs(v.x, u);
        dp[u] = max(dp[u], dp[v.x] + v.y);
        sz += z, ret = max(ret, pii(z, v.x));
    }
    spi[u] = ret.y, out[u] = idx;
    return sz;
}

void hld_upd(int u) {
    while(u) {
        int nex = par[rot[u]];
        long dp, now = 0;
        lazy.travel(in[nex], in[nex], [&](var) { dp = lazy.t[p].x; });
        lazy.travel(in[rot[u]], out[rot[u]], [&](var) { now = max(now, lazy.t[p].x); });

        pii p = *S2[nex].lower_bound(pii(rot[u], -1e18));

        S2[nex].erase(p), S2[nex].emplace(pii(rot[u], now - dp));
        S1[nex].erase(pii(p.y, p.x)), S1[nex].emplace(pii(now - dp, rot[u])); 

        tmx.travel(pos[nex], pos[nex], [&](var) { tmx.t[p] = S1[nex].rbegin()->x - dp; });
        u = nex;
    }
}

long hld_que(int u) {
    long dp, ret = -1e18;
    lazy.travel(in[u], in[u], [&](var) { dp = lazy.t[p].x; });
    lazy.travel(in[u], out[u], [&](var) { ret = max(ret, lazy.t[p].x - 2ll * dp); });
    while(u) {
        long tdp, now = -1e8;
        lazy.travel(in[par[rot[u]]], in[par[rot[u]]], [&](var) { tdp = lazy.t[p].x; });
        lazy.travel(in[par[rot[u]]], in[rot[u]]-1, [&](var) { now = max(now, lazy.t[p].x - 2ll * tdp); });
        lazy.travel(out[rot[u]]+1 , out[par[rot[u]]], [&](var) { now = max(now, lazy.t[p].x - 2ll * tdp); });
        tmx.travel(pos[rot[u]], pos[u]-1, [&](var) { now = max(now, tmx.t[p]); });
        ret = max(ret, now);
        u = par[rot[u]];
    }
    return ret;
}

void gen_tree() {
    function<int(int, int, int)> get = [&](int u, int p, int r) {
        static int idx = 0;
        pos[u] = mxp[u] = ++idx, rot[u] = r;
        for(pii v : g[u]) if(v.x != p && v.x != spi[u]) {
            S1[u].emplace(dp[v.x], v.x);
            S2[u].emplace(v.x, dp[v.x]);
        }
        if(spi[u] != -1) mxp[u] = max(mxp[u], get(spi[u], u, r));
        for(pii v : g[u]) if(v.x != p && v.x != spi[u])
            mxp[u] = max(mxp[u], get(v.x, u, v.x));
        return mxp[u];
    };
    get(1, 0, 1);
    for(int i = 1; i <= n; i++) lazy.travel(in[i], in[i], [&](var) { lazy.t[p] = pii(d[i], i); });
    for(int i = 1; i <= n; i++) tmx.travel(pos[i], pos[i], [&](var) { tmx.t[p] = -d[i]; });
    for(int i = 1; i <= n; i++) hld_upd(i);
}

long get_diameter() {
    pii a(0, 0);
    lazy.travel(1, n, [&](var) { a = max(a, lazy.t[p]); });
    return hld_que(a.y) + a.x;
}

vector<pii> E;
long cost[N];

int main() {
    scanf("%d %d %lld", &n, &q, &w);
    for(int i = 1; i < n; i++) {
        int a, b; long c;
        scanf("%d %d %lld", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
        E.emplace_back(a, b), cost[i-1] = c;
    }
    dfs(1, 0), gen_tree();
    for(pii &e : E) if(dep[e.x] < dep[e.y]) swap(e.x, e.y);

    long last = 0;
    for(int i = 1; i <= q; i++) {
        int d; long e;
        scanf("%d %lld", &d, &e);
        d = (d + last) % (n - 1);
        e = (e + last ) % w;
        int u = E[d].x;
        lazy.travel(in[u], out[u], [&](var) {
            lazy.lz[p] += e - cost[d];
            lazy.push(p, l, r);
        });
        tmx.travel(pos[u], mxp[u], [&](var) {
            tmx.lz[p] -= e - cost[d];
            tmx.push(p, l, r);
        });

        hld_upd(u);
        cost[d] = e;
        last = get_diameter();
        printf("%lld\n", last);
    }

    return 0;
}