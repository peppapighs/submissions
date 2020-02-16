#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, k;
long A[N], S[N], ans;
long dp1[N][105], dp2[N][105]; //up, down
vector<int> g[N];

void dfs(int u, int p) {
    dp1[u][0] = dp2[u][0] = 0;
    dp1[u][1] = S[u];

    long mx1[105] = {0}, mx2[105] = {0};
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        for(int i = 1; i <= k; i++) {
            dp1[u][i] = max({dp1[u][i], dp1[v][i], dp1[v][i-1] + S[u] - A[v]});
            dp2[u][i] = max({dp2[u][i], dp2[v][i], dp2[v][i-1] + S[u] - A[p]});

            long val = dp2[v][i];
            if(val >= mx1[i]) swap(mx1[i], val);
            if(val >= mx2[i]) swap(mx2[i], val);
        }
    }
    for(int v : g[u]) if(v != p) {
        ans = max(ans, dp2[v][k-1] + S[u]);
        for(int i = 0; i <= k; i++) {
            long now = max(dp1[v][i], i ? dp1[v][i-1] + S[u] - A[v] : 0);
            if(dp2[v][k - i] != mx1[k - i]) ans = max(ans, now + mx1[k - i]);
            else ans = max(ans, now + mx2[k - i]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);

    if(k == 0) return !printf("0\n");

    for(int i = 1; i <= n; i++) scanf("%lld", A + i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        S[a] += A[b], S[b] += A[a];
    }

    dfs(1, 0);
    printf("%lld\n", ans);

    return 0;
}