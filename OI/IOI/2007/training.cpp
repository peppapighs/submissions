#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define long long long

using namespace std;

const int N = 1e3 + 5;

int n, m;
vector<int> g[N];
vector<iii> E, res[N];

int par[N][12], dep[N];

void pre_process(int u, int p) {
    dep[u] = dep[p] + 1, par[u][0] = p;
    for (int i = 1; i < 12; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            pre_process(v, u);
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 11; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 11; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

long ans, sum, dp[N][1 << 10];
int pos[N];

void dfs(int u, int p) {
    int mx = 1 << g[u].size();
    for (int i = 0; i < g[u].size(); i++)
        if (g[u][i] != p)
            pos[g[u][i]] = i;
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
            for (int i = 0; i < mx; i++)
                if (i >> pos[v] & 1)
                    dp[u][i] = max(dp[u][i], dp[u][i ^ (1 << pos[v])] +
                                                 dp[v][(1 << g[v].size()) - 1]);
        }
    for (iii e : res[u]) {
        int a, b, c;
        tie(a, b, c) = e;
        long sum_a = 0, sum_b = 0;
        int pv_a = -1, pv_b = -1;

        while (a != u) {
            int mx_a = (1 << g[a].size()) - 1;
            if (pv_a != -1)
                sum_a += dp[a][mx_a ^ (1 << pos[pv_a])];
            else
                sum_a += dp[a][mx_a];
            pv_a = a, a = par[a][0];
        }
        while (b != u) {
            int mx_b = (1 << g[b].size()) - 1;
            if (pv_b != -1)
                sum_b += dp[b][mx_b ^ (1 << pos[pv_b])];
            else
                sum_b += dp[b][mx_b];
            pv_b = b, b = par[b][0];
        }
        int x = 0;
        if (pv_a != -1)
            x ^= 1 << pos[pv_a];
        if (pv_b != -1)
            x ^= 1 << pos[pv_b];
        for (int i = 0; i < mx; i++)
            if ((x & i) == x)
                dp[u][i] = max(dp[u][i], dp[u][i ^ x] + sum_a + sum_b + c);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (!c)
            g[a].emplace_back(b), g[b].emplace_back(a);
        else
            E.emplace_back(a, b, c);
    }
    pre_process(1, 0);
    for (iii e : E) {
        int a, b, c;
        tie(a, b, c) = e;
        int l = lca(a, b), d = dep[a] + dep[b] - 2 * dep[l];
        if (d & 1)
            ans += c;
        else {
            res[l].emplace_back(a, b, c);
            sum += c;
        }
    }
    dfs(1, 0);
    printf("%lld\n", ans + sum - dp[1][(1 << g[1].size()) - 1]);

    return 0;
}
