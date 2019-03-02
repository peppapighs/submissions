#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int T;
int n, dp[N][3];
vector<int> g[N];

void dfs(int u, int p) {
       int ret = 0;
       for(int v : g[u]) if(v != p) {
              dfs(v, u);
              dp[u][0] += max({dp[v][0], dp[v][1], dp[v][2]});
              dp[u][1] += dp[v][0];
              ret += dp[v][0];
       }
       for(int v : g[u]) if(v != p) dp[u][2] = max(dp[u][2], ret - dp[v][0] + dp[v][1]);
       ++dp[u][1], ++dp[u][2];
}

int main() {
       scanf("%d", &T);
       while(T--) {
              scanf("%d", &n);         
              for(int i = 1; i < N; i++) g[i].clear();
              for(int i = 1, a, b; i < n; i++) {
                     scanf("%d %d", &a, &b);
                     g[a].emplace_back(b), g[b].emplace_back(a);
              }
              memset(dp, 0, sizeof dp);
              dfs(1, 1);
              printf("%d\n", max({dp[1][0], dp[1][1], dp[1][2]}));
       }

       return 0;
}