#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, m;
int g[N][N], pw[N][N];

void mul(int a[N][N], int b[N][N]) {
    int c[N][N];
    fill_n(c[0], N * N, -1e9);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = c[i][j];
}

bool f(int mid) {
    int ret[N][N], dp[N][N];
    memset(ret, 0, sizeof ret);
    bool first = true;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = g[i][j];
    for (int a = mid; a; a >>= 1) {
        if (a & 1) {
            if (first) {
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        ret[i][j] = dp[i][j];
                first = false;
            } else
                mul(ret, dp);
        }
        mul(dp, dp);
    }
    for (int i = 1; i <= n; i++)
        if (ret[i][i] > 0)
            return 1;
    return 0;
}

int main() {
    fill_n(g[0], N * N, -1e9);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        g[i][i] = 0;
    for (int i = 1, a, b, c, d; i <= m; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        g[a][b] = c, g[b][a] = d;
    }
    int ans = 0;
    int l = 1, r = 2 * n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (f(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%d\n", ans);

    return 0;
}