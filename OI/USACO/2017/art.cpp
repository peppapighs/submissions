#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
const int M = N * N;

int n, all;
int A[N][N];
int cnt[M], l[M], r[M], u[M], b[M];
int dp[N][N];

int main() {
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);

    fill_n(l, M, 1e9);
    fill_n(u, M, 1e9);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &A[i][j]);
            if (!A[i][j])
                continue;
            if (!cnt[A[i][j]])
                ++all;
            ++cnt[A[i][j]];
            l[A[i][j]] = min(l[A[i][j]], j);
            r[A[i][j]] = max(r[A[i][j]], j);
            u[A[i][j]] = min(u[A[i][j]], i);
            b[A[i][j]] = max(b[A[i][j]], i);
        }
    if (all == 1)
        return !printf("%d\n", n * n - 1);
    for (int i = 1; i <= n * n; i++)
        if (cnt[i]) {
            ++dp[u[i]][l[i]];
            --dp[u[i]][r[i] + 1];
            --dp[b[i] + 1][l[i]];
            ++dp[b[i] + 1][r[i] + 1];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            if (dp[i][j] >= 2)
                cnt[A[i][j]] = 0;
        }
    int ans = n * n - all;
    for (int i = 1; i <= n * n; i++)
        if (cnt[i])
            ++ans;
    printf("%d\n", ans);

    return 0;
}