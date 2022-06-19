#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;
const int M = 1e9 + 7;

int n, h, A[N];
long dp[N][N];

int main() {
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    dp[1][0] = (A[1] == h || A[1] + 1 == h);
    dp[1][1] = (A[1] + 1 == h);
    for (int i = 2; i <= n; i++)
        for (int j = max(0, h - A[i] - 1); j <= min(i, h - A[i]); j++) {
            if (A[i] + j == h) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
                if (j > 0)
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % M;
            }
            if (A[i] + j + 1 == h) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
                dp[i][j] = (dp[i][j] + (dp[i - 1][j + 1] * (j + 1)) % M) % M;
                if (j > 0)
                    dp[i][j] = (dp[i][j] + (dp[i - 1][j] * j) % M) % M;
            }
        }
    printf("%lld\n", dp[n][0]);

    return 0;
}
