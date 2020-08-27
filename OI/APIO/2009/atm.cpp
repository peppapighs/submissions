#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;

int n, m, cc, s, p;
int pre[N], low[N], id[N];
bitset<N> chk;
vector<int> g[N], atm;

void tarjan(int u) {
    static int idx = 0;
    static vector<int> S;
    pre[u] = low[u] = ++idx, chk[u] = 1;
    S.emplace_back(u);
    for(int v : g[u]) {
        if(!pre[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(chk[v]) low[u] = min(low[u], pre[v]);
    }
    if(low[u] == pre[u]) {
        int v; ++cc;
        do {
            v = S.back(); S.pop_back();
            id[v] = cc, chk[v] = 0;
        } while(v != u);
    }
}

int u[N], v[N], cash[N], dp[N];
vector<int> deg(N);

int main() {
    fill_n(dp, N, -1e9);

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d %d", u + i, v + i);
        ++deg[u[i]];
    }
    for(int i = 1; i <= n; i++) g[i].reserve(deg[i]);
    for(int i = 1; i <= m; i++) g[u[i]].emplace_back(v[i]);
    for(int i = 1; i <= n; i++) if(!pre[i]) tarjan(i);
    for(int i = 1; i <= n; i++) g[i].clear();

    deg = vector<int>(cc + 1);

    vector<pii> E;
    for(int i = 1; i <= m; i++) if(id[u[i]] != id[v[i]])
        E.emplace_back(id[u[i]], id[v[i]]);
    sort(E.begin(), E.end());
    E.resize(unique(E.begin(), E.end()) - E.begin());

    for(pii &e : E) g[e.x].emplace_back(e.y), ++deg[e.y];

    for(int i = 1, a; i <= n; i++) scanf("%d", &a), cash[id[i]] += a;

    scanf("%d %d", &s, &p), s = id[s];
    for(int i = 1, a; i <= p; i++) scanf("%d", &a), atm.emplace_back(a);

    vector<int> topo;
    queue<int> Q;
    for(int i = 1; i <= cc; i++) if(!deg[i]) Q.emplace(i);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        topo.emplace_back(u);
        for(int v : g[u]) if(!--deg[v])
            Q.emplace(v);
    }

    dp[s] = cash[s];
    for(int u : topo) if(dp[u] != -1e9)
        for(int v : g[u]) dp[v] = max(dp[v], dp[u] + cash[v]);

    int ans = -1e9;
    for(int u : atm) ans = max(ans, dp[id[u]]);
    printf("%d\n", ans);

    return 0;
}