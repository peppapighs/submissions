#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e12;

int n;
long long dp[105][105];
long long pref[105];

long long sum(int i, int j) { return (pref[j] - pref[i - 1]) % 100; }

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &pref[i]), pref[i] += pref[i - 1];
        for (int i = 1; i <= n; i++)
            fill(begin(dp[i]), end(dp[i]), INF);
        for (int i = 1; i <= n; i++)
            dp[i][i] = 0;
        for (int l = 2; l <= n; l++)
            for (int i = 1, j = i + l - 1; j <= n; i++, j++)
                for (int k = i; k <= j - 1; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] +
                                                 (sum(i, k) * sum(k + 1, j)));
        printf("%lld\n", dp[1][n]);
    }

    return 0;
}