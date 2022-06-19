#include <bits/stdc++.h>

using namespace std;

const int N = 4e4 + 5;
const int M = 1e6 + 7;

int n, m;
int C[505], dp[2][N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &C[i]);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int cur = i & 1;
        dp[cur ^ 1][0] = 1;
        for (int j = 1; j <= m; j++) {
            dp[cur][j] = 0;
            if (C[i] <= j)
                dp[cur][j] += dp[cur ^ 1][j - C[i]];
            dp[cur][j] += dp[cur ^ 1][j];
            dp[cur][j] %= M;
        }
    }
    printf("%d\n", dp[n & 1][m]);

    return 0;
}
