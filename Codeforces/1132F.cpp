#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n;
int dp[N][N];
char S[N];

int main() {
    scanf("%d", &n);
    scanf(" %s", S + 1);
    for (int len = 1; len <= n; len++) {
        for (int i = 1, j = len; j <= n; i++, j++) {
            dp[i][j] = 1e9;
            if (len == 1)
                dp[i][j] = 1;
            else {
                dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                for (int k = i; k < j; k++)
                    if (S[i] == S[k + 1])
                        dp[i][j] = min(dp[i][j], dp[i + 1][k] + dp[k + 1][j]);
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}
