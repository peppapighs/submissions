#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, A[N];
vector<pii> g[N];
priority_queue<pair<pii, int>> Q;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    vector<pii> dp(n + 1, pii(0, 1e9));
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    for (int i = 1; i <= n; i++)
        if (A[i]) {
            dp[i] = pii(A[i], -i);
            Q.emplace(pii(A[i], -i), i);
        }
    while (!Q.empty()) {
        auto now = Q.top();
        Q.pop();
        pii ice = now.x;
        int u = now.y;
        if (dp[u] != ice)
            continue;
        for (pii v : g[u])
            if (dp[v.x] < pii(ice.x - v.y, ice.y))
                Q.emplace(dp[v.x] = pii(ice.x - v.y, ice.y), v.x);
    }
    for (int i = 1; i <= n; i++) {
        if (dp[i].y != 1e9)
            printf("%d %d\n", -dp[i].y, dp[i].x);
        else
            printf("0 0\n");
    }

    return 0;
}