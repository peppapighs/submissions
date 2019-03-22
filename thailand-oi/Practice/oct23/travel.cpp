#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, m;
int dep[N], par[N][18];
vector<int> g[N];

void dfs(int u, int p) {
        dep[u] = dep[p] + 1, par[u][0] = p;
        for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
        for(int v : g[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
        if(dep[a] < dep[b]) swap(a, b);
        for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
        if(a == b) return a;
        for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
        return par[a][0];
}

int d(int a, int b) { return dep[a] + dep[b] - 2*dep[lca(a, b)]; }

int main() {
        scanf("%d", &n);
        for(int i = 1, a, b; i < n; i++) {
                scanf("%d %d", &a, &b);
                g[a].emplace_back(b), g[b].emplace_back(a);
        }
        dfs(1, 1);
        scanf("%d", &m);
        int ans = 0, now = 1;
        while(m--) {
                int a;
                scanf("%d", &a);
                ans += d(now, a);
                now = a;
        }
        printf("%d\n", ans);

        return 0;
}
