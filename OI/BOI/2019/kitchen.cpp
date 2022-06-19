#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, m, k, sum;
int A[N], B[N], dp[2][N * N];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    if (m < k)
        return !printf("Impossible\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i), sum += A[i];
        if (A[i] < k)
            return !printf("Impossible\n");
    }
    for (int i = 1; i <= m; i++)
        scanf("%d", B + i);

    for (int i = 1; i < N * N; i++)
        dp[0][i] = -1e9;
    for (int i = 1; i <= m; i++) {
        int now = i & 1, pre = now ^ 1;
        for (int j = 0; j < N * N; j++) {
            dp[now][j] = dp[pre][j];
            if (j - B[i] >= 0 && dp[pre][j - B[i]] != -1e9)
                dp[now][j] = max(dp[now][j], dp[pre][j - B[i]] + min(n, B[i]));
        }
    }
    for (int j = sum; j < N * N; j++)
        if (dp[m & 1][j] >= n * k)
            return !printf("%d\n", j - sum);
    printf("Impossible\n");

    return 0;
}