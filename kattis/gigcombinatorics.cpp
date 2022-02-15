#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;
const int M = 1e9 + 7;

int n;
long dp[N][4];

int main() {
    scanf("%d", &n);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if(a == 1) ++dp[i][1];
        if(a == 2) dp[i][2] += dp[i - 1][1] + dp[i - 1][2];
        if(a == 3) dp[i][3] += dp[i - 1][2];
        for(int j = 1; j <= 3; j++) {
            dp[i][j] += dp[i - 1][j];
            dp[i][j] %= M;
        }
    }
    printf("%lld\n", dp[n][3]);

    return 0;
}