#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, dp[N][4];
vector<pii> g[N];

void dfs(int u, int p) {
    for(pii v : g[u]) if(v.x != p) dfs(v.x, u);

    vector<int> V, W, M;
    vector<pii> V1, V2;
    for(pii v : g[u]) if(v.x != p) {
        V.emplace_back(v.x), W.emplace_back(v.y);
        M.emplace_back(max(dp[v.x][0], dp[v.x][2] + v.y));
        dp[u][0] += M.back();
        V1.emplace_back(M.back() - dp[v.x][0] - v.y, v.x);
        V2.emplace_back(M.back() - dp[v.x][1] - v.y, v.x);
    }
    sort(V1.begin(), V1.end()), sort(V2.begin(), V2.end());
    dp[u][1] = dp[u][2] = dp[u][3] = -1e9;

    for(int i = 0; i < min(2, (int)V1.size()); i++) for(int j = 0; j < min(2, (int)V2.size()); j++)
        if(V1[i].y != V2[j].y) dp[u][1] = max(dp[u][1], dp[u][0] - V1[i].x - V2[j].x);

    if(V1.size() >= 2) dp[u][1] = max(dp[u][1], dp[u][0] - V1[0].x - V1[1].x);

    for(int i = 0; i < V.size(); i++) {
        dp[u][2] = max(dp[u][2], dp[u][0] - M[i] + dp[V[i]][0] + W[i]);
        dp[u][3] = max(dp[u][3], dp[u][0] - M[i] + dp[V[i]][1] + W[i]);
    }

    for(int i = 0; i < V.size(); i++) 
        dp[u][1] = max(dp[u][1], dp[u][0] - M[i] + max(dp[V[i]][1], dp[V[i]][3] + W[i]));
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    dfs(1, 1);
    printf("%d\n", max(dp[1][0], dp[1][1]));

    return 0;
}
