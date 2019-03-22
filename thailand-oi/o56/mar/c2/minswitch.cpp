#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;

int n, m, sz = 21, chk[N];
vector<int> g[N], ans;

void solve(int u, int k) {
    if(k > sz) return;
    if(u > n) {
        if(k < sz) {
            ans.clear();
            for(int i = 1; i <= n; i++) if(chk[i]) ans.emplace_back(i);
            sz = k;
        }
        return;
    }
    if(!chk[u]) {
        if(g[u].size() <= 20) {
            vector<int> V;
            for(int v : g[u]) if(!chk[v]) {
                chk[v] = 1;
                V.emplace_back(v);
            }
            solve(u + 1, k + V.size());
            for(int v : V) chk[v] = 0;
        }
        if(g[u].size() > 1) {
            chk[u] = 1;
            solve(u + 1, k + 1);
            chk[u] = 0;
        }
    } else solve(u + 1, k);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    solve(1, 0);
    printf("%d\n", (int)ans.size());
    for(int v : ans) printf("%d\n", v);

    return 0;
}
