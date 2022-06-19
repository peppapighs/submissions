#include <bits/stdc++.h>

using namespace std;

const int M = 2009;

int q, a, b;
int dp[55][55][55][2];

int solve(int n, int p, int i,
          int f) { // position - possible push left - stack size - just pushed?
    if (n == 0 && f == 0)
        return (p == 0);
    int &ret = dp[n][p][i][f];
    if (~ret)
        return ret;
    ret = 0;
    if (n != 0)
        ret += solve(n - 1, p, i, 0); // move
    if (n != 0 && p != 0)
        ret += solve(n - 1, p - 1, i + 1, 1); // push
    if (i != 0 && f == 0)
        ret += solve(n, p, i - 1, 0); // pop
    ret %= M;
    return ret;
}

int main() {
    scanf("%d", &q);
    memset(dp, -1, sizeof dp);
    solve(50, 50, 0, 0);
    while (q--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", solve(a, b, 0, 0));
    }

    return 0;
}