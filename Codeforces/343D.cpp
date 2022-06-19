#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;

int n, q, ans[N];
int hv[N], in[N], out[N], pos[N];
vector<int> g[N], Q[N], idx;
vector<pii> vec[N];
set<pii> S;

int proc(int u, int p) {
    static int idx = 0;
    int sz = 1;
    pii ret(0, -1);
    in[u] = ++idx, pos[idx] = u;
    for (int v : g[u])
        if (v != p) {
            int z = proc(v, u);
            sz += z;
            ret = max(ret, pii(z, v));
        }
    hv[u] = ret.y, out[u] = idx;
    return sz;
}

void dfs(int u, int p, bool keep) {
    for (pii x : vec[u])
        if (x.y == 1)
            S.emplace(x);

    for (int v : g[u])
        if (v != p && v != hv[u])
            dfs(v, u, 0);
    if (hv[u] != -1)
        dfs(hv[u], u, 1);

    for (pii x : vec[u])
        if (x.y == 2)
            S.emplace(x);
    for (int v : g[u])
        if (v != p && v != hv[u])
            for (int i = in[v]; i <= out[v]; i++)
                for (pii x : vec[pos[i]])
                    if (x.y == 2)
                        S.emplace(x);

    for (int x : Q[u]) {
        auto it = S.upper_bound(pii(x, -1e9));
        if (it != S.begin())
            --it, ans[x] = (it->y == 1);
    }

    for (pii x : vec[u])
        if (x.y == 1)
            S.erase(x);
    if (!keep)
        for (int i = in[u]; i <= out[u]; i++)
            for (pii x : vec[pos[i]])
                if (x.y == 2)
                    S.erase(x);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    scanf("%d", &q);
    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        if (a != 3)
            vec[b].emplace_back(i, a);
        else
            Q[b].emplace_back(i), idx.emplace_back(i);
    }

    proc(1, 1), dfs(1, 1, 1);
    for (int i : idx)
        printf("%d\n", ans[i]);

    return 0;
}