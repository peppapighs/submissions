#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const int N = 305;

int ptr, cc[N][N], qs[N][N], chk[N*N];
vector<pii> vec;

int n, m, q;
int A[N][N], dp[3][N][N];

// 0 - Corner Vertices
// 1 - Horizontal Edges
// 2 - Vertical Edges

bool inside(pii p, int r1, int r2, int c1, int c2) {
    return r1 <= p.x && p.x <= r2 && c1 <= p.y && p.y <= c2;
}

int get(int i, int x1, int x2, int y1, int y2) {
    if(x1 > x2 || y1 > y2) return 0;
    return dp[i][x2][y2] - dp[i][x1-1][y2] - dp[i][x2][y1-1] + dp[i][x1-1][y1-1];
}

int sum(int x1, int x2, int y1, int y2) {
    if(x1 > x2 || y1 > y2) return 0;
    return qs[x2][y2] - (x1 > 0 ? qs[x1-1][y2] : 0) - (y1 > 0 ? qs[x2][y1-1] : 0) + (x1 > 0 && y1 > 0 ? qs[x1-1][y1-1] : 0);
}

void dfs(int r, int c, int k) {
    cc[r][c] = k;
    for(int x = 0; x < 4; x++) {
        int nr = r + dx[x], nc = c + dy[x];
        if(A[nr][nc] && !cc[nr][nc]) dfs(nr, nc, k);
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    char S[N];
    for(int i = 1; i <= n; i++) {
        scanf(" %s", S + 1);
        for(int j = 1; j <= m; j++) A[i][j] = (S[j] == '1');
    }

    for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= m + 1; j++) {
        if(A[i-1][j] != A[i][j] || A[i-1][j-1] != A[i][j] || A[i][j-1] != A[i][j]) ++dp[0][i][j];
        if(A[i-1][j] != A[i][j]) ++dp[1][i][j];
        if(A[i][j-1] != A[i][j]) ++dp[2][i][j];

        if(!cc[i][j] && A[i][j]) {
            ++qs[i][j], vec.emplace_back(i, j);
            dfs(i, j, ++ptr);
        }
    }

    for(int k = 0; k < 3; k++) for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= m + 1; j++)
        dp[k][i][j] += dp[k][i-1][j] + dp[k][i][j-1] - dp[k][i-1][j-1];
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        qs[i][j] += qs[i-1][j] + qs[i][j-1] - qs[i-1][j-1];

    while(q--) {
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

        int v = get(0, r1+1, r2, c1+1, c2);
        int e = get(1, r1+1, r2, c1, c2) + get(2, r1, r2, c1+1, c2);
        int c = sum(r1+1, r2-1, c1+1, c2-1);

        if(r2 - r1 > 1 && c2 - c1 > 1) {
            for(int i = r1; i <= r2; i++) {
                if(A[i][c1] && !chk[cc[i][c1]]) {
                    pii a = vec[cc[i][c1]-1];
                    if(inside(a, r1+1, r2-1, c1+1, c2-1)) --c;
                    chk[cc[i][c1]] = 1;
                }
                if(A[i][c2] && !chk[cc[i][c2]]) {
                    pii a = vec[cc[i][c2]-1];
                    if(inside(a, r1+1, r2-1, c1+1, c2-1)) --c;
                    chk[cc[i][c2]] = 1;
                }
            }
            for(int i = c1+1; i <= c2-1; i++) {
                if(A[r1][i] && !chk[cc[r1][i]]) {
                    pii a = vec[cc[r1][i]-1];
                    if(inside(a, r1+1, r2-1, c1+1, c2-1)) --c;
                    chk[cc[r1][i]] = 1;
                }
                if(A[r2][i] && !chk[cc[r2][i]]) {
                    pii a = vec[cc[r2][i]-1];
                    if(inside(a, r1+1, r2-1, c1+1, c2-1)) --c;
                    chk[cc[r2][i]] = 1;
                }
            }
            for(int i = r1; i <= r2; i++) chk[cc[i][c1]] = chk[cc[i][c2]] = 0;
            for(int i = c1; i <= c2; i++) chk[cc[r1][i]] = chk[cc[r2][i]] = 0;
        }

        printf("%d\n", 1 - v + e + c);
    } 

    return 0;
}