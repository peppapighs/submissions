#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 805;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int n, s;
int sx, sy, bee[N][N], d[N][N];
char A[N][N];

void gen_bee() {
    queue<pii> Q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (A[i][j] == 'M')
                sx = i, sy = j;
            if (A[i][j] == 'H') {
                bee[i][j] = 0;
                Q.emplace(i, j);
            }
        }
    while (!Q.empty()) {
        pii u = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = u.x + dx[i], nc = u.y + dy[i];
            if (nr < 1 || nr > n || nc < 1 || nc > n)
                continue;
            if (A[nr][nc] != 'G' && A[nr][nc] != 'M')
                continue;
            if (bee[u.x][u.y] + 1 < bee[nr][nc]) {
                bee[nr][nc] = bee[u.x][u.y] + 1;
                Q.emplace(nr, nc);
            }
        }
    }
}

bool chk(int mid) {
    if (1ll * mid >= bee[sx][sy])
        return false;
    fill_n(d[0], N * N, 1e9 + 1);
    queue<pii> Q;
    d[sx][sy] = 0;
    Q.emplace(sx, sy);
    while (!Q.empty()) {
        pii u = Q.front();
        Q.pop();
        if (A[u.x][u.y] == 'D')
            return true;
        for (int i = 0; i < 4; i++) {
            int nr = u.x + dx[i], nc = u.y + dy[i];
            if (nr < 1 || nr > n || nc < 1 || nc > n)
                continue;
            if (A[nr][nc] != 'M' && A[nr][nc] != 'G' && A[nr][nc] != 'D')
                continue;
            if (d[u.x][u.y] + 1 < d[nr][nc] &&
                1ll * d[u.x][u.y] + 1 < 1ll * s * (bee[nr][nc] - mid)) {
                d[nr][nc] = d[u.x][u.y] + 1;
                Q.emplace(nr, nc);
            }
        }
    }
    return false;
}

int main() {
    fill_n(bee[0], N * N, 1e9 + 1);
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++)
        scanf(" %s", A[i] + 1);
    gen_bee();

    int l = 0, r = n * n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (chk(mid))
            l = mid;
        else
            r = mid - 1;
    }
    if (chk(l))
        printf("%d\n", l);
    else
        printf("-1\n");

    return 0;
}