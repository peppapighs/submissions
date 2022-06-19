#include <bits/stdc++.h>

#define pii pair<int, long long>
#define x first
#define y second

using namespace std;

const int N = 8e4 + 5;

struct node {
    long long d;
    int u, pot, ls;
    node(long long d, int u, int pot, int ls) : d(d), u(u), pot(pot), ls(ls) {}
    friend bool operator<(const node &a, const node &b) { return a.d > b.d; }
};

int n, m, l, q;
vector<pii> g[N];
long long dp[N][10];
priority_queue<node> Q;
bitset<N> potion;

int main() {
    scanf("%d%d%d%d", &n, &m, &l, &q);
    while (m--) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].emplace_back(v, w);
    }
    for (int i = 1, a; i <= l; i++)
        scanf("%d", &a), potion[a] = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 10; j++)
            dp[i][j] = LLONG_MAX;
    Q.emplace(dp[1][0] = 0, 1, 0, 0);
    while (!Q.empty()) {
        node now = Q.top();
        Q.pop();

        int u = now.u, pot = now.pot, ls = now.ls;
        if (dp[u][pot] != now.d)
            continue;

        for (pii vw : g[u]) {
            int v = vw.x;
            long long w = vw.y;
            if (dp[u][pot] + (w >> pot) < dp[v][pot]) {
                dp[v][pot] = dp[u][pot] + (w >> pot);
                Q.emplace(dp[v][pot], v, pot, ls);
            }
            if (pot < q && potion[u] && ls != u &&
                dp[u][pot] + (w >> (pot + 1)) < dp[v][pot + 1]) {
                dp[v][pot + 1] = dp[u][pot] + (w >> (pot + 1));
                Q.emplace(dp[v][pot + 1], v, pot + 1, u);
            }
        }
    }

    long long ans = LLONG_MAX;
    for (int i = 0; i <= q; i++)
        ans = min(ans, dp[n][i]);
    printf("%lld", ans);

    return 0;
}