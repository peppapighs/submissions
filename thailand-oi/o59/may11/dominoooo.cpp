#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1 << 7;
const int M = 1e9 + 7;

int R, C, n;
long dp[N][N], ans[N][N];

bool chk(int x) {
    // Check if vertical pieces is OK
    int pv = 0;
    for (; x; x >>= 1) {
        if (x & 1)
            pv ^= 1;
        else if (pv)
            return 0;
    }
    return !pv;
}

void mul(long a[N][N], long b[N][N]) {
    long c[N][N];
    memset(c, 0, sizeof c);
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                c[i][j] += (a[i][k] * b[k][j]) % M;
                c[i][j] %= M;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = c[i][j];
}

int main() {
    scanf("%d %d", &R, &C);
    n = 1 << R;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            ans[i][i] = 1;
            // Check if some of bits in j can be horizontal
            for (int k = 0; k < n; k++)
                if (!(i & k) && (j & k) == k)
                    dp[i][j] += chk(j ^ k);
        }
    for (--C; C; C >>= 1) {
        if (C & 1)
            mul(ans, dp);
        mul(dp, dp);
    }
    long sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sum = (sum + 1ll * chk(i) * ans[i][j]) % M;
    printf("%lld\n", sum);

    return 0;
}
