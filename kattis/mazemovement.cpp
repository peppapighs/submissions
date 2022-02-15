#include <bits/stdc++.h>

#define long long long
#define edge tuple<int, int, long ,long>
#define pii pair<int, int>

using namespace std;

const int N = 1e3 + 5;

class max_flow {
private:
    int n;
    vector<edge> E; 
    vector<vector<int>> g;
    vector<int> d, order, lv;
    vector<long> h, l, p;

    bool bfs(int s, int t) {
        queue<int> Q({s});
        d.assign(n, -1); d[s] = 0;
        lv.clear();

        int ptr = 0;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u == t) break;
            for(auto &idx : g[u]) {
                auto &[_, v, cap, flow] = E[idx];
                if(cap - flow > 0) {
                    order[ptr++] = idx;
                    if (d[v] == -1)
                        d[v] = d[u] + 1, Q.emplace(v);
                }
            }
        }
        for(int i = 0; i < ptr; i++) {
            auto &[u, v, cap, flow] = E[order[i]];
            if(d[u] + 1 == d[v])
                lv.emplace_back(order[i]);
        }
        return d[t] != -1;
    }

    long tide_cycle(int s, int t) {
        h.assign(n, 0); h[s] = 1e18;
        for(auto &idx : lv) {
            auto &[u, v, cap, flow] = E[idx];
            p[idx] = min(h[u], cap - flow);
            h[v] += p[idx];
        }
        if(h[t] == 0) return 0;
        l.assign(n, 0); l[t] = h[t];
        for(int i = (int)lv.size() - 1; ~i; i--) {
            auto &idx = lv[i];
            auto &[u, v, cap, flow] = E[idx];
            p[idx] = min({p[idx], h[u] - l[u], l[v]});
            l[v] -= p[idx], l[u] += p[idx];
        }
        h.assign(n, 0); h[s] = l[s];
        for(auto &idx : lv) {
            auto &[u, v, cap, flow] = E[idx];
            p[idx] = min(p[idx], h[u]);
            h[u] -= p[idx], h[v] += p[idx];
            flow += p[idx];
            auto &rflow = get<3>(E[idx ^ 1]);
            rflow -= p[idx];
        }
        return h[t];
    }

public:
    max_flow(int n) : n(n) {
        E.clear();
        g.assign(n, vector<int>());
    }

    void add_edge(int u, int v, long w, bool directed = true) {
        E.emplace_back(u, v, w, 0);
        g[u].emplace_back(E.size() - 1);
        p.emplace_back(0);
        E.emplace_back(v, u, directed ? 0 : w, 0);
        g[v].emplace_back(E.size() - 1);
        p.emplace_back(0);
    }

    long tide_flow(int s, int t) {
        long ret = 0;
        order.assign(E.size(), 0);

        while(bfs(s, t)) {
            long f = tide_cycle(s, t);
            if(f == 0) break;
            ret += f;
        }
        return ret;
    }
}; 

int n;
int A[N];

int main() {
    scanf("%d", &n);

    max_flow flow(n);
    pii s(2e9, 2e9), t(-1, -1);
    for(int i = 0; i < n; i++) {
        scanf("%d", A + i);
        for(int j = 0; j < i; j++) {
            int w = __gcd(A[i], A[j]);
            if(w <= 1) continue;
            flow.add_edge(i, j, w, 0);
        }
        s = min(s, {A[i], i});
        t = max(t, {A[i], i});
    }

    printf("%lld\n", min((long)1e9, flow.tide_flow(s.second, t.second)));

    return 0;
}