#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 305;

int n, m;
long mx[N][N][N], dp[N][N];

int main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for(int i = 1, w, l, r; i <= m; i++) {
        scanf("%d %d %d", &w, &l, &r);
        for(int j = l; j <= r; j++)
            mx[j][l][r] = max(mx[j][l][r], 1ll * w);
    }
    for(int k = 1; k <= n; k++)
        for(int len = 1; len <= n; len++) 
            for(int i = 1, j = len; j <= n; i++, j++)
                if(i <= k && k <= j) {
                    if(i < n) mx[k][i][j] = max(mx[k][i][j], mx[k][i+1][j]);
                    if(j) mx[k][i][j] = max(mx[k][i][j], mx[k][i][j-1]);
                }
    for(int len = 1; len <= n; len++)
        for(int i = 1, j = len; j <= n; i++, j++) {
            for(int k = i; k < j; k++) dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
            for(int k = i; k <= j; k++) if(mx[k][i][j]) {
                long now = mx[k][i][j];
                if(i <= k - 1) now += dp[i][k - 1];
                if(k + 1 <= j) now += dp[k + 1][j];
                dp[i][j] = max(dp[i][j], now);
            }
        }
    printf("%lld\n", dp[1][n]);

    return 0;
}