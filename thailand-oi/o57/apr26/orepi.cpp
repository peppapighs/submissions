#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 4e4 + 5;

int n, m;
long A[N], dp[N][105];

void solve(int d, int l, int r, int optl, int optr) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    dp[mid][d] = 1e18;
    int idx = -1;
    for (int k = optl; k <= min(optr, mid - 1); k++) {
        long now = dp[k][d - 1] + (mid - k) * (A[mid] - A[k]);
        if (now < dp[mid][d])
            dp[mid][d] = now, idx = k;
    }
    solve(d, l, mid - 1, optl, idx);
    solve(d, mid + 1, r, idx, optr);
}

int main() {
    scanf("%d %d", &n, &m);
    m = min(m, n - 1);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i), A[i] += A[i - 1];
    for (int i = 1; i <= n; i++)
        dp[i][0] = i * A[i];
    for (int i = 1; i <= m; i++)
        solve(i, 1, n, 1, n);
    printf("%lld\n", dp[n][m]);

    return 0;
}