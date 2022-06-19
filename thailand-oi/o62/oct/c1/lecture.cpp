#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int C, n, m;
int room[N];
long dp[305][305], len[N];

bool chk(long mid) {
    long cur = 0, time = 0;
    for (int i = 1; i < C; i++) {
        cur += dp[room[i]][room[i + 1]] * mid;
        if (cur > time + len[i] + len[i + 1])
            return false;
        cur = max(cur, time + len[i]);
        time += len[i];
    }
    return true;
}

int main() {
    fill_n(dp[0], 305 * 305, 1e18);
    scanf("%d %d %d", &C, &n, &m);
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;
    for (int i = 1; i <= C; i++)
        scanf("%d", room + i);
    for (int i = 1; i <= C; i++)
        scanf("%lld", len + i);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        dp[a][b] = dp[b][a] = c;
    }
    if (C == 1)
        return !printf("%lld\n", LLONG_MAX);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    long l = 1, r = 1e12;
    while (l < r) {
        long mid = (l + r + 1) >> 1;
        if (chk(mid))
            l = mid;
        else
            r = mid - 1;
    }
    printf("%lld\n", l);

    return 0;
}