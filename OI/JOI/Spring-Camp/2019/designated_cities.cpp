#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

struct Edge {
    int v;
    long c, d;
    Edge(int v, long c, long d) : v(v), c(c), d(d) {}
};

int n, q, deg[N];
vector<Edge> g[N];

long dwn[N], ans[N];

void pre_process(int u, int p) {
    for (Edge v : g[u])
        if (v.v != p) {
            pre_process(v.v, u);
            dwn[u] += v.c + dwn[v.v];
        }
}

void dfs(int u, int p, long sum) {
    ans[1] = min(ans[1], sum);
    for (Edge v : g[u])
        if (v.v != p) {
            sum -= v.c, sum += v.d;
            dfs(v.v, u, sum);
            sum += v.c, sum -= v.d;
        }
}

int main() {
    ans[1] = 1e18;

    scanf("%d", &n);
    for (int i = 1, a, b, c, d; i < n; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        g[a].emplace_back(b, c, d);
        g[b].emplace_back(a, d, c);
        ++deg[a], ++deg[b];
    }
    pre_process(1, 0), dfs(1, 0, dwn[1]);

    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            Q.emplace(g[i][0].d, i);

    while (Q.size() > 2) {
        pii now = Q.top();
        Q.pop();
        int u = now.y;
        long dist = now.x;
        int nex = -1;
        for (Edge v : g[u])
            if (deg[v.v] > 1) {
                --deg[v.v];
                if (deg[v.v] == 1)
                    nex = v.v;
                else
                    ans[Q.size()] = ans[Q.size() + 1] + dist;
            }
        if (nex != -1)
            for (Edge v : g[nex])
                if (deg[v.v] > 1)
                    Q.emplace(dist + v.d, nex);
    }

    scanf("%d", &q);
    for (int i = 1, a; i <= q; i++) {
        scanf("%d", &a);
        printf("%lld\n", ans[a]);
    }

    return 0;
}