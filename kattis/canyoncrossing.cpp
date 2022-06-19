#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int R, C, k;
int A[N][N], dp[N][N];
deque<pii> Q;

int main() {
    scanf("%d %d %d", &R, &C, &k);
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            scanf("%d", &A[i][j]);

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) / 2;

        fill_n(dp[0], N * N, 1e9);
        for (int i = 1; i <= C; i++) {
            if (A[1][i] < mid) {
                dp[1][i] = 1;
                Q.emplace_back(1, i);
            } else {
                dp[1][i] = 0;
                Q.emplace_front(1, i);
            }
        }

        while (!Q.empty()) {
            pii now = Q.front();
            Q.pop_front();
            for (int i = 0; i < 4; i++) {
                int nr = now.x + dx[i], nc = now.y + dy[i];
                if (nr < 1 || nr > R || nc < 1 || nc > C)
                    continue;
                if (dp[nr][nc] > dp[now.x][now.y] + (A[nr][nc] < mid)) {
                    dp[nr][nc] = dp[now.x][now.y] + (A[nr][nc] < mid);
                    if (A[nr][nc] < mid)
                        Q.emplace_back(nr, nc);
                    else
                        Q.emplace_front(nr, nc);
                }
            }
        }

        bool valid = false;
        for (int i = 1; i <= C; i++)
            valid |= (dp[R][i] <= k);
        if (valid)
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", l);

    return 0;
}