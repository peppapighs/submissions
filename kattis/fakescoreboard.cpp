#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, long, long>
#define pii pair<int, int>

using namespace std;

const long INF = 1e18;

class MaxFlow {
  private:
    int n;
    vector<edge> E;
    vector<vector<int>> g;
    vector<int> d, last;
    unordered_map<int, int> mp;

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

    int hsh(int a, int b) { return a * 1000 + b; }

    void update(int u, int v, long k) {
        auto &flow = get<2>(E[mp[hsh(u, v)]]);
        flow += k;
    }

  public:
    MaxFlow(int n) : n(n) {
        E.clear();
        g.assign(n, vector<int>());
        mp.clear();
    }

    void addEdge(int u, int v, long w, bool directed = true) {
        E.emplace_back(v, w, 0);
        g[u].emplace_back(E.size() - 1);
        mp[hsh(u, v)] = E.size() - 1;
        E.emplace_back(u, directed ? 0 : w, 0);
        g[v].emplace_back(E.size() - 1);
        mp[hsh(v, u)] = E.size() - 1;
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

    bool necessary(int u, int v, int s, int t) {
        auto &[_, cap, flow] = E[mp[hsh(u, v)]];

        --cap;
        if (flow == 0)
            return false;

        update(u, v, -1), update(s, u, -1), update(v, t, -1);
        bool valid = (dinic(s, t) == 0);
        if (valid) {
            ++cap;
            update(u, v, 1), update(s, u, 1), update(v, t, 1);
        }
        return valid;
    }
};

const int N = 105;

int n, m;
int team[N], prob[N];

int main() {
    while (scanf("%d %d", &n, &m), n != 0 || m != 0) {
        MaxFlow flow(n + m + 2);
        int s = n + m, t = n + m + 1;

        int sum = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", team + i);
            flow.addEdge(s, i, team[i]);
            sum += team[i], cnt += team[i];
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", prob + i);
            flow.addEdge(n + i, t, prob[i]);
            sum -= prob[i];
        }
        if (sum != 0) {
            printf("Impossible\n\n");
            continue;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                flow.addEdge(i, n + j, 1);

        if (flow.dinic(s, t) != cnt) {
            printf("Impossible\n\n");
            continue;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (flow.necessary(i, n + j, s, t))
                    printf("Y");
                else
                    printf("N");
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}