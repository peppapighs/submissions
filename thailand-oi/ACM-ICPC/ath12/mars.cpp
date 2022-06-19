#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int T, n;
char S[N];
long dp[N][30][30];

int d(int a, int b) { return min((a - b + 26) % 26, (b - a + 26) % 26); }

long solve(int pos, int a, int b) {
    if (pos > n)
        return 0;
    long &ret = dp[pos][a][b];
    if (~ret)
        return ret;
    int now = S[pos] - 'A';
    int na = d(now, a), nb = d(now, b);
    ret = min(solve(pos + 1, now, b) + na, solve(pos + 1, a, now) + nb);
    return ret;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf(" %s", S + 1);
        n = strlen(S + 1);
        memset(dp, -1, sizeof dp);
        printf("%lld\n", solve(1, 0, 0));
    }

    return 0;
}