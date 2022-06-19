#include <stdio.h>

int A[5005], B[5005];

int dp[2][5005][2];

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main() {
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= M; i++)
        scanf("%d", &B[i]);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5005; j++)
            for (int p = 0; p < 2; p++)
                dp[i][j][p] = (1e9) + 5;
    dp[0][0][0] = 0;
    int res = 0;
    for (int i = 1; i <= N; i++) {
        int cur = i & 1;
        int prev = !cur;
        dp[cur][0][0] = 1;
        dp[cur][0][1] = 1;
        for (int j = 1; j <= M; j++) {
            dp[cur][j][0] = (1e9) + 5;
            dp[cur][j][1] = (1e9) + 5;
            if (A[i] == B[j]) {
                dp[cur][j][0] = dp[prev][j - 1][0];
                // dp[cur][j][1] = dp[prev][j-1][1];
                if (dp[cur][j][0] <= K || dp[cur][j][1] <= K) {
                    res = max(res, j);
                }
            }
            // incorrect
            dp[cur][j][0] = min(dp[cur][j][0], dp[prev][j - 1][0] + 1);
            // skip
            dp[cur][j][1] =
                min(dp[cur][j][1], min(dp[prev][j][0] + 1, dp[prev][j][1]));
            // insert
            dp[cur][j][0] = min(dp[cur][j][0], dp[cur][j - 1][0] + 1);

            dp[cur][j][0] = min(dp[cur][j][0], dp[cur][j][1]);
            if (dp[cur][j][0] <= K || dp[cur][j][1] <= K) {
                res = max(res, j);
            }
        }
    }
    printf("%d", res);
    return 0;
}