#include "traffic.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n, a[N], idx;
long sz[N], dp[N], ans = 1e18;
vector<int> g[N];

int proc(int u, int p) {
    sz[u] = a[u];
    for (int v : g[u])
        if (v != p) {
            sz[u] += proc(v, u);
            dp[u] += dp[v] + sz[v];
        }
    return sz[u];
}

void dfs(int u, int p, long k, int z) {
    if (dp[u] + k < ans)
        ans = dp[u] + k, idx = u;
    ans = min(ans, dp[u] + k);
    for (int v : g[u])
        if (v != p) {
            long nk = k + dp[u] - (dp[v] + sz[v]) + (sz[u] - sz[v]) + z;
            int nz = z + (sz[u] - sz[v]);
            dfs(v, u, nk, nz);
        }
}

int LocateCentre(int N, int P[], int S[], int D[]) {
    n = N;
    for (int i = 1; i <= n; i++)
        a[i] = P[i - 1];
    for (int i = 0; i < n - 1; i++) {
        ++S[i], ++D[i];
        g[S[i]].emplace_back(D[i]);
        g[D[i]].emplace_back(S[i]);
    }
    proc(1, 1), dfs(1, 1, 0, 0);
    return idx - 1;
}