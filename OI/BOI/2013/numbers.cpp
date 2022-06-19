#include <bits/stdc++.h>

using namespace std;

long long a, b, ans;
long long dp[20][15][15][2][2];
char A[20];

long long solve(int pos = 0, int a = 10, int b = 10, int f = 0, int st = 1) {
    if (!A[pos])
        return 1LL;
    long long &ret = dp[pos][a][b][f][st];
    if (~ret)
        return ret;
    ret = 0;
    int lim;
    if (!f)
        lim = A[pos] - '0';
    else
        lim = 9;
    for (int i = 0; i <= lim; i++) {
        if (i == a || i == b)
            continue;
        if (!i && st)
            ret += solve(pos + 1, 10, 10, 1, 1);
        else
            ret += solve(pos + 1, b, i, f | (i < lim), 0);
    }

    return ret;
}

int main() {
    scanf("%lld %lld", &a, &b);
    memset(dp, -1LL, sizeof dp);
    sprintf(A, "%lld", b);
    ans = solve();
    if (a) {
        memset(dp, -1LL, sizeof dp);
        sprintf(A, "%lld", a - 1);
        ans -= solve();
    }

    printf("%lld\n", ans);

    return 0;
}