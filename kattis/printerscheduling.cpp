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
    unordered_map<int, int> mp;

    bool bfs(int s, int t) {
        d.assign(n, -1); d[s] = 0;
        queue<int> Q({s});

        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u == t) break;
            for(int &idx : g[u]) {
                auto &[v, cap, flow] = E[idx];
                if(cap - flow > 0 && d[v] == -1)
                    d[v] = d[u] + 1, Q.emplace(v);
            }
        }

        return d[t] != -1;
    }

    long dfs(int u, int t, long f = INF) {
        if(u == t || f == 0) return f;
        for(int &i = last[u]; i < (int)g[u].size(); i++) {
            auto &[v, cap, flow] = E[g[u][i]];
            if(d[v] != d[u] + 1) continue;
            if(long pushed = dfs(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(E[g[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int h(int u, int v) {
        return u * 1000 + v;
    }

public:
    MaxFlow(int n) : n(n) {
        E.clear(), mp.clear();
        g.assign(n, vector<int>());
    }

    void addEdge(int u, int v, long w, bool directed = true) {
        E.emplace_back(v, w, 0);
        g[u].emplace_back(E.size() - 1);
        mp[h(u, v)] = E.size() - 1;
        E.emplace_back(u, directed ? 0 : w, 0);
        g[v].emplace_back(E.size() - 1);
        mp[h(v, u)] = E.size() - 1;
    }

    long dinic(int s, int t) {
        long mf = 0;
        while(bfs(s, t)) {
            last.assign(n, 0);
            while(long f = dfs(s, t))
                mf += f;
        }
        return mf;
    }

    long getFlow(int u, int v) {
        return get<2>(E[mp[h(u, v)]]);
    }
};

const int N = 1e3 + 5;

int n, m;
int p[N], r[N], d[N], ptr[N], last[N];
vector<int> cd;

void solve() {
    memset(ptr, 0, sizeof ptr), memset(last, 0, sizeof last);

    scanf("%d %d", &n, &m);

    int total = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", p + i, r + i, d + i);
        total += p[i];
        cd.emplace_back(r[i]), cd.emplace_back(d[i]);
    }
    sort(cd.begin(), cd.end());
    cd.resize(unique(cd.begin(), cd.end()) - cd.begin());

    MaxFlow flow(n + cd.size() + 1);
    int s = n + cd.size() - 1, t = n + cd.size();

    for(int i = 0; i < n; i++) {
        int idx = lower_bound(cd.begin(), cd.end(), r[i]) - cd.begin();
        for( ; cd[idx] != d[i]; idx++)
            flow.addEdge(i, n + idx, cd[idx + 1] - cd[idx]);
        flow.addEdge(s, i, p[i]);
    }
    for(int i = 0; i < (int)cd.size() - 1; i++)
        flow.addEdge(n + i, t, m * (cd[i + 1] - cd[i]));
    
    if(flow.dinic(s, t) != total) {
        printf("NO\n\n");
        return;
    }
    printf("YES\n");
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(cd.begin(), cd.end(), r[i]) - cd.begin();
        vector<tuple<int, int, int>> sch;
        function<void(int, int, int)> addSch = [&](int l, int r, int idx) {
            if(!sch.empty()) {
                auto &[a, b, c] = sch.back();
                if(c == idx && b == l)
                    return void(b = r);
            } 
            sch.emplace_back(l, r, idx);
        };

        for( ; cd[idx] != d[i]; idx++) {
            int f = (int)flow.getFlow(i, n + idx);
            if(f == 0) continue;
            int sz = cd[idx + 1] - cd[idx];
            if(sz - last[idx] >= f) {
                addSch(cd[idx] + last[idx], cd[idx] + last[idx] + f, ptr[idx]);
                last[idx] += f;
            } else {
                addSch(cd[idx], cd[idx] + f - (sz - last[idx]), ptr[idx] + 1);
                if(sz - last[idx] > 0)
                    addSch(cd[idx] + last[idx], cd[idx + 1], ptr[idx]);
                last[idx] = f - (sz - last[idx]), ++ptr[idx];
            }
        }
        printf("%d\n", (int)sch.size());
        for(auto &t : sch) {
            auto &[l, r, idx] = t;
            printf("%d %d %d\n", l, r, idx + 1);
        }
    }
    printf("\n");

    cd.clear();
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}