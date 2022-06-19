#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

struct item {
    int v;
    long long w;
    bool sp;
    item(int v, long long w, bool sp) : v(v), w(w), sp(sp) {}
};

struct node {
    long long d;
    int u, k;
    node(long long d, int u, int k) : d(d), u(u), k(k) {}
    friend bool operator<(const node &a, const node &b) { return a.d > b.d; }
};

int n, m, s, l;
long long dp[N][55];
vector<item> g[N];
priority_queue<node> Q;

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &l);
    while (m--) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].emplace_back(v, w, 0);
    }
    while (s--) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].emplace_back(v, w, 1);
    }

    for (int i = 1; i <= n; i++)
        fill(begin(dp[i]), end(dp[i]), LLONG_MAX);

    Q.emplace(dp[1][0] = 0, 1, 0);
    while (!Q.empty()) {
        node now = Q.top();
        Q.pop();

        if (dp[now.u][now.k] != now.d)
            continue;
        for (item next : g[now.u]) {
            int v = next.v;
            long long w = next.w;
            bool sp = next.sp;
            if (sp && now.k < l && dp[now.u][now.k] + w < dp[v][now.k + 1]) {
                dp[v][now.k + 1] = dp[now.u][now.k] + w;
                Q.emplace(dp[v][now.k + 1], v, now.k + 1);
            } else if (!sp && dp[now.u][now.k] + w < dp[v][now.k]) {
                dp[v][now.k] = dp[now.u][now.k] + w;
                Q.emplace(dp[v][now.k], v, now.k);
            }
        }
    }

    long long ans = LLONG_MAX;
    for (int i = 0; i <= l; i++)
        ans = min(ans, dp[n][i]);
    printf("%lld", ans);

    return 0;
}