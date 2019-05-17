#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, a[N], dp[N][3];
char op[N];

int main() {
    fill_n(dp[0], N*3, -1e9);
    scanf("%d", &n);
    for(int i = 1, x = 0, y = 0; i < 2 * n; i++) {
        if(i & 1) ++x, scanf("%d", a + x);
        else ++y, scanf(" %c", op + y);
    }
    dp[1][0] = a[1];
    for(int i = 2; i <= n; i++) {
        if(op[i-1] == '-') {
            dp[i][0] = max(dp[i-1][0] - a[i], dp[i-1][1] + a[i]);
            dp[i][1] = max({dp[i-1][1] + a[i], dp[i-1][0] - a[i], dp[i-1][2] - a[i]});
            dp[i][2] = max(dp[i-1][2] - a[i], dp[i-1][1] + a[i]);
        } else {
            dp[i][0] = max(dp[i-1][0] + a[i], dp[i-1][1] - a[i]);
            dp[i][1] = max(dp[i-1][1] - a[i], dp[i-1][2] + a[i]);
            dp[i][2] = dp[i-1][2] + a[i];
        }
    }
    printf("%d\n", dp[n][0]);

    return 0;
}