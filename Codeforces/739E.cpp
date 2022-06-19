#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

const int N = 2e3 + 5;

int n, a, b;
double pa[N], pb[N], pab[N];
pair<double, int> dp[N][N];

pair<double, int> solve(double C) {
    fill_n(dp[0], N * N, make_pair(0, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= a; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j && dp[i][j].x < dp[i - 1][j - 1].x + pa[i])
                dp[i][j] =
                    make_pair(dp[i - 1][j - 1].x + pa[i], dp[i - 1][j - 1].y);
            if (dp[i][j].x < dp[i - 1][j].x + pb[i] - C)
                dp[i][j] =
                    make_pair(dp[i - 1][j].x + pb[i] - C, dp[i - 1][j].y + 1);
            if (j && dp[i][j].x < dp[i - 1][j - 1].x + pab[i] - C)
                dp[i][j] = make_pair(dp[i - 1][j - 1].x + pab[i] - C,
                                     dp[i - 1][j - 1].y + 1);
        }
    return dp[n][a];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> pa[i];
    for (int i = 1; i <= n; i++)
        cin >> pb[i];
    for (int i = 1; i <= n; i++)
        pab[i] = pa[i] + pb[i] - pa[i] * pb[i];

    double l = 0, r = 1;
    for (int it = 1; it <= 100; it++) {
        double mid = (l + r) / 2.0;
        if (solve(mid).y <= b)
            r = mid;
        else
            l = mid;
    }
    solve(r);
    cout << dp[n][a].x + r * b << endl;

    return 0;
}