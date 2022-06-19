#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5 + 5;

int dsu[N], head[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int n, m, chk[N];
int par[N][18], dep[N];
vector<int> g[N];
vector<iii> Q;

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    chk[u] = true;
    for (int i = 1; i <= 17; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

int main() {
    iota(dsu, dsu + N, 0), iota(head, head + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, T, a, b; i <= m; i++) {
        scanf("%d %d", &T, &a);
        if (T == 1) {
            scanf("%d", &b);
            g[a].emplace_back(b), g[b].emplace_back(a);
        } else if (T == 3)
            scanf("%d", &b);
        Q.emplace_back(T, a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!chk[i])
            dfs(i, 0);
    for (iii q : Q) {
        int T, a, b;
        tie(T, a, b) = q;
        if (T == 1) {
            int now = head[find(b)];
            dsu[find(a)] = find(b);
            head[find(a)] = now;
        } else if (T == 2)
            head[find(a)] = a;
        else {
            int now = head[find(a)];
            int da = dep[a] + dep[now] - 2 * dep[lca(a, now)];
            int db = dep[b] + dep[now] - 2 * dep[lca(b, now)];
            if (da < db)
                printf("%d\n", a);
            else
                printf("%d\n", b);
        }
    }

    return 0;
}