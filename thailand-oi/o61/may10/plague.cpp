#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;
using namespace __gnu_pbds;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1e5+5;

int n, q, ptr, sz[N], chk[N];
int par[N], dep[N], d[N][18];
vector<int> g[N];
ordered_set<pii> S1[N], S2[N];

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

void build(int u, int p) {
    getsz(u, u);
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    par[u = ret.y] = p, dep[u] = dep[p] + 1, chk[u] = true;
    dfs(u, u, dep[u]);
    for(int v : g[u]) if(!chk[v]) build(v, u);
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    build(1, 0);
    for(int t = 1, T, a, b; t <= q; t++) {
        scanf("%d %d", &T, &a);
        if(T == 1) {
            scanf("%d", &b);
            S1[a].insert(pii(b, ++ptr));
            for(int i = par[a], pv = a; i; pv = i, i = par[i]) if(b - d[a][dep[i]] >= 0) {
                S1[i].insert(pii(b - d[a][dep[i]], ++ptr));
                S2[pv].insert(pii(b - d[a][dep[i]], ptr));
            }
        } else {
            int ret = S1[a].size();
            for(int i = par[a], pv = a; i; pv = i, i = par[i]) {
                ret += (S1[i].size() - S1[i].order_of_key(pii(d[a][dep[i]], 0)));
                ret -= (S2[pv].size() - S2[pv].order_of_key(pii(d[a][dep[i]], 0)));
            }
            printf("%d\n", ret);
        }
    }

    return 0;
}
