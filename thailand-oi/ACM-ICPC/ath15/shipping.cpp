#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T;
int n, ans;
int A[N], dp[N][5];
vector<int> g[N];

void dfs(int u, int p) {
    dp[u][0] = A[u];
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
            for (int i = 0; i < 4; i++)
                ans = max(ans, dp[v][i] + dp[u][3 - i]);
            for (int i = 0; i < 4; i++)
                dp[u][i + 1] = max(dp[u][i + 1], dp[v][i]);
        }
    ans = max(ans, dp[u][4] + A[u]);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        ans = -1;
        fill_n(dp[0], N * 5, -1e9);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", A + i), g[i].clear();
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d %d", &a, &b);
            g[a].emplace_back(b), g[b].emplace_back(a);
        }
        dfs(1, 1);
        printf("%d\n", ans);
    }

    return 0;
}
