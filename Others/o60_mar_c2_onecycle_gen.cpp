#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e3 + 5;

int n, x, y, z;
vector<pii> g[N];
int ap[N][N];

int dfs(int u, int p, int d = 0) {
    if (u == y)
        return d;
    for (pii v : g[u])
        if (v.x != p)
            return dfs(v.x, u, d + v.y);
}

int main() {
    fill_n(ap[0], N * N, (int)1e9);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
        ap[a][b] = w, ap[b][a] = w;
    }
    scanf("%d %d %d", &x, &y, &z);
    ap[x][y] = ap[y][x] = z;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            printf("%d ", ap[i][j]);
        }
        printf("\n");
    }

    return 0;
}
