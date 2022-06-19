#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, k, m, id[N];
long cost[N][1 << 5];
vector<pii> g[N];
vector<int> vbit[6];

int main() {
    memset(id, -1, sizeof id);
    fill_n(cost[0], N * (1 << 5), 1e18);

    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0, a; i < k; i++) {
        scanf("%d", &a);
        id[a - 1] = i;
    }
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a - 1].emplace_back(b - 1, c);
        g[b - 1].emplace_back(a - 1, c);
    }

    for (int i = 1; i < (1 << k); i++)
        vbit[__builtin_popcount(i)].emplace_back(i);

    for (int step = 1; step <= k; step++) {
        priority_queue<pair<long, pii>> Q;
        if (step == 1) {
            for (int i = 0; i < n; i++)
                if (id[i] != -1) {
                    cost[i][1 << id[i]] = 0;
                    Q.emplace(-cost[i][1 << id[i]], make_pair(i, 1ll << id[i]));
                }
        } else {
            for (int i = 0; i < n; i++)
                for (int x : vbit[step]) {
                    for (int y = 0; y < (1 << k); y++) {
                        if ((x & y) != y)
                            continue;
                        cost[i][x] =
                            min(cost[i][x], cost[i][y] + cost[i][x ^ y]);
                    }
                    Q.emplace(-cost[i][x], make_pair(i, x));
                }
        }
        while (!Q.empty()) {
            auto now = Q.top();
            Q.pop();
            if (cost[now.y.x][now.y.y] != -now.x)
                continue;

            long c = -now.x;
            int u = now.y.x, bit = now.y.y;
            for (pii v : g[u])
                if (cost[v.x][bit] > c + v.y) {
                    cost[v.x][bit] = c + v.y;
                    Q.emplace(-cost[v.x][bit], make_pair(v.x, bit));
                }
        }
    }

    long ans = 1e18;
    for (int i = 0; i < n; i++)
        ans = min(ans, cost[i][(1 << k) - 1]);
    printf("%lld\n", ans);

    return 0;
}