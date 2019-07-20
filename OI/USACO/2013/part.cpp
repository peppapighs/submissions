#include <bits/stdc++.h>

using namespace std;

int n, k, A[20][20];
int ans = 1e9;

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &A[i][j]);
    for(int bit = 0; bit <= 1 << (n-1); bit++) {
        int cnt = __builtin_popcount(bit), lim = min(k - cnt, n-1);
        int B[20][20], dp[20][20], mx[20][20];
        memset(mx, 0, sizeof mx);
        fill_n(dp[0], 20*20, 1e9);
        if(cnt > k) continue;
        for(int i = 1; i <= n; i++) for(int j = 1, sum = 0, R = 0; j <= n; j++) {
            sum += A[i][j];
            if((bit >> (j-1)) & 1 || j == n) {
                B[i][++R] = sum;
                sum = 0;
            }
        }
        for(int i = 1; i <= n; i++) {
            int sum[20];
            memset(sum, 0, sizeof sum);
            for(int j = i; j <= n; j++) for(int x = 1; x <= cnt+1; x++) {
                sum[x] += B[j][x];
                mx[i][j] = max(mx[i][j], sum[x]);
            }
        }
        for(int i = 0; i <= lim; i++) dp[0][i] = 0;
        for(int i = 1; i <= n; i++) {
            dp[i][0] = mx[1][i];
            for(int j = 1; j < i; j++) for(int x = 1; x <= lim; x++) dp[i][x] = min(dp[i][x], max(dp[j][x-1], mx[j+1][i]));
        }
        ans = min(ans, dp[n][lim]);
    }
    printf("%d\n", ans);

    return 0;
}