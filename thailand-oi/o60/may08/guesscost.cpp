#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, C[N], dp[N][N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", C+i), dp[i][i] = C[i];
    for(int len = 2; len <= n; len++) for(int i = 1, j = len; j <= n; i++, j++) {
        dp[i][j] = 1e9;
        for(int k = i; k <= j; k++) 
            dp[i][j] = min(dp[i][j], C[k] + max(dp[i][k-1], dp[k+1][j]));
    }
    printf("%d\n", dp[1][n]);

    return 0;
}
