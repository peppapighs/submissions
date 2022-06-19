#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, A[N];
int hv[N];
vector<int> g[N];

int proc(int u, int p) {
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u])
        if (v != p) {
            int z = proc(v, u);
            sz += z, ret = max(ret, pii(z, v));
        }
    hv[u] = ret.y;
    return sz;
}

void dfs(int u, int p, multiset<int> &S) {
    if (hv[u] != -1)
        dfs(hv[u], u, S);
    for (int v : g[u])
        if (v != p && v != hv[u]) {
            multiset<int> T;
            dfs(v, u, T);
            for (int x : T)
                S.emplace(x);
        }
    S.emplace(A[u]);
    auto it = S.upper_bound(A[u]);
    if (it != S.end())
        S.erase(it);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", A + i);
    for (int i = 0, a, b; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    proc(0, 0);
    multiset<int> S;
    dfs(0, 0, S);
    printf("%d\n", n - (int)S.size());

    return 0;
}
