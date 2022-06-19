#include <bits/stdc++.h>

using namespace std;

int q;
char A[105];
int dp[15][15][2];

long long calc(int pos, int last, int f) {
    int &ret = dp[pos][last][f];
    if (~ret)
        return ret;
    if (!A[pos])
        return (last != 0);
    ret = 0;
    int lim = 9;
    if (!f)
        lim = A[pos] - '0';
    if (!last)
        ret += calc(pos + 1, 0, 1);
    for (int i = last + 1; i <= lim; i++)
        ret += calc(pos + 1, i, f | (i < lim));
    return ret;
}

int solve(long long m) {
    memset(dp, -1, sizeof dp);
    sprintf(A, "%lld", m);
    return calc(0, 0, 0);
}

int main() {
    for (int n = 1; n <= 511; n++) {
        long long l = 1, r = 123456789LL;
        while (l < r) {
            long long m = (l + r) >> 1;
            if (solve(m) < n)
                l = m + 1;
            else
                r = m;
        }
        printf("%lld, ", l);
    }

    return 0;
}