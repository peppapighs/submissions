#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 305;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int R, C, m;
int A[N][N], vis[N][N];

int get(int a, int b, int c, int d) {
    return A[c][d] - A[a - 1][d] - A[c][b - 1] + A[a - 1][b - 1];
}

bool chk(int h, int w) {
    if (get(1, 1, h, w))
        return false;
    queue<pii> Q;
    memset(vis, 0, sizeof vis);
    Q.emplace(h, w), vis[h][w] = true;
    while (!Q.empty()) {
        pii now = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = now.x + dx[i], nc = now.y + dy[i];
            if (nr - h + 1 < 1 || nr > R || nc - w + 1 < 1 || nc > C)
                continue;
            if (get(nr - h + 1, nc - w + 1, nr, nc))
                continue;
            if (!vis[nr][nc]) {
                vis[nr][nc] = true;
                Q.emplace(nr, nc);
            }
        }
    }
    return vis[R][C];
}

int main() {
    scanf("%d %d %d", &R, &C, &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        A[++a][++b] = 1;
    }
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    int ans = 0;
    for (int i = 1; i <= R; i++) {
        int l = 1, r = C;
        bool valid = false;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (chk(i, mid))
                l = mid, valid = true;
            else
                r = mid - 1;
        }
        if (valid)
            ans = max(ans, i * l);
    }
    printf("%d\n", ans);

    return 0;
}