#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

struct SegmentTree {
    int t[N << 1];

    void update(int x, int k) {
        for(t[x += N] = k; x != 1; x >>= 1)
            t[x >> 1] = max(t[x], t[x ^ 1]);
    }

    int query(int l, int r) {
        int ret = 0;
        for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = max(ret, t[l++]);
            if(r & 1) ret = max(ret, t[--r]);
        }
        return ret;
    }
} tree;

int n;
int ans[N];
vector<int> g[N];

int all;
int sz[N], chk[N];

int get_sz(int u, int p) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p && !chk[v])
        sz[u] += get_sz(v, u);
    return sz[u];
}

int find_cen(int u, int p, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

int dfs(int u, int p, int dist, bool fill) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p && !chk[v])
        sz[u] += dfs(v, u, dist + 1, fill);

    if(!fill) {
        if(tree.query(sz[u], all) != -1e9)
            ans[sz[u]] = max(ans[sz[u]], dist + tree.query(sz[u], all) + 1);
        if(sz[u] <= all - sz[u])
            ans[sz[u]] = max(ans[sz[u]], dist + 1);
    } else if(dist > tree.t[sz[u] + N])
        tree.update(sz[u], dist);

    return sz[u];
}

void centroid(int u) {
    get_sz(u, u);

    all = sz[u];

    pii ret(all + 1, -1);
    find_cen(u, u, ret);
    u = ret.y;

    for(int i = 1; i <= all; i++)
        tree.update(i, -1e9);
    for(int v : g[u]) if(!chk[v]) {
        dfs(v, u, 1, 0);
        dfs(v, u, 1, 1);
    }
    for(int i = 1; i <= all; i++)
        tree.update(i, -1e9);
    for(auto it = g[u].rbegin(); it != g[u].rend(); it++) if(!chk[*it]) {
        dfs(*it, u, 1, 0);
        dfs(*it, u, 1, 1);
    }

    chk[u] = 1;
    for(int v : g[u]) if(!chk[v])
        centroid(v);
}

int main() {
    fill_n(ans, N, 1);

    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    centroid(1);

    for(int i = n / 2; i; i--)
        ans[i] = max(ans[i], ans[i + 1]);

    for(int i = 1; i <= n; i++) {
        if(i & 1) printf("1\n");
        else printf("%d\n", ans[i / 2]);
    }

    return 0;
}