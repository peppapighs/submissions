#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 505;
const int dx[4] = {1, 1, -1, -1};
const int dy[4] = {1, -1, -1, 1};
const int px[4] = {0, 0, -1, -1};
const int py[4] = {0, -1, -1, 0};

int n, m;
int dp[N][N];
char A[N][N];
priority_queue<iii, vector<iii>, greater<iii>> Q;

int main() {
    fill_n(dp[0], N * N, 1e9);

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf(" %s", A[i] + 1);

    Q.emplace(dp[1][1] = 0, 1, 1);
    while (!Q.empty()) {
        iii now = Q.top();
        Q.pop();
        int d, r, c;
        tie(d, r, c) = now;
        if (dp[r][c] != d)
            continue;

        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr < 1 || nr > n + 1 || nc < 1 || nc > m + 1)
                continue;
            char C = i & 1 ? '/' : '\\';
            if (d + (C != A[r + px[i]][c + py[i]]) < dp[nr][nc]) {
                dp[nr][nc] = d + (C != A[r + px[i]][c + py[i]]);
                Q.emplace(dp[nr][nc], nr, nc);
            }
        }
    }
    if (dp[n + 1][m + 1] == 1e9)
        printf("NO SOLUTION\n");
    else
        printf("%d\n", dp[n + 1][m + 1]);

    return 0;
}