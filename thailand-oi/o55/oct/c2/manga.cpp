#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 5e4 + 5;

struct edge {
    int v, w, i;
    edge(int v, int w, int i) : v(v), w(w), i(i) {}
};

int n, m, k;
long dp[N];
vector<edge> g[N];
priority_queue<pii, vector<pii>, greater<pii>> Q;

void dijkstra(int m) {
    for (int i = 1; i <= n; i++)
        dp[i] = 1e12;
    dp[1] = 0;
    Q.emplace(dp[1], 1);
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();
        if (dp[now.y] != now.x)
            continue;
        for (edge e : g[now.y]) {
            int v = e.v, w = e.w, i = e.i;
            if (i <= m && dp[v] > dp[now.y] + w) {
                dp[v] = dp[now.y] + w;
                Q.emplace(dp[v], v);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].emplace_back(v, w, i), g[v].emplace_back(u, w, i);
    }
    int l = 0, r = m;
    bool valid = false;
    while (l < r) {
        int m = (l + r) >> 1;
        dijkstra(m);
        if (dp[n] <= k)
            r = m, valid = true;
        else
            l = m + 1;
    }
    if (valid)
        printf("%d\n", r);
    else
        printf("-1\n");

    return 0;
}
