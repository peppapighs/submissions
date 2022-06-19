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
        for (int i = 0; i < n_left; i++) {
            if (match_left[i] == -1)
                Q.emplace(i), dist[i] = 0;
            else
                dist[i] = -1;
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int &v : g[u])
                if (match_right[v] != -1 && dist[match_right[v]] == -1) {
                    dist[match_right[v]] = dist[u] + 1;
                    Q.emplace(match_right[v]);
                }
        }
    }

    bool dfs(int u) {
        for (int &v : g[u])
            if (match_right[v] == -1) {
                match_left[u] = v, match_right[v] = u;
                return true;
            }
        for (int &v : g[u])
            if (dist[match_right[v]] == dist[u] + 1 && dfs(match_right[v])) {
                match_left[u] = v, match_right[v] = u;
                return true;
            }
        return false;
    }

  public:
    bipartite_matching(int n_left, int n_right)
        : n_left(n_left), n_right(n_right) {
        g.assign(n_left, vector<int>());
        match_left.assign(n_left, -1);
        match_right.assign(n_right, -1);
        dist.assign(n_left, 0);
    }

    void add_edge(int u, int v) { g[u].emplace_back(v); }

    int mcbm(int shuff = false) {
        if (shuff) {
            mt19937 rng(time(0));
            for (int i = 0; i < n_left; i++)
                shuffle(g[i].begin(), g[i].end(), rng);
        }
        while (true) {
            bfs();
            int augment = 0;
            for (int i = 0; i < n_left; i++)
                if (match_left[i] == -1)
                    augment += dfs(i);
            if (!augment)
                break;
            flow += augment;
        }
        return flow;
    }

    pair<vector<int>, vector<int>> mvc() {
        vector<int> L, R;
        for (int i = 0; i < n_left; i++) {
            if (dist[i] == -1)
                L.emplace_back(i);
            else if (match_left[i] != -1)
                R.emplace_back(match_left[i]);
        }
        return {L, R};
    }

    vector<pii> matching() {
        vector<pii> ans;
        for (int i = 0; i < n_left; i++)
            if (match_left[i] != -1)
                ans.emplace_back(i, match_left[i]);
        return ans;
    }
};

const int N = 505;

int n;
char S[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %s", S[i]);

    int l = strlen(S[0]);
    bipartite_matching bm(n, n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int cnt = 0;
            for (int k = 0; k < l; k++)
                cnt += (S[i][k] != S[j][k]);
            if (cnt == 2) {
                bm.add_edge(i, j);
                bm.add_edge(j, i);
            }
        }
    int ret = bm.mcbm();
    printf("%d\n", n - ret / 2);

    return 0;
}