#include <bits/stdc++.h>

using namespace std;

int k;
int dp[25][25][2];
char A[20];

int solve(int pos = 0, int sum = 0, int f = 0) {
    if (sum > 10)
        return 0;
    if (!A[pos])
        return sum == 10;
    if (dp[pos][sum][f] != -1)
        return dp[pos][sum][f];
    int res = 0, lim;
    if (!f)
        lim = A[pos] - '0';
    else
        lim = 9;
    for (int i = 0; i <= lim; i++) {
        int nf = f;
        if (!f && i < lim)
            nf = 1;
        if (sum + i <= 10)
            res += solve(pos + 1, sum + i, nf);
    }

    return dp[pos][sum][f] = res;
}

int main() {
    scanf("%d", &k);
    long long l = 0, r = 2e10;
    long long res;
    while (l <= r) {
        long long m = (l + r) >> 1;
        memset(dp, -1, sizeof dp);
        sprintf(A, "%lld", m);
        int ret = solve();
        if (ret < k)
            l = m + 1;
        else
            res = m, r = m - 1;
    }
    printf("%lld\n", res);

    return 0;
}