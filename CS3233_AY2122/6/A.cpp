#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

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

int r, c;
char S[N];

void solve() {
    scanf("%d %d", &r, &c);
    bipartite_matching bm(r, c);
    for(int i = 0; i < r; i++) {
        scanf(" %s", S);
        for(int j = 0; j < c; j++) {
            if(S[j] == '.')
                bm.add_edge(i, j);
        }
    }
    printf("%d\n", bm.mcbm());
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}