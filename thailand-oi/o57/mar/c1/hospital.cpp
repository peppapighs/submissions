#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n;
long sz[N], dp[N], ans = LLONG_MAX;
vector<int> g[N];

int proc(int u, int p) {
    sz[u] = 1;
    for (int v : g[u])
        if (v != p) {
            sz[u] += proc(v, u);
            dp[u] += dp[v] + sz[v];
        }
    return sz[u];
}

void dfs(int u, int p, long k, int z) {
    ans = min(ans, dp[u] + k);
    for (int v : g[u])
        if (v != p)
            dfs(v, u, k + dp[u] - (dp[v] + sz[v]) + (sz[u] - sz[v]) + z,
                z + (sz[u] - sz[v]));
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    proc(1, 1);
    dfs(1, 1, 0, 0);
    printf("%lld\n", ans);

    return 0;
}