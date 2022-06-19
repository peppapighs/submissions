#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

int n, k;
int ans;
int A[N][N][5];
int dp[N][N][5];

int get(int i, int j, int t) {
    return A[i][j][t] - A[max(i - k, 0)][j][t] - A[i][max(j - k, 0)][t] +
           A[max(i - k, 0)][max(j - k, 0)][t];
}

void slide(int t, int c) {
    deque<pii> Q;
    Q.emplace_back(get(k, c, t), k);
    dp[1][c][t] = get(k, c, t);
    for (int i = 2; i <= n; i++) {
        while (!Q.empty() && Q.front().y < i)
            Q.pop_front();
        if (i + k - 1 <= n) {
            while (!Q.empty() && Q.back().x < get(i + k - 1, c, t))
                Q.pop_back();
            Q.emplace_back(get(i + k - 1, c, t), i + k - 1);
        }
        dp[i][c][t] = Q.front().x;
    }
}

void solve(int r) {
    deque<pii> Q[4];
    for (int t = 1; t <= 3; t++)
        Q[t].emplace_back(dp[r][k][t], r);
    ans = max(ans, Q[1].front().x + Q[2].front().x + Q[3].front().x);
    for (int i = 2; i <= n; i++) {
        for (int t = 1; t <= 3; t++)
            while (!Q[t].empty() && Q[t].front().y < i)
                Q[t].pop_front();
        if (i + k - 1 <= n)
            for (int t = 1; t <= 3; t++) {
                while (!Q[t].empty() && Q[t].back().x < dp[r][i + k - 1][t])
                    Q[t].pop_back();
                Q[t].emplace_back(dp[r][i + k - 1][t], i + k - 1);
            }
        ans = max(ans, Q[1].front().x + Q[2].front().x + Q[3].front().x);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int t = 1; t <= 3; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                scanf("%d", &A[i][j][t]);
                A[i][j][t] +=
                    A[i - 1][j][t] + A[i][j - 1][t] - A[i - 1][j - 1][t];
            }
    for (int t = 1; t <= 3; t++)
        for (int i = k; i <= n; i++)
            slide(t, i);
    for (int i = 1; i <= n; i++)
        solve(i);
    printf("%d\n", ans);

    return 0;
}
