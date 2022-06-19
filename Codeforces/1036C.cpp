#include <bits/stdc++.h>

using namespace std;

const long long N = 1e18 + 5;

int T;
int dp[20][5][2];

int solve(char *A, int pos = 0, int cnt = 0, int f = 0) {
    if (cnt > 3)
        return 0;
    if (!A[pos])
        return 1;
    if (dp[pos][cnt][f] != -1)
        return dp[pos][cnt][f];
    int res = 0, lim;
    if (!f)
        lim = A[pos] - '0';
    else
        lim = 9;
    for (int i = 0; i <= lim; i++) {
        int nf = f, ncnt = cnt;
        if (!f && i < lim)
            nf = 1;
        if (i)
            ncnt++;
        if (ncnt <= 3)
            res += solve(A, pos + 1, ncnt, nf);
    }

    return dp[pos][cnt][f] = res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        char A[20], B[20];
        sprintf(A, "%lld", l - 1);
        sprintf(B, "%lld", r);
        memset(dp, -1, sizeof dp);
        int a = solve(A);
        memset(dp, -1, sizeof dp);
        int b = solve(B);
        printf("%d\n", b - a);
    }

    return 0;
}