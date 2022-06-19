#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e3 + 5;
const int M = 998244353;

int n, s, A[N];
long dp[N][N][2];

long solve(int idx, int sum, int f) {
    if (sum == s)
        return n - idx + 1;
    if (idx == n)
        return 0;
    long &now = dp[idx][sum][f];
    if (~now)
        return now;
    now = 0;
    now = (now + solve(idx + 1, sum, f)) % M;
    if (sum + A[idx + 1] <= s)
        now = (now + solve(idx + 1, sum + A[idx + 1], 1)) % M;
    return now;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    solve(0, 0, 0);
    long ans = 0;
    for (int i = 1; i <= n; i++)
        if (A[i] <= s)
            ans = (ans + solve(i, A[i], 1) * i % M) % M;
    printf("%lld\n", ans);

    return 0;
}