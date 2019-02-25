#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6+5;

int n, ans[N];
int in[N], out[N], pos[N], hv[N], dep[N], cnt[N];
pii mx[N];
vector<int> g[N];

int gethv(int u, int p) {
    static int idx = 0;
    int sz = 1; pii ret(0, -1);
    in[u] = ++idx, pos[idx] = u, dep[u] = dep[p] + 1;
    for(int v : g[u]) if(v != p) {
        int z = gethv(v, u);
        sz += z, ret = max(ret, pii(z, v));
    }
    hv[u] = ret.y, out[u] = idx;
    return sz;
}

void add(int u, int lca) {
    ++cnt[dep[u]];
    mx[lca] = max(mx[lca], pii(cnt[dep[u]], -dep[u]));
}

void dfs(int u, int p, bool keep) {
    for(int v : g[u]) if(v != p && v != hv[u]) dfs(v, u, 0);
    if(hv[u] != -1) dfs(hv[u], u, 1);
    mx[u] = mx[hv[u]], add(u, u);
    for(int v : g[u]) if(v != p && v != hv[u])
        for(int i = in[v]; i <= out[v]; i++) add(pos[i], u);
    ans[u] = -(dep[u] + mx[u].y);
    if(!keep) for(int i = in[u]; i <= out[u]; i++) --cnt[dep[pos[i]]];
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    gethv(1, 1);
    dfs(1, 1, 1);
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);

    return 0;
}