#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 405;

int n;
int cnt[3], dp[3][N][N][N];
char A[N];
vector<iii> vec[3];

int f(char c) {
    if (c == 'R')
        return 0;
    if (c == 'G')
        return 1;
    return 2;
}

int cost(int c, iii a, iii b) {
    int ret = 0;
    if (c != 0)
        ret += max(0, get<0>(b) - get<0>(a));
    if (c != 1)
        ret += max(0, get<1>(b) - get<1>(a));
    if (c != 2)
        ret += max(0, get<2>(b) - get<2>(a));
    return ret;
}

int main() {
    scanf("%d %s", &n, A + 1);
    for (int i = 1; i <= n; i++) {
        ++cnt[f(A[i])];
        vec[f(A[i])].emplace_back(cnt[0], cnt[1], cnt[2]);
    }

    int R = cnt[0], G = cnt[1], Y = cnt[2];
    for (int i = 0; i <= R; i++)
        for (int j = 0; j <= G; j++)
            for (int k = 0; k <= Y; k++) {
                if (!i && !j && !k)
                    continue;
                dp[0][i][j][k] = dp[1][i][j][k] = dp[2][i][j][k] = 1e9;
                if (i)
                    dp[0][i][j][k] =
                        min(dp[1][i - 1][j][k], dp[2][i - 1][j][k]) +
                        cost(0, vec[0][i - 1], {i, j, k});
                if (j)
                    dp[1][i][j][k] =
                        min(dp[0][i][j - 1][k], dp[2][i][j - 1][k]) +
                        cost(1, vec[1][j - 1], {i, j, k});
                if (k)
                    dp[2][i][j][k] =
                        min(dp[0][i][j][k - 1], dp[1][i][j][k - 1]) +
                        cost(2, vec[2][k - 1], {i, j, k});
            }
    int ans = 1e9;
    for (int i = 0; i < 3; i++)
        ans = min(ans, dp[i][R][G][Y]);
    if (ans == 1e9)
        printf("-1\n");
    else
        printf("%d\n", ans);

    return 0;
}