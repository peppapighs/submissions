#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int n, m, vis[N<<1], inst[N<<1];
int dsu[N<<1], num[N<<1], deg[N<<1];
char A[N][N];
vector<int> g[N<<1];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

bool cycle(int u) {
    vis[u] = inst[u] = 1;
    for(int v : g[u]) if((!vis[v] && cycle(v)) || inst[v]) return true;
    inst[u] = 0;
    return false;
}

void dfs(int u, int k) {
    if(num[u] > k) return;
    num[u] = max(num[u], k);
    for(int v : g[u]) if(k + 1 > num[v]) dfs(v, k+1); 
}

int main() {
    iota(dsu, dsu + (N<<1), 0);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf(" %s", A[i]+1);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        if(A[i][j] == '=') dsu[find(n + j)] = find(i);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        if(A[i][j] == '<') {
            if(find(i) == find(n + j)) return !printf("No\n");
            g[find(i)].emplace_back(find(n + j)), ++deg[find(n + j)];
        }
        if(A[i][j] == '>') {
            if(find(i) == find(n + j)) return !printf("No\n");
            g[find(n + j)].emplace_back(find(i)), ++deg[find(i)];
        }
    }
    for(int i = 1; i <= n + m; i++) if(!vis[find(i)] && cycle(i)) return !printf("No\n");
    for(int i = 1; i <= n + m; i++) if(!deg[find(i)]) dfs(find(i), 1); 
    printf("Yes\n");
    for(int i = 1; i <= n; i++) printf("%d ", num[find(i)]);
    printf("\n");
    for(int i = n+1; i <= n+m; i++) printf("%d ", num[find(i)]);

    return 0;
}