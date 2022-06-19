#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 205;
const int M = 1e9 + 9;

int n, m, k, sz;
long dp[N][N], ans[N][N];

void mul(long a[N][N], long b[N][N]) {
    long c[N][N];
    memset(c, 0, sizeof c);
    for (int k = 1; k <= sz; k++)
        for (int i = 1; i <= sz; i++)
            for (int j = 1; j <= sz; j++) {
                c[i][j] += (a[i][k] * b[k][j]) % M;
                c[i][j] %= M;
            }
    for (int i = 1; i <= sz; i++)
        for (int j = 1; j <= sz; j++)
            a[i][j] = c[i][j];
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    sz = n;
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (c == 1)
            ++dp[a][b], ++dp[b][a];
        else {
            ++sz, ++dp[a][sz];
            for (int j = 2; j < c; j++)
                ++sz, ++dp[sz - 1][sz];
            ++dp[sz][b];
            ++sz, ++dp[b][sz];
            for (int j = 2; j < c; j++)
                ++sz, ++dp[sz - 1][sz];
            ++dp[sz][a];
        }
    }
    for (int i = 1; i <= sz; i++)
        ans[i][i] = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            mul(ans, dp);
        mul(dp, dp);
    }
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[1][i]);

    return 0;
}