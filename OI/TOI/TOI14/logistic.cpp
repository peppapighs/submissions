#include <bits/stdc++.h>

#define ii pair<int, int>

using namespace std;

struct node {
    int d, n, fu, oe;
    node(int d, int n, int fu, int oe) : d(d), n(n), fu(fu), oe(oe) {}
    friend bool operator<(const node &a, const node &b) { return a.d > b.d; }
};

int n, m, s, d, f;
priority_queue<node> pq;
int cost[105], dp[105][105][2];
vector<vector<ii>> g(105);

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &cost[i]);
    scanf("%d%d%d%d", &s, &d, &f, &m);
    --s, --d;
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[--u].emplace_back(--v, w);
        g[v].emplace_back(u, w);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= f; j++)
            dp[i][j][0] = dp[i][j][1] = INT_MAX;

    dp[s][0][0] = 0;
    pq.emplace(0, s, 0, 0);
    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();

        int u = now.n, fu = now.fu, oe = now.oe;

        if (!oe && dp[u][fu][0] < dp[u][f][1]) {
            dp[u][f][1] = dp[u][fu][0];
            pq.emplace(dp[u][f][1], u, f, 1);
        }
        if (fu < f && dp[u][fu][oe] + cost[u] < dp[u][fu + 1][oe]) {
            dp[u][fu + 1][oe] = dp[u][fu][oe] + cost[u];
            pq.emplace(dp[u][fu + 1][oe], u, fu + 1, oe);
        }
        for (ii vw : g[u]) {
            int v = vw.first, w = vw.second;
            if (fu >= w && dp[u][fu][oe] < dp[v][fu - w][oe]) {
                dp[v][fu - w][oe] = dp[u][fu][oe];
                pq.emplace(dp[v][fu - w][oe], v, fu - w, oe);
            }
        }
    }

    printf("%d", min(dp[d][f][0], dp[d][f][1]));

    return 0;
}