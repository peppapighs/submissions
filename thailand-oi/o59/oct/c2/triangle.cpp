#include <bits/stdc++.h>

using namespace std;

const int M = 1e9 + 7;

int n, m;
long long dp[105][105];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1LL;
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            for (int k = i - 1; k; k--)
                if (i - k <= m)
                    dp[i][j] = dp[i][j] + dp[k - 1][j - 1];
            for (int k = j - 1; k; k--)
                if (j - k <= m)
                    dp[i][j] = dp[i][j] + dp[i - 1][k - 1];
            dp[i][j] = (dp[i][j] + M) % M;
        }
    printf("%lld\n", (dp[n][n] + M - 1) % M);

    return 0;
}
