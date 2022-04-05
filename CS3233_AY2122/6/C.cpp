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

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

const int N = 5e3 + 5;

int r, c;
char A[N][N];

bool valid(int i, int j) {
    return !(i < 0 || i >= r || j < 0 || j >= c);
}

void solve() {
    scanf("%d %d", &r, &c);
    for(int i = 0; i < r; i++) scanf(" %s", A[i]);
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) if(A[i][j] == '?') {
        bool ok = false;
        for(int x = 0; x < 4; x++) {
            int ni = i + dx[x], nj = j + dy[x];
            if(!valid(ni, nj)) continue;
            if(A[ni][nj] == '+') {
                ok = true;
                break;
            }
        }
        if(ok) A[i][j] = '-';
    }

    int ans = 0;
    bipartite_matching bm(r * c, r * c);
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) if(A[i][j] == '?') {
        ++ans;
        for(int x = 0; x < 4; x++) {
            int ni = i + dx[x], nj = j + dy[x];
            if(!valid(ni, nj)) continue;
            if(A[ni][nj] == '?') {
                bm.add_edge(i * c + j, ni * c + nj);
            }
        }
    }
    ans -= (bm.mcbm() / 2);
    vector<vector<bool>> vis(r, vector<bool>(c, false));
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) if(A[i][j] == '+' && !vis[i][j]) {
        ++ans;
        queue<pii> Q({{i, j}});
        vis[i][j] = true;
        while(!Q.empty()) {
            pii u = Q.front(); Q.pop();
            for(int x = 0; x < 4; x++) {
                int ni = u.x + dx[x], nj = u.y + dy[x];
                if(!valid(ni, nj)) continue;
                if(!vis[ni][nj] && A[ni][nj] == '+') {
                    vis[ni][nj] = true;
                    Q.emplace(ni, nj);
                }
            }
        }
    }
    printf("%d\n", ans);
} 

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}