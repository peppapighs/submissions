#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, m, k, A, B;
int dp1[N], dp2[N], chk[N];
vector<int> g[N], adj[N];
set<int> S[N];

void bfs_a() {
    fill_n(dp1, N, 2e9), memset(chk, 0, sizeof chk);

    queue<int> Q;
    Q.emplace(k), dp1[k] = 0, chk[k] = 1;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int v : g[u]) if(!chk[v]) {
            dp1[v] = dp1[u] + 1, chk[v] = 1;
            Q.emplace(v);
        }
    }
}

void bfs_b() {
    fill_n(dp2, N, 2e9), memset(chk, 0, sizeof chk);

    queue<int> Q;
    for(int i = 1; i <= n; i++) adj[i] = g[i];
    Q.emplace(k), dp2[k] = 0, chk[k] = 1;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int v : g[u]) {
            vector<int> vec;
            for(int w : adj[v]) if(!chk[w]) {
                vec.emplace_back(w);
                if(S[u].find(w) != S[u].end()) continue;
                chk[w] = 1, dp2[w] = dp2[u] + 1;
                Q.emplace(w);
            }
            swap(vec, adj[v]);
        }
    }
}

int main() {

    scanf("%d %d %d %d %d", &n, &m, &k, &A, &B);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        S[a].emplace(b), S[b].emplace(a);
    }
    bfs_a(), bfs_b(); 
    for(int i = 1; i <= n; i++) {
        int now = dp1[i] / 2 * min(2 * A, B) + dp1[i] % 2 * A;
        if(dp2[i] != 2e9) now = min(now, dp2[i] * B);
        printf("%d\n", now);
    }

    return 0;
}