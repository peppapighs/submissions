#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, s, q, e;
int u[N], v[N], w[N], in[N], out[N], pos[N];
int par[N][18], dep[N];
long d[N], dp[N], pre[N][18];
bitset<N> shop;
vector<pii> g[N];

void gen_lca(int u, int p) {
    static int idx = 0;
    in[u] = ++idx, pos[idx] = u;
    dep[u] = dep[p] + 1, par[u][0] = p;
    if (shop[u])
        dp[u] = d[u];
    for (pii v : g[u])
        if (v.x != p) {
            d[v.x] = d[u] + v.y;
            gen_lca(v.x, u);
            dp[u] = min(dp[u], dp[v.x]);
        }
    out[u] = idx;
}

int main() {
    fill_n(dp, N, 1e18), fill_n(pre[0], N * 18, 1e18);
    scanf("%d %d %d %d", &n, &s, &q, &e);
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", u + i, v + i, w + i);
        g[u[i]].emplace_back(v[i], w[i]);
        g[v[i]].emplace_back(u[i], w[i]);
    }
    for (int i = 1, a; i <= s; i++)
        scanf("%d", &a), shop[a] = true;
    gen_lca(e, 0);
    for (int i = 1; i <= n; i++)
        if (dp[i] != 1e18)
            pre[i][0] = dp[i] - 2 * d[i];
    for (int t = 1; t <= n; t++) {
        int u = pos[t];
        for (int i = 1; i <= 17; i++) {
            par[u][i] = par[par[u][i - 1]][i - 1];
            pre[u][i] = min(pre[u][i - 1], pre[par[u][i - 1]][i - 1]);
        }
    }
    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        int now = dep[u[a]] > dep[v[a]] ? u[a] : v[a];
        if (in[now] > in[b] || out[b] > out[now]) {
            printf("escaped\n");
            continue;
        }
        int dist = dep[b] - dep[now], u = b;
        long ans = 1e18;
        for (int i = 17; ~i; i--)
            if (dist >> i & 1) {
                ans = min(ans, pre[u][i]);
                u = par[u][i];
            }
        ans = min(ans, pre[u][0]);
        if (ans >= 1e18)
            printf("oo\n");
        else
            printf("%lld\n", ans + d[b]);
    }

    return 0;
}