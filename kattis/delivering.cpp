#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const long INF = 1e18;

class bipartite_matching {
private:
    int n_left, n_right, flow = 0;
    vector<vector<int>> g;
    vector<int> match_left, match_right, dist;

    void bfs() {
        queue<int> Q;
        for(int i = 0; i < n_left; i++) {
            if(match_left[i] == -1)
                Q.emplace(i), dist[i] = 0;
            else dist[i] = -1;
        }
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(int &v : g[u]) if(match_right[v] != -1 && dist[match_right[v]] == -1) {
                dist[match_right[v]] = dist[u] + 1;
                Q.emplace(match_right[v]);
            }
        }
    }

    bool dfs(int u) {
        for(int &v : g[u]) if(match_right[v] == -1) {
            match_left[u] = v, match_right[v] = u;
            return true;
        } 
        for(int &v : g[u]) if(dist[match_right[v]] == dist[u] + 1 && dfs(match_right[v])) {
            match_left[u] = v, match_right[v] = u;
            return true;
        }
        return false;
    }
public:
    bipartite_matching(int n_left, int n_right) : n_left(n_left), n_right(n_right) {
        g.assign(n_left, vector<int>());
        match_left.assign(n_left, -1);
        match_right.assign(n_right, -1);
        dist.assign(n_left, 0);
    }

    void add_edge(int u, int v) {
        g[u].emplace_back(v);
    }

    int mcbm(int shuff = false) {
        if(shuff) {
            mt19937 rng(time(0));
            for(int i = 0; i < n_left; i++)
                shuffle(g[i].begin(), g[i].end(), rng);
        }
        while(true) {
            bfs();
            int augment = 0;
            for(int i = 0; i < n_left; i++) if(match_left[i] == -1)
                augment += dfs(i);
            if(!augment) break;
            flow += augment;
        }
        return flow;
    }

    pair<vector<int>, vector<int>> mvc() {
        vector<int> L, R;
        for(int i = 0; i < n_left; i++) {
            if(dist[i] == -1) L.emplace_back(i);
            else if(match_left[i] != -1)
                R.emplace_back(match_left[i]);
        }
        return {L, R};
    }

    vector<pii> matching() {
        vector<pii> ans;
        for(int i = 0; i < n_left; i++) if(match_left[i] != -1)
            ans.emplace_back(i, match_left[i]);
        return ans;
    }
};

const int N = 1e3 + 5;

int n, m, _c;
int C[N];
vector<pii> g[N];
long d[305][N];

void dijkstra(int src, long d[]) {
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    Q.emplace(d[src] = 0, src);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(u.x != d[u.y]) continue;
        for(pii &v : g[u.y]) if(u.x + v.y < d[v.x])
            Q.emplace(d[v.x] = u.x + v.y, v.x);
    }
}

int main() {
    fill_n(d[0], 305 * N, INF);

    scanf("%d %d %d", &n, &m, &_c); ++_c;
    for(int i = 1; i < _c; i++) scanf("%d", C + i);
    for(int i = 0, a, b, c; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
    }

    for(int i = 0; i < _c; i++)
        dijkstra(C[i], d[i]);
    
    bipartite_matching bm(_c, _c);
    for(int i = 1; i < _c; i++) for(int j = 1; j < _c; j++) if(i != j)
        if(d[0][C[j]] == d[0][C[i]] + d[i][C[j]])
            bm.add_edge(i, j);
    
    printf("%d\n", _c - bm.mcbm() - 1);

    return 0;
}