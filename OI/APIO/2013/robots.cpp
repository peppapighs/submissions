#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 505;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

struct item {
    int r, c, id;
    item(int r, int c, int id) : r(r), c(c), id(id) {}
};

int n, w, h, mp[10][10], dp[45][N][N];
char A[N][N];
pii nex[4][N][N];
vector<item> process[45];

pii find_next(int r, int c, int dir) {
    if(nex[dir][r][c] == pii(-1, -1) && A[r][c] != 'x') {
        int ndir = dir;
        if(A[r][c] == 'C') ndir = (dir + 1) % 4;
        if(A[r][c] == 'A') ndir = (dir + 3) % 4;
        int nr = r + dx[ndir], nc = c + dy[ndir];
        if(nr < 1 || nr > h || nc < 1 || nc > w || A[nr][nc] == 'x')
            nex[dir][r][c] = pii(r, c);
        else nex[dir][r][c] = find_next(nr, nc, ndir);
    }
    return nex[dir][r][c];
}

int main() {
    fill_n(nex[0][0], N * N * 4, pii(-1, -1));
    fill_n(dp[0][0], 45 * N * N, 1e9);

    scanf("%d %d %d", &n, &w, &h);
    for(int i = 1; i <= h; i++) scanf(" %s", A[i] + 1);

    for(int i = 1; i <= h; i++) 
        for(int j = 1; j <= w; j++)
            for(int k = 0; k < 4; k++)
                find_next(i, j, k);
    for(int i = 1, ptr = 0; i <= n; i++) for(int j = i; j <= n; j++)
        mp[i][j] = ptr++;

    queue<item> Q;
    for(int k = 1; k <= n; k++) for(int x = 1, y = k; y <= n; x++, y++) {
        vector<item> proc;
        for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) {
            if(A[i][j] == 'x') continue;
            if(k == 1) {
                if(A[i][j] == '0' + x) {
                    int now = mp[A[i][j] - '0'][A[i][j] - '0'];
                    proc.emplace_back(i, j, now);
                    dp[now][i][j] = 0;
                }
            } else {
                int now = mp[x][y];
                for(int l = x; l < y; l++) {
                    int L = mp[x][l], R = mp[l + 1][y];
                    dp[now][i][j] = min(dp[now][i][j], dp[L][i][j] + dp[R][i][j]);
                }
                proc.emplace_back(i, j, now);
            }
        }

        sort(proc.begin(), proc.end(), [&](item &a, item &b) {
            return dp[a.id][a.r][a.c] < dp[b.id][b.r][b.c];
        });
        for(item &now : proc) {
            Q.emplace(now);
            while(!Q.empty()) {
                item u = Q.front(); Q.pop();
                for(int i = 0; i < 4; i++) {
                    int nr = u.r + dx[i], nc = u.c + dy[i];
                    if(nr < 1 || nr > h || nc < 1 || nc > w || A[nr][nc] == 'x')
                        continue;
                    pii v = nex[i][nr][nc];
                    if(dp[u.id][u.r][u.c] + 1 < dp[u.id][v.x][v.y]) {
                        dp[u.id][v.x][v.y] = dp[u.id][u.r][u.c] + 1;
                        Q.emplace(v.x, v.y, u.id);
                    }
                }
            }
        }
    }
    int ans = 1e9;
    for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++)
        ans = min(ans, dp[mp[1][n]][i][j]); 
    if(ans != 1e9) printf("%d\n", ans);
    else printf("-1\n");

    return 0;
}