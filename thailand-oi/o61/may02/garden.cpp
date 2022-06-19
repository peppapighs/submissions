#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;
const int M = 1e6 + 3;

int n, m, c, A[N];
long dp[N][1 << 10];
vector<int> bit[N], g[N];

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < n; i++)
        scanf("%d", A + i), ++dp[i][1 << A[i]];
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for (int i = 0; i < (1 << c); i++)
        bit[__builtin_popcount(i)].emplace_back(i);
    for (int i = 2; i <= c; i++)
        for (int j : bit[i])
            for (int u = 0; u < n; u++)
                if (j >> A[u] & 1)
                    for (int v : g[u])
                        dp[u][j] = (dp[u][j] + dp[v][j ^ (1 << A[u])]) % M;
    long ans = 0;
    for (int i = 0; i < n; i++)
        ans = (ans + dp[i][(1 << c) - 1]) % M;
    printf("%lld\n", ans);

    return 0;
}
