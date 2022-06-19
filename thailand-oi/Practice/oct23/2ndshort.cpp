#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4 + 5;

int n, m, s, t;
int dp[N][2];
priority_queue<pii, vector<pii>, greater<pii>> Q;
vector<pii> g[N], tg[N];
vector<iii> E;

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        tg[b].emplace_back(a, c);
        E.emplace_back(a, b, c);
    }
    fill_n(dp[0], N * 2, 1e9);
    dp[s][0] = 0;
    Q.emplace(0, s);
    while (!Q.empty()) {
        int u = Q.top().y;
        Q.pop();
        for (pii v : g[u]) {
            if (dp[v.x][0] > dp[u][0] + v.y)
                Q.emplace(dp[v.x][0] = dp[u][0] + v.y, v.x);
        }
    }
    dp[t][1] = 0;
    Q.emplace(0, t);
    while (!Q.empty()) {
        int u = Q.top().y;
        Q.pop();
        for (pii v : tg[u])
            if (dp[v.x][1] > dp[u][1] + v.y)
                Q.emplace(dp[v.x][1] = dp[u][1] + v.y, v.x);
    }
    int ans = 1e9;
    for (iii e : E) {
        int a, b, c;
        tie(a, b, c) = e;
        int d = dp[a][0] + c + dp[b][1];
        if (d < ans && d != dp[t][0])
            ans = d;
    }
    printf("%d\n", ans);

    return 0;
}
