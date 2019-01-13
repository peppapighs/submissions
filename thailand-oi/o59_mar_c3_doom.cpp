#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 105;

int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

int n, m, k;
int A[N][N], ap[35][35], dp[35][1<<15];

void bfs(int x, int y) {
    int st = A[x][y];
    int d[N][N];
    fill_n(d[0], N*N, 1e9);
    queue<iii> Q;

    Q.emplace(d[x][y] = 0, x, y);
    while(!Q.empty()) {
        iii now = Q.front(); Q.pop();

        int dist, r, c;
        tie(dist, r, c) = now;
        if(d[r][c] != dist) continue;
        
        for(int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if(nr < 1 || nr > n || nc < 1 || nc > m || A[nr][nc] == -1) continue;
            if(d[nr][nc] > d[r][c] + 1) {
                d[nr][nc] = d[r][c] + 1;
                if(A[nr][nc] >= 0) ap[st][A[nr][nc]] = d[nr][nc];
                else Q.emplace(d[nr][nc], nr, nc);
            }
        }
    }
}

int main() {
    fill_n(ap[0], 35*35, 1e9);
    fill_n(dp[0], 35*(1<<15), 1e9);

    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        char S[N];
        scanf(" %s", S+1);
        for(int j = 1; j <= m; j++) {
            if(S[j] == '.') A[i][j] = -2;
            if(S[j] == '#') A[i][j] = -1;
            if('a' <= S[j] && S[j] <= 'z') A[i][j] = S[j] - 'a' + 2;
            if('A' <= S[j] && S[j] <= 'Z') A[i][j] = S[j] - 'A' + k + 2;
            if(S[j] == 'z') A[i][j] = 0;
            if(S[j] == 'Z') A[i][j] = 1;
        }
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(A[i][j] >= 0) bfs(i, j);
    
    priority_queue<iii, vector<iii>, greater<iii> > Q;
    Q.emplace(dp[0][0] = 0, 0, 0);

    while(!Q.empty()) {
        iii now = Q.top(); Q.pop();
        
        int dist, u, bit;
        tie(dist, u, bit) = now;
        if(dp[u][bit] != dist) continue;
        if(u == 1) return !printf("%d\n", dp[u][bit]);

        for(int v = 0; v < 35; v++) {
            if(ap[u][v] == 1e9) continue;
            int w = ap[u][v];
            if(v == 0 || v == 1) {
                if(dp[v][bit] > dp[u][bit] + w) 
                    Q.emplace(dp[v][bit] = dp[u][bit] + w, v, bit);
            } else if(v >= k+2) {
                int pos = v - k - 2;
                if(!(bit & (1 << pos))) continue;
                if(dp[v][bit] > dp[u][bit] + w) 
                    Q.emplace(dp[v][bit] = dp[u][bit] + w, v, bit);
            } else {
                int pos = v - 2;
                int nbit = bit | (1 << pos);
                if(dp[v][nbit] > dp[u][bit] + w) 
                    Q.emplace(dp[v][nbit] = dp[u][bit] + w, v, nbit);
            }
        }
    }

    printf("-1\n");

    return 0;
}
