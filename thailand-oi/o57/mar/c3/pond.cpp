#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 31;

int h, w, a, b;
long A[N][N], col[N][N], dp[N][N][1 << 4], idx, ans = 1e18;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void flood(int x, int y, int C) {
    queue<pii> Q;
    col[x][y] = C;
    Q.emplace(x, y);
    while (!Q.empty()) {
        int r = Q.front().x, c = Q.front().y;
        Q.pop();
        col[r][c] = C;
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr < 1 || nr > h || nc < 1 || nc > w)
                continue;
            if (A[nr][nc] && C == -1)
                col[nr][nc] = -1;
            if (A[r][c] == A[nr][nc] && col[nr][nc] == -2) {
                col[nr][nc] = C;
                Q.emplace(nr, nc);
            }
        }
    }
}

void dfs(int r, int c, int bit) {
    if (bit == (1 << idx) - 1)
        return void(ans = min(ans, dp[r][c][bit]));
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i], nbit = bit;
        long sw = 0;
        if (nr < 1 || nr > h || nc < 1 || nc > w || col[nr][nc] == -1)
            continue;
        if (col[nr][nc] > 0)
            nbit |= (1 << (col[nr][nc] - 1));
        if (dp[r][c][bit] + A[nr][nc] < dp[nr][nc][nbit]) {
            dp[nr][nc][nbit] = dp[r][c][bit] + A[nr][nc];
            swap(sw, A[nr][nc]);
            dfs(nr, nc, nbit);
            swap(sw, A[nr][nc]);
        }
    }
}

int main() {
    fill_n(dp[0][0], N * N * (1 << 4), INT_MAX);
    fill_n(col[0], N * N, -2);
    scanf("%d %d", &h, &w);
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            scanf("%lld", &A[i][j]);
    for (int i = 1; i <= h; i++) {
        if (!A[i][1] && col[i][1] == -2)
            flood(i, 1, -1);
        if (!A[i][w] && col[i][w] == -2)
            flood(i, w, -1);
    }
    for (int i = 1; i <= w; i++) {
        if (!A[1][i] && col[1][i] == -2)
            flood(1, i, -1);
        if (!A[h][i] && col[h][i] == -2)
            flood(h, i, -1);
    }
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++) {
            if (A[i][j] && col[i][j] == -2)
                flood(i, j, 0);
            else if (!A[i][j] && col[i][j] == -2) {
                if (!idx)
                    a = i, b = j;
                flood(i, j, ++idx);
            }
        }
    if (!a && !b)
        return printf("0\n");
    dp[a][b][1] = 0;
    dfs(a, b, 1);
    printf("%lld\n", ans);

    return 0;
}