#include <bits/stdc++.h>

using namespace std;

const int N = 2e4+5;

int n, t, s;
int A[N], pre[N][55], dp[55][N], mn[55];

int main() {
    fill_n(dp[0], 55 * N, INT_MAX);

    scanf("%d %d %d", &n, &t, &s);
    for(int i = 1; i <= t; i++) scanf("%d", A + i), A[i] += A[i-1];
    for(int i = 1; i <= n; i++) {
        char S[N];
        scanf(" %s", S + 1);
        for(int j = 1; j <= t; j++) {
            if(S[j] == '0') pre[j][i] = j;
            else pre[j][i] = pre[j-1][i];
        }
    }
    for(int i = 1; i <= t; i++) {
        pre[i][n + 1] = i;
        sort(pre[i] + 1, pre[i] + n + 1);
    }
    dp[0][0] = 0;
    for(int k = 1; k <= s; k++) {
        fill_n(mn, 55, 2e9);
        for(int i = 1; i <= t; i++) {
            for(int j = 0; j <= n; j++) {
                for(int l = pre[i - 1][j + 1]; l < pre[i][j + 1]; l++) mn[j] = min(mn[j], dp[k-1][l] - A[l] * j);
                if(pre[i][j + 1]) dp[k][i] = min(dp[k][i], mn[j] + A[i] * j);
            }
        }
        printf("%d\n", dp[k][t]);
    }

    return 0;
}