#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, A[N], dp[N][2], ans;
vector<int> g[N];

void dfs(int u, int p) {
    vector<int> V1(3, 0), V2(3, 0);
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        V1.emplace_back(dp[v][0]);
        V2.emplace_back(max(dp[v][0], dp[v][1]));
    }
    sort(V1.begin(), V1.end(), greater<int>());
    sort(V2.begin(), V2.end(), greater<int>());
    ans = max(ans, V1[0] + V1[1] + V1[2] + A[u]);
    ans = max(ans, V2[0] + V2[1] + A[u]);
    dp[u][0] = A[u] + V2[0];
    dp[u][1] = A[u] + V1[0] + V1[1];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", A+i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(0, 0);
    printf("%d\n", ans); 

    return 0;
}
