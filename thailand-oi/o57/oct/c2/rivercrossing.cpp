#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e4 + 5;
const int M = 30011;

int n, m, k, l;
int dp[N][15][2];
vector<int> rs[N][2];
pii seg[N][2];

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &l);
    while (l--) {
        int a, b;
        scanf("%d %d", &a, &b);
        rs[a][0].emplace_back(b);
        rs[b][1].emplace_back(a);
    }
    for (int i = 1; i <= n; i++) {
        sort(rs[i][0].begin(), rs[i][0].end());
        int a, b;
        scanf("%d %d", &a, &b);
        seg[i][0] = pii(b, b + a - 1);
    }
    for (int i = 1; i <= m; i++) {
        sort(rs[i][1].begin(), rs[i][1].end());
        int a, b;
        scanf("%d %d", &a, &b);
        seg[i][1] = pii(b, b + a - 1);
    }
    for (int i = 1; i <= m; i++)
        dp[i][0][1] += (dp[i - 1][0][1] + 1) % M;
    for (int x = 1; x <= k; x++) {
        if (x & 1)
            for (int i = 1; i <= n; i++) {
                int l = seg[i][0].x, r = seg[i][0].y;
                for (int t : rs[i][0])
                    if (l <= t && t <= r) {
                        dp[i][x][0] -= dp[t][x - 1][1] - dp[t - 1][x - 1][1];
                        r++;
                    }
                r = min(r, m);
                dp[i][x][0] += dp[r][x - 1][1] - dp[l - 1][x - 1][1];
                dp[i][x][0] += dp[i - 1][x][0];
                dp[i][x][0] = (dp[i][x][0] + M) % M;
            }
        else
            for (int i = 1; i <= m; i++) {
                int l = seg[i][1].x, r = seg[i][1].y;
                for (int t : rs[i][1])
                    if (l <= t && t <= r) {
                        dp[i][x][1] -= dp[t][x - 1][0] - dp[t - 1][x - 1][0];
                        r++;
                    }
                r = min(r, n);
                dp[i][x][1] += dp[r][x - 1][0] - dp[l - 1][x - 1][0];
                dp[i][x][1] += dp[i - 1][x][1] + 1;
                dp[i][x][1] = (dp[i][x][1] + M) % M;
            }
    }

    if (k & 1)
        printf("%d\n", dp[n][k][0]);
    else
        printf("%d\n", dp[n][k - 1][0]);

    return 0;
}
