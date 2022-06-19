#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, long, long>

using namespace std;

const long INF = 1e18;

class MaxFlow {
  private:
    int n;
    vector<edge> E;
    vector<vector<int>> g;
    vector<int> d, last;

    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> Q({s});

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (u == t)
                break;
            for (int &idx : g[u]) {
                auto &[v, cap, flow] = E[idx];
                if (cap - flow > 0 && d[v] == -1)
                    d[v] = d[u] + 1, Q.emplace(v);
            }
        }

        return d[t] != -1;
    }

    long dfs(int u, int t, long f = INF) {
        if (u == t || f == 0)
            return f;
        for (int &i = last[u]; i < (int)g[u].size(); i++) {
            auto &[v, cap, flow] = E[g[u][i]];
            if (d[v] != d[u] + 1)
                continue;
            if (long pushed = dfs(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(E[g[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

  public:
    MaxFlow(int n) : n(n) {
        E.clear();
        g.assign(n, vector<int>());
    }

    void addEdge(int u, int v, long w, bool directed = true) {
        E.emplace_back(v, w, 0);
        g[u].emplace_back(E.size() - 1);
        E.emplace_back(u, directed ? 0 : w, 0);
        g[v].emplace_back(E.size() - 1);
    }

    long dinic(int s, int t) {
        long mf = 0;
        while (bfs(s, t)) {
            last.assign(n, 0);
            while (long f = dfs(s, t))
                mf += f;
        }
        return mf;
    }
};

int n, m, t, s1, s2;
vector<edge> vec;

int main() {
    scanf("%d %d %d %d %d", &n, &m, &t, &s1, &s2);
    --t, --s1, --s2;

    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        vec.emplace_back(--a, --b, c);
    }

    long l = 0, r = 1e6;
    while (l < r) {
        long mid = (l + r + 1) >> 1;
        MaxFlow flow(n + 1);
        for (auto &e : vec) {
            auto &[u, v, w] = e;
            flow.addEdge(u, v, w << 1, 0);
        }
        flow.addEdge(n, s1, mid, 0);
        flow.addEdge(n, s2, mid, 0);
        long ret = flow.dinic(n, t);

        if (ret == (mid << 1))
            l = mid;
        else
            r = mid - 1;
    }
    printf("%lld\n", l);

    return 0;
}