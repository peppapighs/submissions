#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;
const int M = 2553;

int n, k;
int dp[2][N];
int ans;

int get(int i, int j) {
    int ret = dp[!(i & 1)][j];
    if (j - k >= 0)
        ret -= dp[!(i & 1)][j - k];
    ret = (ret + M) % M;
    return ret;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        int x = n - i;
        for (int j = 0; j <= x; j++)
            dp[i & 1][j] = get(i, j);
        int ret = (dp[i & 1][x] * dp[i & 1][x]) % M;
        ret = (ret * dp[i & 1][x]) % M;
        ans = (ans + ret) % M;
        for (int j = 1; j <= n; j++)
            dp[i & 1][j] = (dp[i & 1][j] + dp[i & 1][j - 1]) % M;
    }
    printf("%d\n", ans);

    return 0;
}
