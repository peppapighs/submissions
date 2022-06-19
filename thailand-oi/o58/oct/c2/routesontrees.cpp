#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

struct node {
    int d, u, c;
    node(int d, int u, int c) : d(d), u(u), c(c) {}
    friend bool operator<(const node &a, const node &b) { return a.d > b.d; }
};

int n, m, k;
vector<pii> g[N];
int dp[N][8];
priority_queue<node> Q;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    while (m--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].emplace_back(v, w);
    }
    for (int i = 1; i <= n; i++)
        fill(begin(dp[i]), end(dp[i]), INT_MAX);
    Q.emplace(dp[1][0] = 0, 1, 0);
    while (!Q.empty()) {
        node now = Q.top();
        Q.pop();
        int u = now.u, c = now.c;
        if (dp[u][c] != now.d)
            continue;
        for (pii vw : g[u]) {
            int v = vw.x, w = vw.y;
            if (w >= 0 && dp[u][c] + w < dp[v][c])
                Q.emplace(dp[v][c] = dp[u][c] + w, v, c);
            if (w <= 0) {
                if (w < -100 && c < k && dp[u][c] < dp[v][c + 1])
                    Q.emplace(dp[v][c + 1] = dp[u][c], v, c + 1);
                if (w >= -100 && dp[u][c] < dp[v][c])
                    Q.emplace(dp[v][c] = dp[u][c], v, c);
            }
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dp[n][i]);
    if (ans == INT_MAX)
        printf("-1\n");
    else
        printf("%d\n", ans);

    return 0;
}