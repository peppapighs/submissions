#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5+5;

int n, hv[N], t[N], in[N], out[N], pos[N];
long A[N], dp[N], ans = 1e18, all;
vector<int> g[N];
set<long> S;

int proc(int u, int p) {
    static int idx = 0;
    int sz = 1; pii ret(0, -1);
    dp[u] = A[u], in[u] = ++idx, pos[idx] = u;
    for(int v : g[u]) if(v != p) {
        int z = proc(v, u);
        sz += z, dp[u] += dp[v];
        ret = max(ret, pii(z, v));
    }
    out[u] = idx, hv[u] = ret.y;
    return sz;
}

void getans(long a, long b, long c) { ans = min(ans, max({a, b, c}) - min({a, b, c})); }

void dfs(int u, int p, bool keep) {
    for(int v : g[u]) if(v != p && v != hv[u]) dfs(v, u, 0);
    if(hv[u] != -1) dfs(hv[u], u, 1);
    for(int v : g[u]) if(v != p && v != hv[u]) {
        for(int i = in[v]; i <= out[v]; i++) {
            long now = dp[pos[i]];
            auto it = S.lower_bound((all - now) / 2ll);
            if(it != S.end()) getans(now, *it, all - now - *it);
            if(it != S.begin()) --it, getans(now, *it, all - now - *it);
        }
        for(int i = in[v]; i <= out[v]; i++) S.emplace(dp[pos[i]]);
    } 
    if(u != 1) {
        auto it = S.lower_bound(dp[u] / 2ll);
        if(it != S.end()) getans(*it, dp[u] - *it, all - dp[u]);
        if(it != S.begin()) --it, getans(*it, dp[u] - *it, all - dp[u]);
    }
    S.emplace(dp[u]);
    if(!keep) for(int i = in[u]; i <= out[u]; i++) S.erase(dp[pos[i]]);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", A+i), all += A[i];
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    proc(1, 1), dfs(1, 1, 1);
    printf("%lld\n", ans);

    return 0;
}