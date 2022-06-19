#include <bits/stdc++.h>

#define long long long

using namespace std;

const int M = 1e9 + 7;

long n, dp[105][105], ans[105];
int m;

int main() {
    scanf("%lld %d", &n, &m);
    for (int i = 1; i < m; i++)
        dp[i][i - 1] = 1;
    for (int i = 0; i < m; i++)
        ans[i] = 1;
    ans[0]++;
    dp[0][0] = dp[0][m - 1] = 1;
    if (n < m)
        return !printf("1\n");
    for (long a = n - m; a; a >>= 1) {
        if (a & 1) {
            long tdp[105];
            memset(tdp, 0, sizeof tdp);
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++) {
                    tdp[i] += (dp[i][j] * ans[j]) % M;
                    tdp[i] %= M;
                }
            for (int i = 0; i < m; i++)
                ans[i] = tdp[i];
        }
        long tdp[105][105];
        memset(tdp, 0, sizeof tdp);
        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++) {
                    tdp[i][j] += (dp[i][k] * dp[k][j]) % M;
                    tdp[i][j] %= M;
                }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                dp[i][j] = tdp[i][j];
    }
    printf("%lld\n", ans[0]);

    return 0;
}