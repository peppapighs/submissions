#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 705;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char A[N][N];

bool border(int r, int c) { return r < 1 || r > n || c < 1 || c > m; }

template <typename T> void bfs(int sr, int sc, int d[N][N], const T &f) {
    fill_n(d[0], N * N, 1e9);

    queue<iii> Q;
    Q.emplace(sr, sc, d[sr][sc] = 0);
    while (!Q.empty()) {
        iii now = Q.front();
        Q.pop();
        int r, c, dist;
        tie(r, c, dist) = now;
        if (d[r][c] != dist)
            continue;
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if (border(nr, nc) || A[nr][nc] == 'I')
                continue;
            if (dist + 1 < d[nr][nc] && !f(nr, nc, dist + 1))
                Q.emplace(nr, nc, d[nr][nc] = dist + 1);
        }
    }
}

int sr, sc, er, ec, vr, vc;
int dv[N][N], ds[N][N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf(" %s", A[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (A[i][j] == 'Y')
                sr = i, sc = j, A[i][j] = '.';
            if (A[i][j] == 'T')
                er = i, ec = j, A[i][j] = '.';
            if (A[i][j] == 'V')
                vr = i, vc = j, A[i][j] = '.';
        }
    }
    bfs(vr, vc, dv, [&](int x, int y, int d) { return false; });
    bfs(sr, sc, ds, [&](int x, int y, int d) {
        for (int i = 0; i < 4; i++) {
            int r = x, c = y;
            while (!border(r, c)) {
                if (A[r][c] == 'I')
                    break;
                if (dv[r][c] <= d)
                    return true;
                r += dx[i], c += dy[i];
            }
        }
        return false;
    });
    if (ds[er][ec] != 1e9)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}