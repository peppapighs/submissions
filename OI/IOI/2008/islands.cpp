#include <bits/stdc++.h>

#define pll pair<long long, long long>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n;
long long deg[N], dm[N];
pll par[N], dp[N];
bitset<N> vis;

long long solve(int u) {
    long long ret = 0;
    int sz;
    vector<pll> V;
    deque<pll> Q;

    V.emplace_back(0, 0);
    while (deg[u]) {
        deg[u]--;
        dm[u] = max(dm[u], dp[u].x + dp[u].y);
        ret = max(ret, dm[u]);
        V.emplace_back(u, par[u].y);
        u = par[u].x;
    }

    sz = V.size() - 1;
    for (int i = 1; i <= sz; i++)
        V[i].y += V[i - 1].y;
    for (int i = 2; i <= sz; i++) {
        while (!Q.empty() && Q.back().x < V[i - 1].y + dp[V[i].x].x)
            Q.pop_back();
        Q.emplace_back(V[i - 1].y + dp[V[i].x].x, i);
    }
    ret = max(ret, dp[V[1].x].x + Q.front().x);
    for (int i = 1; i < sz; i++) {
        if (Q.front().y == i + 1)
            Q.pop_front();
        while (!Q.empty() && Q.back().x < V[sz].y + V[i - 1].y + dp[V[i].x].x)
            Q.pop_back();
        Q.emplace_back(V[sz].y + V[i - 1].y + dp[V[i].x].x, i);
        ret = max(ret, dp[V[i + 1].x].x + Q.front().x - V[i].y);
    }

    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, v, w; i <= n; i++) {
        scanf("%d %d", &v, &w);
        par[i] = pll(v, w);
        deg[v]++;
    }

    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (!deg[i])
            Q.emplace(i);

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        long long p = par[now].x, w = par[now].y;
        dm[now] = max(dm[now], dp[now].x + dp[now].y);
        dm[p] = max(dm[p], dm[now]);

        long long ret = dp[now].x + w;
        if (ret > dp[p].x)
            swap(ret, dp[p].x);
        if (ret > dp[p].y)
            swap(ret, dp[p].y);
        if (!--deg[p])
            Q.emplace(p);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i])
            ans += solve(i);

    printf("%lld", ans);

    return 0;
}
