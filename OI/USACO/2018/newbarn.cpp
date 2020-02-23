#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q;
vector<pii> ask;
vector<int> g[N];

int chk[N], sz[N], par[N], dep[N], d[N][20];

int get_sz(int u, int p) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p && !chk[v])
        sz[u] += get_sz(v, u);
    return sz[u];
}

int find_cen(int u, int p, int all, int &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, all, ret));
    if(mx * 2 <= all) ret = u;
    return sz[u];
}

void dfs(int u, int p, int i) {
    for(int v : g[u]) if(v != p && !chk[v]) {
        d[v][i] = d[u][i] + 1;
        dfs(v, u, i);
    }
}

void build(int u, int p) {
    get_sz(u, u);
    find_cen(u, u, sz[u], u);
    par[u] = p, dep[u] = dep[p] + 1, chk[u] = 1;
    dfs(u, u, dep[u]);
    for(int v : g[u]) if(!chk[v]) build(v, u);
}

int enable[N];
pii mx1[N], mx2[N];

int main() {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    fill_n(mx1, N, pii(-1, -1)), fill_n(mx2, N, pii(-1, -1));

    scanf("%d", &q);
    while(q--) {
        char T; int a;
        scanf(" %c %d", &T, &a);
        if(T == 'B') {
            ++n;
            if(a != -1) {
                g[a].emplace_back(n);
                g[n].emplace_back(a);
            }
            ask.emplace_back(0, n);
        } else ask.emplace_back(1, a);
    }
    for(int i = 1; i <= n; i++) if(!chk[i]) build(i, 0);
    for(pii a : ask) {
        int st = a.y;
        if(a.x == 0) {
            enable[st] = true;
            for(int u = par[st], pv = st; u; pv = u, u = par[u]) {
                pii now(d[st][dep[u]], pv);
                if(mx1[u].y == pv) mx1[u] = max(mx1[u], now), now = pii(-1, -1);
                if(mx2[u].y == pv) mx2[u] = max(mx2[u], now), now = pii(-1, -1);
                if(mx2[u] > mx1[u]) swap(mx1[u], mx2[u]);
                if(now > mx1[u]) swap(now, mx1[u]);
                if(now > mx2[u]) swap(now, mx2[u]);
            }
        } else {
            int ans = mx1[st] != pii(-1, -1) ? mx1[st].x : 0;
            for(int u = par[st], pv = st; u; pv = u, u = par[u]) if(enable[u]) {
                ans = max(ans, d[st][dep[u]]);
                if(mx1[u].y != pv && mx1[u].y != -1) ans = max(ans, d[st][dep[u]] + mx1[u].x);
                if(mx2[u].y != pv && mx2[u].y != -1) ans = max(ans, d[st][dep[u]] + mx2[u].x);
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}