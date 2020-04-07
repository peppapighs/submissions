#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, m;
int par[N][18], dep[N];
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

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(1, 0);
    for(int i = 1, z; i <= m; i++) {
        vector<int> vec;
        scanf("%d", &z);
        for(int j = 1, a; j <= z; j++) {
            scanf("%d", &a);
            vec.emplace_back(a);
        }
        sort(vec.begin(), vec.end(), [&](int a, int b) {
            return dep[a] > dep[b];
        });
        int cur = vec[0];
        bool valid = true;
        for(int i = 1; i < z; i++) {
            if(lca(cur, vec[i]) == vec[i]) cur = vec[i];
            else {
                int now = par[vec[i]][0];
                if(lca(cur, now) == now) cur = now;
                else {
                    valid = false;
                    break;
                }
            }
        }
        if(valid) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}