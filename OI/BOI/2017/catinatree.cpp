#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, k;
int dep[N], hv[N];
vector<int> g[N];
multiset<int> S[N];

int dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    int sz = 1, mx = 0, x = -1;
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        if(z > mx) mx = z, x = v;
        sz += z;
    }
    hv[u] = x;
    return sz;
}

void sack(int u, int p) {
    S[u].emplace(dep[u]);
    for(int v : g[u]) if(v != p) sack(v, u);
    if(hv[u] == -1) return;
    swap(S[u], S[hv[u]]);
    for(int v : g[u]) if(v != p) {
        while(!S[u].empty() && !S[v].empty() && *S[u].begin() + *S[v].begin() - 2 * dep[u] < k) {
            if(*S[u].begin() > *S[v].begin()) S[v].erase(S[v].begin());
            else S[u].erase(S[u].begin());
        }
        for(int x : S[v]) S[u].emplace(x);
        S[v].clear();
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[++p].emplace_back(i);
        g[i].emplace_back(p);
    }
    dfs(1, 0);
    sack(1, 0);
    printf("%d\n", S[1].size());

    return 0;
}