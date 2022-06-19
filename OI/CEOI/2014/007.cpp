#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, s, d, a, b;
int da[N], db[N], dp[N];
vector<int> g[N];

void bfs(int src, int d[]) {
    fill_n(d, N, 1e9);

    queue<int> Q;
    Q.emplace(src), d[src] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : g[u])
            if (d[u] + 1 < d[v])
                Q.emplace(v), d[v] = d[u] + 1;
    }
}

int dep[N];

int solve(int src) {
    memset(dep, -1, sizeof dep);

    queue<int> Q;
    Q.emplace(src), dep[src] = 0;
    int ret = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        ret = max(ret, dep[u]);
        for (int v : g[u])
            if (da[v] == da[u] - 1 && da[v] == db[v] && dep[v] == -1)
                dep[v] = dep[u] + 1, Q.emplace(v);
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &s, &d, &a, &b);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d %d", &u, &v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    bfs(a, da), bfs(b, db);

    int w1 = da[d] - da[s], w2 = db[d] - db[s];
    if (w1 != w2)
        printf("%d\n", max(-1, min(w1, w2)));
    else
        printf("%d\n", max(-1, w1 - (w1 + solve(s) < solve(d))));

    return 0;
}