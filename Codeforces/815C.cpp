#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e3+5;

int n, b, sz[N];
long cost[N], dis[N], dp[N][N][2];
vector<int> g[N];

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(v != p) sz[u] += getsz(v, u); return sz[u]; }

void dfs(int u, int p) {
    dp[u][0][0] = 0;
    dp[u][1][1] = dis[u], dp[u][1][0] = cost[u];
    int now = 1;
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        for(int i = now; ~i; i--) for(int j = 0; j <= sz[v]; j++) {
            dp[u][i + j][0] = min(dp[u][i + j][0], dp[u][i][0] + dp[v][j][0]);
            dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[v][j][1]);
        }
        now += sz[v];
    }
    for(int i = 0; i <= sz[u]; i++) dp[u][i][1] = min(dp[u][i][1], dp[u][i][0]);
}

int main() {
    fill_n(dp[0][0], N*N*2, 1e12);
    scanf("%d %d", &n, &b);
    for(int i = 1, a; i <= n; i++) {
        scanf("%lld %lld", cost+i, dis+i);
        dis[i] = cost[i] - dis[i];
        if(i > 1) {
            scanf("%d", &a);
            g[a].emplace_back(i), g[i].emplace_back(a);
        }
    }
    getsz(1, 1);
    dfs(1, 1);
    for(int i = n; i; i--) if(dp[1][i][1] <= b) return !printf("%d\n", i);
    printf("0\n");

    return 0;
}