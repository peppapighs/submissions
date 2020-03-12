#include <bits/stdc++.h>

#define long long long

const int N = 105;

int n, m, k, chk[N][N];
long dp[N][N];

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for(int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &b, &a);
        chk[a][b] = true;
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        if(i == 1 && j == 1) dp[i][j] = 1;
        else {
            if(chk[i][j]) continue;
            if(i > 1) dp[i][j] += dp[i-1][j];
            if(j > 1) dp[i][j] += dp[i][j-1];
        }
    } 
    printf("%lld\n", dp[n][m]);

    return 0;
}