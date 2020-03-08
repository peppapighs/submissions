#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

int n, a, b;
int E[N], par[N], block[N], dp[N];
vector<int> g[N];

void dfs(int u, int p) {
    par[u] = p;
    for(int v : g[u]) if(v != p)
        dfs(u ^ E[v], v);
}

int process(int u, int p) {
    dp[u] = 0;
    vector<int> child;
    for(int v : g[u]) if(v != p && !block[v])
        child.emplace_back(process(E[v] ^ u, v));
    sort(child.begin(), child.end(), greater<int>());
    for(int i = 0; i < child.size(); i++)
        dp[u] = max(dp[u], 1 + i + child[i]);
    return dp[u];
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(i), g[b].emplace_back(i);
        E[i] = a ^ b;
    }
    dfs(b, 0);
    vector<int> vec;
    int now = a;
    while(now != b) {
        vec.emplace_back(par[now]);
        now ^= E[par[now]];
    }
    int l = 0, r = vec.size() - 1;
    int ans = 1e9;
    while(l <= r) {
        int mid = (l + r) >> 1;

        block[vec[mid]] = 1;
        int t_a = process(a, 0), t_b = process(b, 0);
        block[vec[mid]] = 0;

        ans = min(ans, max(t_a, t_b));
        if(t_a == t_b) break;
        else if(t_a < t_b) l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);

    return 0;
}