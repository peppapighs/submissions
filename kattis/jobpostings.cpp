#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, long, long, long>
#define pii pair<int, int>

using namespace std;

const long INF = 1e18;

class MinCostMaxFlow {
  private:
    int n;
    vector<edge> E;
    vector<vector<int>> g;
    vector<long> d;
    vector<bool> inQ;
    vector<pii> p;

    bool spfa(int s, int t) {
        d.assign(n, INF), inQ.assign(n, false), p.assign(n, {-1, -1});
        d[s] = 0, inQ[s] = true;

        queue<int> Q({s});
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inQ[u] = false;
            for (auto &idx : g[u]) {
                auto &[v, cap, flow, cost] = E[idx];
                if (cap - flow > 0 && d[u] + cost < d[v]) {
                    d[v] = d[u] + cost, p[v] = {u, idx};
                    if (!inQ[v])
                        inQ[v] = true, Q.emplace(v);
                }
            }
        }

        return d[t] != INF;
    }

    long sendFlow(int s, int t) {
        int u = t;
        long f = INF;
        while (u != s) {
            auto &[v, idx] = p[u];
            auto &cap = get<1>(E[idx]), &flow = get<2>(E[idx]);
            f = min(f, cap - flow);
            u = v;
        }
        u = t;
        while (u != s) {
            auto &[v, idx] = p[u];
            auto &flow = get<2>(E[idx]), &rflow = get<2>(E[idx ^ 1]);
            flow += f, rflow -= f;
            u = v;
        }
        return f;
    }

  public:
    MinCostMaxFlow(int n) : n(n) {
        E.clear();
        g.assign(n, vector<int>());
    }

    void addEdge(int u, int v, long w, long cost) {
        E.emplace_back(v, w, 0, cost);
        g[u].emplace_back(E.size() - 1);
        E.emplace_back(u, 0, 0, -cost);
        g[v].emplace_back(E.size() - 1);
    }

    long edmondKarp(int s, int t) {
        long cost = 0;
        while (spfa(s, t)) {
            long f = sendFlow(s, t);
            if (f == 0)
                break;
            cost += d[t];
        }
        return cost;
    }
};

int n, m;

int main() {
    while (scanf("%d %d", &n, &m), n != 0 || m != 0) {
        MinCostMaxFlow flow(n + m + 2);
        int s = n + m, t = n + m + 1;

        for (int i = 0, a; i < n; i++) {
            scanf("%d", &a);
            flow.addEdge(m + i, t, a, 0);
        }

        for (int i = 0, a; i < m; i++) {
            scanf("%d", &a);
            for (int j = 0, b; j < 4; j++) {
                scanf("%d", &b);
                flow.addEdge(i, m + b, 1, -(a * 4 - j));
            }
            flow.addEdge(s, i, 1, 0);
        }
        printf("%lld\n", -flow.edmondKarp(s, t));
    }

    return 0;
}