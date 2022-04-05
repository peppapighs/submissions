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

int n;
vector<vector<int>> vec;
mt19937 rng(12345);

void solve(int index) {
    scanf("%d", &n);
    vec.assign(n, vector<int>());
    for(int i = 0, k; i < n; i++) {
        scanf("%d", &k);
        for(int j = 0, a; j < k; j++)  {
           scanf("%d", &a); 
           vec[i].emplace_back(a);
        }
    }
    bipartite_matching bm(n, n);
    for(int i = 0; i < n; i++) for(int &x : vec[i])
        bm.add_edge(i, x);
    int ans = bm.mcbm();
    if(ans != n) {
        printf("Case %d: no\n", index);
        return;
    }
    vector<pii> ex = bm.matching();
    shuffle(ex.begin(), ex.end(), rng);
    for(int _ = 0; _ < min(n, 300); _++) {
        pii bk = ex[_];
        bipartite_matching bm2(n, n);
        for(int i = 0; i < n; i++) for(int &x : vec[i]) {
            if(pii(i, x) == bk) continue;
            bm2.add_edge(i, x);
        }
        if(bm2.mcbm() == n) {
            printf("Case %d: no\n", index);
            return;
        }
    }
    printf("Case %d: yes\n", index);
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}