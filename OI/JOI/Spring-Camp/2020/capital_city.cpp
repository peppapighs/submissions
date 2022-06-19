#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, k, ans = 1e9;
int C[N], cnt[N];
vector<int> g[N];

int sz[N];
bitset<N> chk;

int get_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u])
        if (v != p && !chk[v])
            sz[u] += get_sz(v, u);
    return sz[u];
}

int find_cen(int u, int p, int all, int &ret) {
    int mx = all - sz[u];
    for (int v : g[u])
        if (v != p && !chk[v])
            mx = max(mx, find_cen(v, u, all, ret));
    if (mx <= (all + 1) / 2)
        ret = u;
    return sz[u];
}

int par[N], used[N];
vector<int> col[N];
queue<int> Q;

void dfs(int u, int p, bool fill) {
    if (fill)
        col[C[u]].emplace_back(u), par[u] = p;
    else
        col[C[u]].clear(), used[C[u]] = 0;
    for (int v : g[u])
        if (v != p && !chk[v])
            dfs(v, u, fill);
}

void process(int u) {
    get_sz(u, u), find_cen(u, u, sz[u], u);
    dfs(u, 0, 1);

    int ret = 1;
    bool valid = true;
    Q.emplace(C[u]), used[C[u]] = 1;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        if (col[now].size() != cnt[now]) {
            valid = false;
            break;
        }
        for (int x : col[now])
            if (x != u && !used[C[par[x]]]) {
                used[C[par[x]]] = 1, ++ret;
                Q.emplace(C[par[x]]);
            }
    }
    if (valid)
        ans = min(ans, ret);

    dfs(u, 0, 0), chk[u] = 1;
    for (int v : g[u])
        if (!chk[v])
            process(v);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", C + i), ++cnt[C[i]];
    process(1);

    printf("%d\n", ans - 1);

    return 0;
}