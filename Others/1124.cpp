#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e4+5;

int n, k;
int mask[N];
long dp[N][1 << 8], cost[N];

int main() {
    fill_n(dp[0], N * (1 << 8), 1e18);

    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", cost + i);
        for(int j = 0, a; j < k; j++) {
            scanf("%d", &a);
            mask[i] += a << j; 
        }
    }
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) for(int j = 0; j < 1 << k; j++) {
        dp[i][j | mask[i]] = min(dp[i][j | mask[i]], dp[i-1][j] + cost[i]);
        dp[i][j] = min(dp[i][j], dp[i-1][j]);
    }

    printf("%lld\n", dp[n][(1 << k) - 1]);

    return 0;
}