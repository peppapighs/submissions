#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>

using namespace std;

const int N = 2e5 + 5;

int n, m;
int x[N], y[N], l[N], par[N][19], dep[N];
long qs[N];
map<pii, int> mp;
vector<int> g[N];

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i <= 18; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 18; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 18; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

int pre(int a, int l) {
    if (a == l)
        return -1;
    for (int i = 18; ~i; i--)
        if (dep[par[a][i]] > dep[l])
            a = par[a][i];
    return a;
}

void process(int u, int p) {
    for (int v : g[u])
        if (v != p) {
            qs[v] += qs[u];
            process(v, u);
        }
}

long ans;

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(1, 0);
    for (int i = n; i <= m; i++) {
        scanf("%d %d", x + i, y + i);
        l[i] = lca(x[i], y[i]);
        int pre_x = pre(x[i], l[i]), pre_y = pre(y[i], l[i]);
        if (~pre_x)
            ans -= qs[pre_x]++ + 1;
        if (~pre_y)
            ans -= qs[pre_y]++ + 1;
        if (~pre_x && ~pre_y) {
            if (pre_x > pre_y)
                swap(pre_x, pre_y);
            ans -= mp[pii(pre_x, pre_y)]++;
        }
    }
    process(1, 0);
    for (int i = n; i <= m; i++)
        ans += qs[x[i]] + qs[y[i]] - 2ll * qs[l[i]];
    printf("%lld\n", ans);

    return 0;
}