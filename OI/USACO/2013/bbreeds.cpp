#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
const int M = 2012;

int n;
int dp[N][N], suf[N];
char S[N];

int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);

    scanf(" %s", S + 1);
    n = strlen(S + 1);

    for (int i = n; i; i--) {
        if (S[i] == '(')
            suf[i] = suf[i + 1] - 1;
        else
            suf[i] = suf[i + 1] + 1;
    }
    dp[n + 1][0] = 1;
    for (int i = n; i; i--)
        for (int j = 0; j <= n; j++) {
            int k = suf[i] - j;
            if (k < 0)
                continue;
            if (S[i] == '(') {
                dp[i][j] += dp[i + 1][j + 1];
                dp[i][j] += dp[i + 1][j];
            } else {
                if (j > 0)
                    dp[i][j] += dp[i + 1][j - 1];
                if (k > 0)
                    dp[i][j] += dp[i + 1][j];
            }
            dp[i][j] %= M;
        }
    if (suf[1] == 0)
        printf("%d\n", dp[1][0]);
    else
        printf("0\n");

    return 0;
}