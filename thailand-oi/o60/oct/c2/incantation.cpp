#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 7;

int n, k, mx;
long long ans[N], dp[N][N];

int main() {
    scanf("%d%d", &n, &k);
    mx = 1 << k;
    for (int i = 0; i < mx; i++) {
        long long cost;
        scanf("%lld", &cost);
        dp[i >> 1][i] = cost;
        dp[(mx >> 1) | (i >> 1)][i] = cost;
    }
    for (int a = n - k + 1; a; a >>= 1) {
        if (a & 1) {
            long long tmp[N];
            memset(tmp, 0LL, sizeof tmp);
            for (int i = 0; i < mx; i++)
                for (int j = 0; j < mx; j++)
                    tmp[j] = max(tmp[j], ans[i] + dp[i][j]);
            for (int i = 0; i < mx; i++)
                ans[i] = tmp[i];
        }

        long long tmp[N][N];
        memset(tmp, 0LL, sizeof tmp);
        for (int i = 0; i < mx; i++)
            for (int j = 0; j < mx; j++)
                for (int l = 0; l < mx; l++)
                    tmp[i][j] = max(tmp[i][j], dp[i][l] + dp[l][j]);
        for (int i = 0; i < mx; i++)
            for (int j = 0; j < mx; j++)
                dp[i][j] = tmp[i][j];
    }

    long long ret = 0;
    for (int i = 0; i < mx; i++)
        ret = max(ret, ans[i]);
    printf("%lld", ret);

    return 0;
}