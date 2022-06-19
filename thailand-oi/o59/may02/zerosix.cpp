#include <bits/stdc++.h>

using namespace std;

int n, m;
int dp[105][105][1005];

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int a, p2 = 0, p3 = 0;
            scanf("%d", &a);
            for (; a % 2 == 0; a /= 2)
                p2++;
            for (; a % 3 == 0; a /= 3)
                p3++;
            if (i == 1 && j == 1)
                dp[i][j][p3] = p2;
            else
                for (int k = p3; k <= 1000; k++) {
                    if (dp[i - 1][j][k - p3] != -1)
                        dp[i][j][k] =
                            max(dp[i][j][k], dp[i - 1][j][k - p3] + p2);
                    if (dp[i][j - 1][k - p3] != -1)
                        dp[i][j][k] =
                            max(dp[i][j][k], dp[i][j - 1][k - p3] + p2);
                }
        }

    int ans = 0;
    for (int i = 0; i <= 1000; i++)
        ans = max(ans, min(i, dp[n][m][i]));
    printf("%d\n", ans);

    return 0;
}
