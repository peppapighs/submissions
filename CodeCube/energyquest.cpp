#include <bits/stdc++.h>

#define pii pair<int, int>
#define pli pair<long long, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, s, t, r;
long long ans;
bitset<N> path;
vector<pii> g[N];
pii par[N];
long long dp[N], cost[N];
;

void dfs(int u, int p) {
    for (pii v : g[u])
        if (v.x != p) {
            par[v.x] = pii(u, v.y);
            dfs(v.x, u);
        }
}

pli calc(int u) {
    int sub = u == r;
    for (pii v : g[u])
        if (v.x != par[u].x && !path[v.x]) {
            pli ret = calc(v.x);
            if (ret.y || ret.x - 2LL * v.y > 0)
                cost[u] += ret.x - 2LL * v.y, sub |= ret.y;
        }
    return pli(cost[u], sub);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b, w; i < n; i++) {
        scanf("%d %d %d", &a, &b, &w);
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }
    for (int i = 1; i <= n; i++)
        scanf("%lld", &cost[i]);
    scanf("%d %d %d", &s, &t, &r);
    dfs(s, 0);
    for (int i = t; par[i].x; i = par[i].x)
        path[i] = 1;
    path[s] = 1;
    for (int i = t; par[i].x; i = par[i].x)
        ans += calc(i).x - par[i].y;
    ans += calc(s).x;
    printf("%lld\n", ans);

    return 0;
}