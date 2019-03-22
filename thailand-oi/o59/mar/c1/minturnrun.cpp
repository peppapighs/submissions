#include <bits/stdc++.h>

#define iii tuple<int, int, int, int>

using namespace std;

const int N = 1e6+5;

int n, m, s;
int dx[3] = {0, 1, -1}, dy[3] = {1, 0, 0};
char S[N];
priority_queue<iii, vector<iii>, greater<iii> > Q;

int main() {
    scanf("%d %d %d", &n, &m, &s);
    vector<vector<int> > A(n+1, vector<int>(m+1, 0));
    vector<vector<vector<int> > > dp(n+1, vector<vector<int> >(m+1, vector<int>(3, INT_MAX)));
    for(int i = 1; i <= n; i++) {
        scanf(" %s", S+1);
        for(int j = 1; j <= m; j++) A[i][j] = (S[j] == '.');
    }
    dp[s][1][0] = 0;
    Q.emplace(0, s, 1, 0);
    while(!Q.empty()) {
        iii now = Q.top(); Q.pop();
        int d, r, c, f;
        tie(d, r, c, f) = now;
        if(d != dp[r][c][f]) continue;
        if(c == m) return !printf("%d\n", d);
        for(int i = 0; i < 3; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if(nr < 1 || nr > n || nc < 1 || nc > m || !A[nr][nc]) continue;
            if(dp[r][c][f] + (i != f) < dp[nr][nc][i]) {
                dp[nr][nc][i] = dp[r][c][f] + (i != f);
                Q.emplace(dp[nr][nc][i], nr, nc, i);
            }
        }
    }
    printf("-1\n");

    return 0;
}
