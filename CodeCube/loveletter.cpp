#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, q;
long long dp[N][5][5];
char A[N];

int f(char a) {
    if (a == 'L')
        return 1;
    if (a == 'O')
        return 2;
    if (a == 'V')
        return 3;
    if (a == 'E')
        return 4;
}

long long query(int x, int y, int l = 1, int r = 4) {
    if (l == r)
        return dp[y][l][l] - dp[x - 1][l][l];
    if (x == 1)
        return dp[y][l][r];
    long long ret = dp[y][l][r] - dp[x - 1][l][r];
    for (int i = l; i < r; i++)
        ret -= query(1, x - 1, l, i) * query(x, y, i + 1, r);
    return ret;
}

int main() {
    scanf("%d", &n);
    scanf(" %s", A + 1);
    for (int i = 1; i <= n; i++) {
        int c = f(A[i]);
        for (int a = 1; a <= 4; a++) {
            for (int b = a; b <= 4; b++) {
                dp[i][a][b] = dp[i - 1][a][b];
                if (b == c)
                    dp[i][a][b] += dp[i - 1][a][b - 1];
            }
        }
        dp[i][c][c] = dp[i - 1][c][c] + 1LL;
    }
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%lld\n", query(l, r));
    }

    return 0;
}
