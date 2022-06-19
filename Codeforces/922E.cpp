#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, w, b, x, sumb = 0;
    scanf("%lld%lld%lld%lld", &n, &w, &b, &x);
    long long bird[n], cost[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &bird[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &cost[i]);
        sumb += cost[i];
    }
    long long dp[n + 1][sumb + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sumb; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = w;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= sumb && dp[i][j] != -1; j++) {
            for (int k = 0; k <= bird[i] && dp[i][j] - cost[i] * k >= 0; k++) {
                dp[i + 1][j + k] =
                    min(w + (j + k) * b, dp[i][j] - cost[i] * k + x);
            }
        }
    }
    int mx = 0;
    for (int i = 0; i <= sumb; i++) {
        if (dp[n][i] != -1) {
            mx = max(mx, i);
        }
    }

    printf("%d", mx);

    return 0;
}
