#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e3+5;
const int M = 1e9+7;

int n, m;
long dp[N][N];

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) {
        if(i == 0 || j == 0) dp[i][j] = 1;
        else {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
            dp[i][j] = (dp[i][j] + 4ll * j * dp[i - 1][j - 1]) % M;
            if(j > 1) dp[i][j] = (dp[i][j] + 1ll * (1ll * j * (j - 1) / 2) * dp[i - 1][j - 2]) % M;
            if(i > 1) dp[i][j] = (dp[i][j] + 1ll * j * (i - 1) * dp[i - 2][j - 1]) % M;
        }
    }
    printf("%lld\n", dp[n][m] - 1);

    return 0;
}