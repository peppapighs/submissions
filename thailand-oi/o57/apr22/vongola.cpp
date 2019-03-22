#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q;
int hv[N], dep[N], in[N], out[N], pos[N];
int mn[N], mx[N];
long A[N];
vector<int> g[N], C[N];
vector<vector<long> > dp;
vector<pii> Q[N];

int proc(int u, int p) {
    static int idx = 0;
    int sz = 1; pii ret(0, -1);
    dep[u] = dep[p] + 1, in[u] = ++idx, pos[idx] = u;
    C[dep[u]].emplace_back(idx);
    for(int v : g[u]) if(v != p) {
        int z = proc(v, u);
        sz += z, ret = max(ret, pii(z, v));
    }
    hv[u] = ret.y, out[u] = idx;
    return sz;
}

void dfs(int u, int p, bool keep) {
    for(int v : g[u]) if(v != p && v != hv[u]) dfs(v, u, 0);
    if(hv[u] != -1) dfs(hv[u], u, 1);
    mn[dep[u]] = min(mn[dep[u]], in[u]), mx[dep[u]] = max(mx[dep[u]], in[u]);
    for(int v : g[u]) if(v != p && v != hv[u]) {
        for(int i = in[v]; i <= out[v]; i++) {
            mn[dep[pos[i]]] = min(mn[dep[pos[i]]], in[pos[i]]);
            mx[dep[pos[i]]] = max(mx[dep[pos[i]]], in[pos[i]]);
        }
    }
    for(pii x : Q[u]) {
        int d = x.x, k = x.y;
        int a = lower_bound(C[dep[u] + d].begin(), C[dep[u] + d].end(), mn[dep[u] + d]) - C[dep[u] + d].begin();
        int b = lower_bound(C[dep[u] + d].begin(), C[dep[u] + d].end(), mx[dep[u] + d]) - C[dep[u] + d].begin();
        dp[dep[u] + d][a] += k;
        if(b + 1 < C[dep[u] + d].size()) dp[dep[u] + d][b+1] -= k;
        A[u] -= 1ll * k * (b - a + 1);
    }
    if(!keep) for(int i = in[u]; i <= out[u]; i++) mn[dep[pos[i]]] = 1e9, mx[dep[pos[i]]] = 0; 
}

int main() {
    fill_n(mn, N, 1e9);
    scanf("%d %d", &n, &q);
    for(int i = 0, a; i < n; i++) {
        scanf("%d %lld", &a, A+i);
        if(a != -1) g[a].emplace_back(i), g[i].emplace_back(a);
    }
    for(int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        Q[a].emplace_back(b, c);
    }
    proc(0, 0); 
    dp.emplace_back(vector<long>());
    for(int i = 1; i <= n; i++) dp.emplace_back(vector<long>(C[i].size(), 0));
    dfs(0, 0, 1);
    for(int i = 1; i <= n; i++) {
        if(!C[i].empty()) A[pos[C[i][0]]] += dp[i][0];
        for(int j = 1; j < dp[i].size(); j++) {
            dp[i][j] += dp[i][j-1];
            A[pos[C[i][j]]] += dp[i][j];
        }
    }
    for(int i = 0; i < n; i++) printf("%lld\n", A[i]);

    return 0;
}
