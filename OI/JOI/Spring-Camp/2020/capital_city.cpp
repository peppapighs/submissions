#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, k;
int C[N], par[N], dep[N], dsu[N];
vector<int> g[N], col[N];
set<int> S[N];

void dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    for(int v : g[u]) if(v != p) dfs(v, u);
}

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int main() {
    iota(dsu, dsu + N, 0);

    scanf("%d %d", &n, &k);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        scanf("%d", C + i);
        S[i].emplace(C[i]);
        col[C[i]].emplace_back(i);
    }
    for(int i = 1; i <= k; i++) if(col[i].size() > 1) {
        printf("now = %d\n", i);
        for(int j = 1; j < col[i].size(); j++) {
            int a = find(col[i][j-1]), b = find(col[i][j]);
            while(a != b) {
                if(dep[a] < dep[b]) swap(a, b);
                int x = find(par[a]);
                if(S[x].size() < S[a].size()) swap(S[x], S[a]);
                for(int c : S[a]) S[x].emplace(c);
                a = dsu[a] = x;
            }
        }
        for(int c : S[find(col[i][0])]) printf("%d ", c);
        printf("\n");
    }
    int ans = 1e9;
    for(int i = 1; i <= n; i++) if(find(i) == i) ans = min(ans, (int)S[i].size() - 1);
    printf("%d\n", ans);

    return 0;
}