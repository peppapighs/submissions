#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;
const int M = 1e6 + 3;

int R, C, K;
int A[N][N];
long pre[N][N], dp[N][N], ans[N][N];

void mul(long a[N][N], long b[N][N]) {
    int c[N][N];
    memset(c, 0, sizeof c);
    for (int k = 1; k <= R; k++)
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= R; j++) {
                c[i][j] += (a[i][k] * b[k][j]) % M;
                c[i][j] %= M;
            }
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= R; j++)
            a[i][j] = c[i][j];
}

int main() {
    scanf("%d %d %d", &R, &C, &K);
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            scanf("%d", &A[i][j]);
    for (int i = 1; i <= R; i++) {
        memset(pre, 0, sizeof pre);
        pre[i][1] = A[i][1], ans[i][i] = 1;
        for (int k = 2; k <= C; k++)
            for (int j = 1; j <= R; j++)
                if (A[j][k]) {
                    pre[j][k] +=
                        pre[j - 1][k - 1] + pre[j][k - 1] + pre[j + 1][k - 1];
                    pre[j][k] %= M;
                }
        for (int j = 1; j <= R; j++)
            dp[i][j] = pre[j][C];
    }
    for (; K; K >>= 1) {
        if (K & 1)
            mul(ans, dp);
        mul(dp, dp);
    }
    for (int i = 1; i <= R; i++) {
        long ret = 0;
        for (int j = 1; j <= R; j++)
            ret = (ret + ans[i][j]) % M;
        printf("%lld\n", ret);
    }

    return 0;
}
