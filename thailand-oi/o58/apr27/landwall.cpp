#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, k;
int A[N], dp[N][N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    dp[1][0] = max(0, A[1]);
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 2][j] + A[i]);
            if (j)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + A[i]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    int ans = 0;
    for (int i = 0; i <= k; i++)
        ans = max(ans, dp[n][i]);
    printf("%d\n", ans);

    return 0;
}
