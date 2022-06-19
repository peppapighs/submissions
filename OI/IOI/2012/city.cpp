#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int M = 1e9;

int n, id[N], sz[N];
long dp[N], ans;
vector<set<int>> g;

long dfs(int u, int p) {
    long cnt = sz[u];
    for (int v : g[u])
        if (v != p) {
            long z = dfs(v, u);
            ans = (ans + (dp[v] + z) * cnt + dp[u] * z) % M;
            dp[u] = (dp[u] + dp[v] + z) % M;
            cnt = (cnt + z) % M;
        }
    return cnt;
}

void solve(int *X, int *Y) {
    memset(id, 0, sizeof id), memset(sz, 0, sizeof sz);
    memset(dp, 0, sizeof dp);
    g = vector<set<int>>(N);

    vector<pii> vec;
    for (int i = 0; i < n; i++)
        vec.emplace_back(X[i], Y[i]);
    sort(vec.begin(), vec.end());

    map<pii, int> mp;
    for (int i = 0, ptr = 0; i < n; i++) {
        mp[vec[i]] = i;
        if (i == 0 || vec[i - 1].x != vec[i].x || vec[i - 1].y + 1 != vec[i].y)
            id[i] = ++ptr;
        else
            id[i] = id[i - 1];
        ++sz[id[i]];
        if (mp.count(pii(vec[i].x - 1, vec[i].y))) {
            int v = id[mp[pii(vec[i].x - 1, vec[i].y)]];
            g[id[i]].emplace(v), g[v].emplace(id[i]);
        }
    }

    dfs(1, 0);
}

int DistanceSum(int _n, int *X, int *Y) {
    n = _n;
    solve(X, Y), solve(Y, X);
    return ans;
}
