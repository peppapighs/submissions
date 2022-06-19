#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

int n, m, c;
int disc[N], low[N], chk[N], comp[N], rnk[N], cnt[N], deg[N], sz[N];
vector<int> g[N], C[N];

void dfs(int u) {
    static int idx = 0;
    static stack<int> S;
    disc[u] = low[u] = ++idx;
    S.emplace(u);
    chk[u] = true;
    for (int v : g[u]) {
        if (!disc[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (chk[v])
            low[u] = min(low[u], disc[v]);
    }
    if (low[u] == disc[u]) {
        int v;
        ++c;
        do {
            v = S.top(), S.pop();
            comp[v] = c, chk[v] = false;
            ++sz[c];
        } while (v != u);
    }
}

void find(int u, int x) {
    rnk[u] = max(rnk[u], x);
    for (int v : C[u])
        find(v, x + 1);
}

int main() {
    scanf("%d %d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        ++a, ++b;
        g[a].emplace_back(b);
    }
    for (int i = 1; i <= n; i++)
        if (!disc[i])
            dfs(i);
    for (int i = 1; i <= n; i++)
        for (int v : g[i])
            if (comp[i] != comp[v]) {
                C[comp[i]].emplace_back(comp[v]);
                ++deg[comp[v]];
            }
    for (int i = 1; i <= c; i++)
        if (!deg[i])
            find(i, 1);
    for (int i = 1; i <= c; i++)
        cnt[rnk[i]] += sz[i];
    for (int i = 1; cnt[i]; i++)
        printf("%d ", cnt[i]);
    printf("\n");

    return 0;
}
