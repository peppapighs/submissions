#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

vector<pii> g[N];

void sssp(int src, long d[]) {
    fill_n(d, N, 1e18);
    priority_queue<pii, vector<pii>, greater<pii>> Q;

    Q.emplace(d[src] = 0, src);
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();
        if (d[now.y] != now.x)
            continue;
        long u, w;
        tie(w, u) = now;
        for (pii v : g[u])
            if (w + v.y < d[v.x])
                Q.emplace(d[v.x] = w + v.y, v.x);
    }
}

int n, m, s, t, u, v;
long ds[N], dt[N], du[N], dv[N];

long solve(int a, int b, long da[], long db[]) {
    long dp[N], len = da[b];
    bool vis[N];
    memset(vis, 0, sizeof vis);
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int i = 1; i <= n; i++)
        dp[i] = du[i];

    Q.emplace(0, a), vis[a] = true;
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();
        if (now.x != da[now.y])
            continue;
        long u, w;
        tie(w, u) = now;
        for (pii v : g[u])
            if (w + v.y + db[v.x] == len) {
                dp[v.x] = min(dp[v.x], dp[u]);
                if (!vis[v.x])
                    vis[v.x] = true, Q.emplace(w + v.y, v.x);
            }
    }
    long ret = 1e18;
    for (int i = 1; i <= n; i++)
        if (da[i] + db[i] == len)
            ret = min(ret, dp[i] + dv[i]);
    return ret;
}

int main() {
    scanf("%d %d %d %d %d %d", &n, &m, &s, &t, &u, &v);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    sssp(s, ds), sssp(t, dt);
    sssp(u, du), sssp(v, dv);

    printf("%lld\n", min({du[v], solve(s, t, ds, dt), solve(t, s, dt, ds)}));

    return 0;
}