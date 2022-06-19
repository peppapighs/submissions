#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e3 + 5;

struct node {
    int r, c;
    int a, b;
    node(int r, int c, int a, int b) : r(r), c(c), a(a), b(b) {}
    friend bool operator<(const node &a, const node &b) {
        return pii(a.a, a.b) > pii(b.a, b.b);
    }
};

int n, m;
int sr, sc, x, y;
int A[N][N], vis[N][N];
pii dp[N][N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    fill_n(dp[0], N * N, pii(2e9, 2e9));
    scanf("%d %d", &n, &m);
    scanf("%d %d", &sr, &sc);
    scanf("%d %d", &x, &y);
    for (int i = 1; i <= n; i++) {
        char s[N];
        scanf(" %s", s + 1);
        for (int j = 1; j <= m; j++)
            A[i][j] = (s[j] == '*');
    }
    priority_queue<node> Q;
    dp[sr][sc] = pii(0, 0);
    vis[sr][sc] = true;
    Q.emplace(sr, sc, 0, 0);
    while (!Q.empty()) {
        node now = Q.top();
        Q.pop();
        int r = now.r, c = now.c, a = now.a, b = now.b;
        if (dp[r][c] > pii(a, b))
            continue;
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            int left = a + (i == 3), right = b + (i == 1);
            if (nr < 1 || nr > n || nc < 1 || nc > m || A[nr][nc] ||
                vis[nr][nc])
                continue;
            if (left <= x && right <= y)
                dp[nr][nc] = pii(left, right), Q.emplace(nr, nc, left, right),
                vis[nr][nc] = true;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (dp[i][j].x <= x && dp[i][j].y <= y)
                ans++;
    printf("%d\n", ans);

    return 0;
}
