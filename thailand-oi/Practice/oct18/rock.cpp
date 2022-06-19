#include <bits/stdc++.h>

using namespace std;

int n;
int A[105], dp[105][105];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
        scanf("%d", A + i);
    for (int len = 2; len <= 2 * n; len++)
        for (int i = 1, j = i + len - 1; j <= 2 * n; i++, j++)
            dp[i][j] = max({dp[i + 2][j] + A[i], dp[i][j - 2] + A[j],
                            dp[i + 1][j - 1] + max(A[i], A[j])});

    printf("%d\n", dp[1][2 * n]);

    return 0;
}