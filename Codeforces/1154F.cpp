#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

int n, m, k;
int cnt[N], pos[N];
long A[N], dp[N];

int main() {
    fill_n(dp, N, 1e18);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i);
    for (int i = 1; i <= m; i++)
        scanf("%d %d", cnt + i, pos + i);
    sort(A + 1, A + n + 1);
    for (int i = 1; i <= n; i++)
        A[i] += A[i - 1];
    dp[0] = 0;
    for (int i = 0; i <= k; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + A[i + 1] - A[i]);
        for (int j = 1; j <= m; j++)
            if (i + cnt[j] <= k)
                dp[i + cnt[j]] =
                    min(dp[i + cnt[j]], A[i + cnt[j]] - A[i + pos[j]] + dp[i]);
    }
    printf("%lld\n", dp[k]);

    return 0;
}