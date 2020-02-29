#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3+5;
const int M = 1e9+7;

struct UnionFind {
    int par[N];

    UnionFind() { iota(par, par + N, 0); }

    int find(int x) { return par[x] == x ? x : find(par[x]); }

    void unite(int a, int b) {
        if(find(a) == find(b)) return;
        par[find(a)] = find(b);
    }
} dsu[N];

int n, m;
int par[N][N], id[N][N], deg[N * N];
long dp[N * N];
char A[N][N];
vector<int> g[N * N];

void dfs(int u) {
    dp[u] = 1;
    for(int v : g[u]) {
        dfs(v);
        dp[u] = dp[u] * dp[v] % M;
    }
    dp[u] = (dp[u] + 1) % M;
}

int main() {
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf(" %s", A[i-1]);
    --n, --m;

    for(int i = n; i; i--) {
        for(int j = 1; j <= m; j++) if(A[i][j-1] == '.' && A[i][j] == '.')
            dsu[i].unite(j-1, j);
        for(int j = 1; j <= m; j++) if(A[i][j] == '.' && A[i+1][j] == '.') {
            int now = dsu[i].find(j), pre = dsu[i+1].find(j);
            if(!par[i+1][pre]) par[i+1][pre] = now;
            else dsu[i].unite(now, par[i+1][pre]);
        }
    }

    int idx = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) if(A[i][j] == '.' && dsu[i].find(j) == j)
            id[i][j] = ++idx;
        for(int j = 1; j <= m; j++) if(A[i][j] == '.' && dsu[i].find(j) == j) if(par[i][j]) {
            g[id[i-1][dsu[i-1].find(par[i][j])]].emplace_back(id[i][j]);
            ++deg[id[i][j]];
        }
    }
    long ans = 1;
    for(int i = 1; i <= idx; i++) if(deg[i] == 0) {
        dfs(i);
        ans = ans * dp[i] % M;
    }
    printf("%lld\n", ans);

    return 0;
}