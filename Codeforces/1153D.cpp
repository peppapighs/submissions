#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, lev, op[N], dp[N];
vector<int> g[N];

int dfs(int u, int p) {
    if (g[u].size() == 1 && u != 1) {
        ++lev;
        return dp[u] = 1;
    }
    if (op[u])
        dp[u] = 1e9;
    for (int v : g[u])
        if (v != p) {
            if (!op[u])
                dp[u] += dfs(v, u);
            else
                dp[u] = min(dp[u], dfs(v, u));
        }
    return dp[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", op + i);
    for (int i = 2, a; i <= n; i++) {
        scanf("%d", &a);
        g[a].emplace_back(i), g[i].emplace_back(a);
    }
    dfs(1, 1);
    printf("%d\n", lev + 1 - dp[1]);

    return 0;
}