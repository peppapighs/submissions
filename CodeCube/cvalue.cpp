#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, arr[N], dp[N][3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            dp[i][0] = dp[i - 1][0] - arr[i];
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + arr[i];
            dp[i][2] = min(dp[i - 1][2], dp[i - 1][1]) - arr[i];
        } else {
            dp[i][0] = dp[i - 1][0] + arr[i];
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) - arr[i];
            dp[i][2] = min(dp[i - 1][2], dp[i - 1][1]) + arr[i];
        }
    }

    printf("%d", min(dp[n][0], min(dp[n][1], dp[n][2])));

    return 0;
}