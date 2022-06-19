#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

struct FenwickTree {
    long t[N];

    void update(int x, long k) {
        for (int i = x; i < N; i += i & -i)
            t[i] += k;
    }

    long query(int x) {
        long ret = 0;
        for (int i = x; i; i -= i & -i)
            ret += t[i];
        return ret;
    }
} t1, t2;

int n, q, in[N], out[N], pos[N], sz[N];
vector<int> g[N];
set<pii> S[N];

int dfs(int u, int p) {
    static int idx = 0;
    pos[in[u] = ++idx] = u, sz[u] = 1;
    for (int v : g[u])
        if (v != p)
            sz[u] += dfs(v, u);
    out[u] = idx;
    return sz[u];
}

int main() {
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);

    scanf("%d %d", &n, &q);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(1, 0);
    for (int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if (T == 1) {
            scanf("%d", &b);
            auto it = S[b].upper_bound(pii(in[a], -1e9));
            if (it != S[b].begin() && prev(it)->y >= out[a])
                continue;
            while (it != S[b].end() && it->y <= out[a]) {
                t1.update(it->x, -1), t1.update(it->y + 1, 1);
                t2.update(it->x, -sz[pos[it->x]]);
                auto nex = next(it);
                S[b].erase(it);
                it = nex;
            }
            t1.update(in[a], 1), t1.update(out[a] + 1, -1);
            t2.update(in[a], sz[a]);
            S[b].emplace(in[a], out[a]);
        } else
            printf("%lld\n", t1.query(in[a]) * sz[a] + t2.query(out[a]) -
                                 t2.query(in[a]));
    }

    return 0;
}