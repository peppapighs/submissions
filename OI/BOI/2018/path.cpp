#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5 + 5;

int n, m, k, col[N];
long dp[N][1 << 5], ans;
vector<int> g[N], bit[10];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", col + i);
        --col[i];
        dp[i][1 << col[i]] = 1;
    }
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for(int i = 1; i < (1 << k); i++)
        bit[__builtin_popcount(i)].emplace_back(i);
    for(int i = 2; i <= k; i++) for(int b : bit[i]) for(int u = 1; u <= n; u++) {
        if(b >> col[u] & 1) for(int v : g[u])
            dp[u][b] += dp[v][b ^ (1 << col[u])];
        ans += dp[u][b];
    }
    printf("%lld\n", ans);

    return 0;
}