#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, long, long>
#define pii pair<int, int>

using namespace std;

const long INF = 1e18;                             // large enough

class max_flow {
private:
    int V;
    vector<edge> E;
    vector<vector<int>> g;
    vector<int> d, last;
    vector<pii> p;

    bool bfs(int s, int t) {                       // find augmenting path
        d.assign(V, -1); d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});                       // record BFS sp tree
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(u == t) break;                         // stop as sink t reached
            for(auto &idx : g[u]) {                  // explore neighbors of u
                auto &[v, cap, flow] = E[idx];          // stored in E[idx]
                if(cap - flow > 0 && d[v] == -1)      // positive residual edge
                    d[v] = d[u] + 1, q.emplace(v), p[v] = {u, idx}; // 3 lines in one!
            }
        }
        return d[t] != -1;                           // has an augmenting path
    }

    long send_one_flow(int s, int t) {   // send one flow from s->t
        int u = t; long f = INF;
        while(u != s) {
            auto &[v, idx] = p[u];
            auto &cap = get<1>(E[idx]), &flow = get<2>(E[idx]);
            f = min(f, cap - flow);
            u = v;
        }
        u = t;
        while(u != s) {
            auto &[v, idx] = p[u];
            auto &flow = get<2>(E[idx]), &rflow = get<2>(E[idx ^ 1]);
            flow += f, rflow -= f;
            u = v;
        }
        return f;
    }

    long dfs(int u, int t, long f = INF) {             // traverse from s->t
        if(u == t || f == 0) return f;
        for(int &i = last[u]; i < (int)g[u].size(); i++) { // from last edge
            auto &[v, cap, flow] = E[g[u][i]];
            if(d[v] != d[u] + 1) continue;              // not part of layer graph
            if(long pushed = dfs(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(E[g[u][i] ^ 1]);     // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    max_flow(int initialV) : V(initialV) {
        E.clear();
        g.assign(V, vector<int>());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, long w, bool directed = true) {
        if (u == v) return;                          // safeguard: no self loop
        E.emplace_back(v, w, 0);                    // u->v, cap w, flow 0
        g[u].emplace_back(E.size() - 1);                // remember this index
        E.emplace_back(u, directed ? 0 : w, 0);     // back edge
        g[v].emplace_back(E.size() - 1);                // remember this index
    }

    long edmonds_karp(int s, int t) {
        long mf = 0;                                   // mf stands for max_flow
        while(bfs(s, t)) {                          // an O(V*E^2) algorithm
            long f = send_one_flow(s, t);                // find and send 1 flow f
            if(f == 0) break;                         // if f == 0, stop
            mf += f;                                   // if f > 0, add to mf
        }
        return mf;
    }

    long dinic(int s, int t) {
        long mf = 0;                                   // mf stands for max_flow
        while(bfs(s, t)) {                          // an O(V^2*E) algorithm
            last.assign(V, 0);                         // important speedup
            while(long f = dfs(s, t))                   // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

const int N = 305;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int T;
int k, n, m;
char S[10], A[N][N];

int f(int i, int j) {
    return i * m + j;
}

int get(char c) {
    for(int i = 0; i < k; i++)
        if(S[i] == c)
            return i;
    return -1;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &k, &n, &m);
        scanf(" %s", S);

        max_flow flow(n * m * 2 + 2);
        for(int i = 0; i < n; i++) {
            scanf(" %s", A[i]);
            for(int j = 0; j < m; j++) {
                flow.add_edge(f(i, j) * 2, f(i, j) * 2 + 1, 1);
            }
        }		
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            if(get(A[i][j]) == -1) continue;
            int now = get(A[i][j]);
            if(now == 0) {
                flow.add_edge(n * m * 2, f(i, j) * 2, 1);
            }
            if(now == k - 1) {
                flow.add_edge(f(i, j) * 2 + 1, n * m * 2 + 1, 1);
                continue;
            }
            for(int x = 0; x < 4; x++) {
                int di = i + dx[x], dj = j + dy[x];
                if(di < 0 || di >= n || dj < 0 || dj >= m) continue;
                if(S[now + 1] == A[di][dj]) {
                    flow.add_edge(f(i, j) * 2 + 1, f(di, dj) * 2, 1);
                }
            }
        }
        printf("%lld\n", flow.dinic(n * m * 2, n * m * 2 + 1));
    }

    return 0;
}