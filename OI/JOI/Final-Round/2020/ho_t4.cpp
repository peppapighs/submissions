#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 205;
const int M = 5e4+5;

int n, m;
vector<pii> g[N];
array<int, 4> E[M];

long dp[N];
priority_queue<pii, vector<pii>, greater<pii> > Q;

long dijkstra(int s, int e, int i) {
    fill_n(dp, N, 1e18);
    Q.emplace(dp[s] = 0, s);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(dp[u.y] != u.x) continue;
        for(pii v : g[u.y]) {
            if(v.y == i) continue;
            if(u.x + E[v.y][2] < dp[v.x])
                Q.emplace(dp[v.x] = u.x + E[v.y][2], v.x);
        }
        if(u.y == E[i][1] && u.x + E[i][2] < dp[E[i][0]])
            Q.emplace(dp[E[i][0]] = u.x + E[i][2], E[i][0]);
    }
    return dp[e];
}

long ap[N][N];

int main() {
    fill_n(ap[0], N * N, 1e18);

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) ap[i][i] = 0;
    for(int i = 1, a, b, c, d; i <= m; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        E[i] = {a, b, c, d};
        g[a].emplace_back(b, i);
        ap[a][b] = min(ap[a][b], (long)c);
    }
    for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);

    long ans = ap[1][n] + ap[n][1];
    for(int i = 1; i <= m; i++) {
        long d1 = min(ap[1][n], ap[1][E[i][1]] + E[i][2] + ap[E[i][0]][n]);
        long d2 = min(ap[n][1], ap[n][E[i][1]] + E[i][2] + ap[E[i][0]][1]);
        if(d1 + d2 + E[i][3] < ans) 
            ans = min(ans, dijkstra(1, n, i) + dijkstra(n, 1, i) + E[i][3]);
    }

    if(ans >= 1e18) printf("-1\n");
    else printf("%lld\n", ans);

    return 0;
}