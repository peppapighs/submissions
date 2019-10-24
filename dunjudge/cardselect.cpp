#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, a;
int A[55];
long dp[55][55][2505];

int main() {
    scanf("%d %d", &n, &a);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k <= 2500; k++) {
        dp[i][j][k] += dp[i-1][j][k];
        if(k >= A[i] && j) dp[i][j][k] += dp[i-1][j-1][k - A[i]];
    }
    long ans = 0;
    for(int i = 1; i <= n; i++) ans += dp[n][i][i * a];
    printf("%lld\n", ans);

    return 0;
}