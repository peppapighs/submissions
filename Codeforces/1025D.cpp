#include <bits/stdc++.h>

using namespace std;

int n;
bool dp[705][705][2];
int A[705], gcd[705][705];

bool f(int a, int b, int c) {
    if (a > b)
        return true;
    return dp[a][b][c];
}

int g(int a, int b) {
    if (a < 1 || a > n)
        return INT_MAX;
    return gcd[a][b];
}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            gcd[i][j] = __gcd(A[i], A[j]);
    for (int len = 1; len <= n; len++) {
        for (int i = 1, j = len; j <= n; i++, j++) {
            for (int k = i; k <= j; k++)
                if (f(i, k - 1, 0) && f(k + 1, j, 1)) {
                    if (g(i - 1, k) > 1)
                        dp[i][j][1] = true;
                    if (g(j + 1, k) > 1)
                        dp[i][j][0] = true;
                }
        }
    }
    if (dp[1][n][0] || dp[1][n][1])
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
