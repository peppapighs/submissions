#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1.5e3 + 5;

int n, m, k, ans;

function<pii(int, int)> f[4] = {
    [](int x, int y) { return pii(x, y); },
    [](int x, int y) { return pii(n - x + 1, y); },
    [](int x, int y) { return pii(y, x); },
    [](int x, int y) { return pii(y, n - x + 1); }
};

int A[N][N], pref[N][N];

int rect(int x1, int x2, int y1, int y2) {
    return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
}

int dp[N][N][4];

void solve(int idx, int n, int m) {
    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        int x, y; tie(x, y) = f[idx](i, j);
        pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + A[x][y];
    }
    for(int i = k; i <= n; i++) for(int j = k; j <= m; j++) for(int t = 1; t <= 3; t++) {
        dp[i][j][t] = max(dp[i - k][m][t - 1], dp[i][j - k][t - 1]) + rect(i - k + 1, i, j - k + 1, j);
        dp[i][j][t] = max({dp[i][j][t], dp[i - 1][j][t], dp[i][j - 1][t]});
    }
    ans = max(ans, dp[n][m][3]);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", A[i] + j);

    solve(0, n, m), solve(1, n, m);
    solve(2, m, n), solve(3, m, n);

    printf("%d\n", ans);

    return 0;
}