#include <bits/stdc++.h>

#define iii tuple<int, int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 32;

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int w, h, d[N][N][N][N];
int dp[N][N][N][N];
int ax, ay, bx, by;
int ans = 1e9, cnt;
char A[35][35];

int main() {
    fill_n(d[0][0][0], N * N * N * N, 1e9);
    fill_n(dp[0][0][0], N * N * N * N, 1e9);
    scanf("%d %d", &w, &h);
    for (int i = 1; i <= h; i++) {
        scanf(" %s", A[i] + 1);
        for (int j = 1; j <= w; j++) {
            if (A[i][j] == 'A')
                ax = i, ay = j, A[i][j] = '.';
            if (A[i][j] == 'B')
                bx = i, by = j, A[i][j] = '.';
        }
    }
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++) {
            queue<pii> Q;
            d[i][j][i][j] = 0;
            Q.emplace(i, j);
            while (!Q.empty()) {
                pii now = Q.front();
                Q.pop();
                int r = now.x, c = now.y;
                for (int k = 0; k < 4; k++) {
                    int nr = r + dx[k], nc = c + dy[k];
                    if (A[nr][nc] != '.')
                        continue;
                    if (d[i][j][r][c] + 1 < d[i][j][nr][nc]) {
                        d[i][j][nr][nc] = d[i][j][r][c] + 1;
                        Q.emplace(nr, nc);
                    }
                }
            }
        }
    queue<iii> Q;
    dp[ax][ay][bx][by] = 0;
    Q.emplace(ax, ay, bx, by);
    while (!Q.empty()) {
        iii now = Q.front();
        Q.pop();
        int r1, c1, r2, c2;
        tie(r1, c1, r2, c2) = now;
        if (d[r1][c1][r2][c2] < ans)
            ans = d[r1][c1][r2][c2], cnt = dp[r1][c1][r2][c2];
        for (int i = 0; i < 4; i++) {
            int nr1 = r1 + dx[i], nc1 = c1 + dy[i];
            int nr2 = r2 + dx[i ^ 1], nc2 = c2 + dy[i ^ 1];
            if (A[nr1][nc1] != '.')
                nr1 = r1, nc1 = c1;
            if (A[nr2][nc2] != '.')
                nr2 = r2, nc2 = c2;
            if (dp[r1][c1][r2][c2] + 1 < dp[nr1][nc1][nr2][nc2]) {
                dp[nr1][nc1][nr2][nc2] = dp[r1][c1][r2][c2] + 1;
                Q.emplace(nr1, nc1, nr2, nc2);
            }
        }
    }
    if (ans != 1e9)
        printf("%d %d\n", ans, cnt);
    else
        printf("-1 0\n");

    return 0;
}
