#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int dsu[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int n, m, p;
int a[N], b[N];
vector<int> g[N];

int pre[N], low[N];
bitset<N> br;

void tarjan(int u, int p) {
    static int idx = 0;
    pre[u] = low[u] = ++idx;
    for(int i : g[u]) if(i != p) {
        int v = a[i] ^ b[i] ^ u;
        if(!pre[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(low[v] > pre[u]) br[i] = true;
        } else low[u] = min(low[u], pre[v]);
    }
}

int dp[N], dep[N];

void dfs(int u, int p) {
    for(int i : g[u]) if(i != p) {
        int v = find(a[i]) ^ find(b[i]) ^ u;
        dep[v] = dep[u] + 1;
        dfs(v, i);
        dp[u] += dp[v];
    }
}

int main() {
    iota(dsu, dsu+N, 0);

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d %d", a+i, b+i);
        g[a[i]].emplace_back(i);
        g[b[i]].emplace_back(i);
    }

    for(int i = 1; i <= n; i++) if(!pre[i]) tarjan(i, 0); 
    for(int i = 1; i <= m; i++) if(!br[i]) dsu[find(a[i])] = find(b[i]);
    for(int i = 1; i <= n; i++) g[i].clear();
    for(int i = 1; i <= m; i++) if(br[i]) {
        g[find(a[i])].emplace_back(i);
        g[find(b[i])].emplace_back(i);
    }
    
    scanf("%d", &p);
    for(int i = 1, x, y; i <= p; i++) {
        scanf("%d %d", &x, &y);
        ++dp[find(x)], --dp[find(y)];
    }
    for(int i = 1; i <= n; i++) if(!dep[find(i)]) {
        dep[find(i)] = 1;
        dfs(find(i), 0);
    }
    for(int i = 1; i <= m; i++) {
        if(!br[i]) printf("B");
        else {
            int u = dep[find(a[i])] > dep[find(b[i])] ? a[i] : b[i];
            if(dp[find(u)] == 0) printf("B");
            else if((dp[find(u)] > 0) == (u == a[i])) printf("R");
            else printf("L");
        } 
    }
    printf("\n");

    return 0;
}