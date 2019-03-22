#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e4+5;

int n, q;
int par[N][17], dep[N], d[N];
vector<pii> g[N];

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for(int i = 1; i < 17; i++) par[u][i] = par[par[u][i-1]][i-1];
    for(pii v : g[u]) if(v.x != p) {
        d[v.x] = d[u] + v.y;
        dfs(v.x, u);
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 16; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 16; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    return par[a][0];
}

int dist(int a, int b) { return d[a] + d[b] - 2*d[lca(a, b)]; }

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    dfs(0, 0);
    scanf("%d", &q);
    while(q--) {
        int A[5];
        for(int i = 0; i < 5; i++) scanf("%d", A+i);
        sort(A, A+5, [&](const int &a, const int &b) {
            return dep[a] > dep[b];
        });
        int rt = A[0], ret;
        for(int i = 1; i < 5; i++) rt = lca(rt, A[i]);
        ret = dist(A[0], rt);
        for(int i = 1; i < 5; i++) {
            int low = rt;
            for(int j = 0; j < i; j++) if(dep[lca(A[i], A[j])] > dep[low]) low = lca(A[i], A[j]);
            ret += dist(A[i], low);
        }
        printf("%d\n", ret);
    }

    return 0;
}