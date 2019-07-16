#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 5e5+5;
 
int n, k, ans;
int qs[N], col[N];
vector<int> g[N], st[N];
 
int par[N][20], dep[N];
 
void init_lca(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for(int i = 1; i < 20; i++) par[u][i] = par[par[u][i-1]][i-1];
    for(int v : g[u]) if(v != p) init_lca(v, u);
}
 
int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 19; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 19; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    return par[a][0];
}
 
void solve_qs(int u, int p) {
    for(int v : g[u]) if(v != p) {
        solve_qs(v, u);
        qs[u] += qs[v];
    }
}
 
void flood(int u, int c, int &cnt) {
    col[u] = c;
    for(int v : g[u]) {
        if((!qs[v] && par[v][0] == u) || (par[u][0] == v && !qs[u])) {
            ++cnt;
            continue;
        }
        if(!col[v]) flood(v, c, cnt);
    }
}
 
int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    init_lca(1, 0);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        st[a].emplace_back(i);
    }
    for(int i = 1; i <= k; i++) for(int j = 1; j < st[i].size(); j++) {
        int l = lca(st[i][j-1], st[i][j]);
        ++qs[st[i][j-1]];
        ++qs[st[i][j]];
        qs[l] -= 2;
    }
    solve_qs(1, 0);
    for(int i = 1, ptr = 0; i <= n; i++) if(!col[i]) {
        int cnt = 0;
        flood(i, ++ptr, cnt);
        if(cnt == 1) ++ans;
    }
    printf("%d\n", (ans + 1) / 2);
 
    return 0;
}