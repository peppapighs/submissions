#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
int A[N], dp[N][2];
vector<int> g[N];

void dfs(int u, int p) {
    dp[u][1] = A[u];
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", A + i);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(0, 0);
    printf("%d\n", max(dp[0][0], dp[0][1]));

    return 0;
}