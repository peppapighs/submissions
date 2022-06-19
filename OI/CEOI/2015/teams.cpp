#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e4 + 5;
const int M = 1e6 + 7;

int n, A[N], mx[N];
long dp[2][N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        mx[i] = max(mx[i - 1], A[i]), dp[0][i] = 1;
    }
    long ans = 1ll * (A[n] - 1) * dp[0][mx[n - 1]];
    for (int i = 1; i <= n; i++) {
        int now = i & 1, pre = now ^ 1;
        for (int j = 0; j <= n; j++)
            dp[now][j] = (1ll * j * dp[pre][j] % M + dp[pre][j + 1]) % M;
        if (i < n)
            ans = (ans + (A[n - i] - 1) * dp[now][mx[n - i - 1]]) % M;
    }
    printf("%lld\n", ans + 1);

    return 0;
}