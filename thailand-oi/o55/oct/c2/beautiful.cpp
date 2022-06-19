#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4 + 5;

int n, m;
int deg[N], ap[20][20], dist[N], dp[1 << 16];
vector<int> g[N], odd;

int solve(int bit) {
    int &ret = dp[bit];
    if (bit == 0)
        return 0;
    if (~ret)
        return ret;
    ret = INT_MAX;
    for (int i = 0; i < odd.size(); i++)
        if ((bit >> i) & 1) {
            for (int j = 0; j < odd.size(); j++) {
                if (i == j || !((bit >> j) & 1))
                    continue;
                int nbit = bit ^ (1 << i) ^ (1 << j);
                ret = min(ret, solve(nbit) + ap[i][j]);
            }
        }
    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        ++deg[a], ++deg[b];
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1)
            odd.emplace_back(i);
    for (int i = 0; i < odd.size(); i++) {
        int st = odd[i];
        priority_queue<pii, vector<pii>, greater<pii>> Q;
        fill_n(dist, N, INT_MAX);
        Q.emplace(dist[st] = 0, st);
        while (!Q.empty()) {
            pii now = Q.top();
            Q.pop();
            if (dist[now.y] != now.x)
                continue;
            int u = now.y;
            for (int v : g[u])
                if (dist[v] > dist[u] + 1)
                    Q.emplace(dist[v] = dist[u] + 1, v);
        }
        for (int j = 0; j < odd.size(); j++)
            ap[i][j] = dist[odd[j]];
    }
    printf("%d\n", m - solve((1 << odd.size()) - 1));

    return 0;
}
