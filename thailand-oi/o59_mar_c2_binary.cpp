#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n;
int dp[N];
vector<int> g[N];

void dfs(int u, int p) {
    vector<int> V;
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        V.emplace_back(dp[v]);
    }
    sort(V.begin(), V.end(), greater<int>());
    if(!V.empty()) {
        if(V.size() <= 2) dp[u] = V[0] + 1;
        else {
            int lvl = 1, k;
            while(1 << lvl < V.size()) ++lvl;
            k = (1 << lvl) - V.size();
            for(int i = 0; i < k && i < V.size(); i++) dp[u] = max(dp[u], V[i] + lvl - 1);
            for(int i = k; i < V.size(); i++) dp[u] = max(dp[u], V[i] + lvl);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[p].emplace_back(i), g[i].emplace_back(p);
    } 
    dfs(1, 1);
    printf("%d\n", dp[1]);

    return 0;
}