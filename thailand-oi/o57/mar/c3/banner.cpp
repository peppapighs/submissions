#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, m;
int dp[N][N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        ++dp[a][b];
    }
    for (int len = 2; len <= n; len++)
        for (int i = 1, j = len; j <= n; i++, j++) {
            int mx = 0;
            for (int k = i; k < j; k++)
                mx = max(mx, dp[i][k] + dp[k + 1][j]);
            dp[i][j] += mx;
        }
    printf("%d\n", m - dp[1][n]);

    return 0;
}