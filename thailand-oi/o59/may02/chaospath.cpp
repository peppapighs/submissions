#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
long A[N], ans;
vector<pii> g[N];

int pre(int u, int p) {
    int sz = 1;
    for(pii v : g[u]) if(v.x != p) {
        int z = pre(v.x, u);
        sz += z;
        A[v.y] = 1ll * z * (n - z);
    }
    return sz;
}

int sz[N], chk[N];
long cur;

int getsz(int u, int p) { sz[u] = 1; for(pii v : g[u]) if(v.x != p && !chk[v.x]) sz[u] += getsz(v.x, u); return sz[u]; }

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(pii v : g[u]) if(v.x != p && !chk[v.x])
        mx = max(mx, find_cen(v.x, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, long len, bool fill) {
    if(!fill) ans = max(ans, len + cur);
    else cur = max(cur, len);
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) dfs(v.x, u, len + A[v.y], fill);
}

void proc(int u) {
    getsz(u, u);
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    u = ret.y, cur = 0, chk[u] = true;
    for(pii v : g[u]) if(!chk[v.x]) {
        dfs(v.x, u, A[v.y], 0);
        dfs(v.x, u, A[v.y], 1);
    }
    for(pii v : g[u]) if(!chk[v.x]) proc(v.x);
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b, i), g[b].emplace_back(a, i);
    }
    pre(1, 1), proc(1);
    printf("%lld\n", ans);

    return 0;
}