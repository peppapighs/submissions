#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, long, long>
#define pii pair<int, int>

using namespace std;

const long INF = 1e18;

class MaxFlow {
  private:
  public:
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

const int N = 35;

int n;
int point[N];
char S[N];

void solve() {
    memset(point, 0, sizeof point);

    scanf("%d", &n);

    vector<pii> match;
    for (int i = 0; i < n; i++) {
        scanf(" %s", S);
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            if (S[j] == '1')
                point[i] += 2;
            if (S[j] == 'd')
                ++point[i];
            if (S[j] == '.' && i < j)
                match.emplace_back(i, j);
        }
    }

    for (int p = 0; p < n; p++) {
        int cur = point[p];
        vector<pii> vec;
        for (pii &mat : match) {
            auto &[a, b] = mat;
            if (a == p || b == p)
                cur += 2;
            else
                vec.emplace_back(mat);
        }
        if (cur < max(*max_element(point, point + p),
                      *max_element(point + p + 1, point + n)))
            continue;

        MaxFlow flow(vec.size() + n + 2);
        int s = vec.size() + n, t = vec.size() + n + 1;

        for (int i = 0; i < (int)vec.size(); i++) {
            auto &[a, b] = vec[i];
            assert(a != p && b != p);

            flow.addEdge(s, i, 2);
            flow.addEdge(i, vec.size() + a, 2);
            flow.addEdge(i, vec.size() + b, 2);
        }
        for (int i = 0; i < n; i++)
            if (i != p)
                flow.addEdge(vec.size() + i, t, cur - point[i]);
        flow.dinic(s, t);
        bool valid = true;
        for (auto &idx : flow.g[s]) {
            auto &f = get<2>(flow.E[idx]);
            valid &= (f == 2);
        }
        if (valid)
            printf("%d ", p + 1);
    }
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}