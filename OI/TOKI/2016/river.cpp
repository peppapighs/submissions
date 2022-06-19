#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;
const int M = 1e9 + 7;

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

int n, m, k;
long dp[2][1005];
char sub[100], w[N];

int main() {
    scanf("%s", sub);
    scanf("%d %d %d %s", &n, &m, &k, w + 1);

    dp[0][0] = 1;
    long mul = modpow(2, n - 1);
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= k; j++) {
            dp[i & 1][j] = 0;
            if (j)
                dp[i & 1][j] = (dp[i & 1][j] + dp[~i & 1][j - 1] * mul % M) % M;
            dp[i & 1][j] = (dp[i & 1][j] + dp[~i & 1][j] * mul % M) % M;
        }
    printf("%lld\n", dp[m & 1][k]);

    return 0;
}