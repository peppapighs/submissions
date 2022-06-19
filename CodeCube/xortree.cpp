#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int N = 1e5 + 5;

int n, m;
vector<vector<pii>> g(N);
int dp[N];

void dfs(int u, int p) {
    for (pii v : g[u])
        if (v.first != p) {
            dp[v.first] = dp[u] ^ v.second;
            dfs(v.first, u);
        }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[--u].emplace_back(--v, w);
        g[v].emplace_back(u, w);
    }
    dfs(0, -1);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", dp[--a] ^ dp[--b]);
    }

    return 0;
}