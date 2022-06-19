#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int B = 1e3 + 5;

struct UnionFindDisjointSet {
    int par[N], sz[N];
    stack<int> S;

    void reset() { iota(par, par + N, 0), fill_n(sz, N, 1); }

    int find(int x) { return x == par[x] ? x : find(par[x]); }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return;
        if (sz[a] > sz[b])
            swap(a, b);
        par[a] = b, sz[b] += sz[a];
        S.emplace(a);
    }

    void rollback(int x) {
        while (S.size() > x) {
            int now = S.top();
            S.pop();
            sz[par[now]] -= sz[now];
            par[now] = now;
        }
    }
} dsu;

int n, m, q, ans[N];
int u[N], v[N], w[N], t[N], x[N], y[N];
bool chk[N];
vector<int> join[B];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d %d %d", u + i, v + i, w + i);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d %d %d", t + i, x + i, y + i);

    for (int l = 1, r; l <= q; l += B) {
        r = min(q, l + B - 1);
        dsu.reset();
        fill(chk + 1, chk + m + 1, 0);

        vector<int> upd, ask, E;
        for (int i = l; i <= r; i++) {
            if (t[i] == 1) {
                upd.emplace_back(i);
                chk[x[i]] = true;
            } else
                ask.emplace_back(i);
        }
        for (int i = 1; i <= m; i++)
            if (!chk[i])
                E.emplace_back(i);
        for (int i = l; i <= r; i++) {
            if (t[i] == 1)
                w[x[i]] = y[i];
            else {
                join[i - l].clear();
                for (int &z : upd)
                    if (w[x[z]] >= y[i])
                        join[i - l].emplace_back(z);
            }
        }

        sort(ask.begin(), ask.end(), [&](int a, int b) { return y[a] > y[b]; });
        sort(E.begin(), E.end(), [&](int a, int b) { return w[a] > w[b]; });

        int ptr = 0;
        for (int &i : ask) {
            int idx = x[i], cost = y[i];
            while (ptr < E.size() && w[E[ptr]] >= cost)
                dsu.unite(u[E[ptr]], v[E[ptr]]), ++ptr;
            int tmp = dsu.S.size();
            for (int &z : join[i - l])
                dsu.unite(u[x[z]], v[x[z]]);
            ans[i] = dsu.sz[dsu.find(idx)];
            dsu.rollback(tmp);
        }
    }
    for (int i = 1; i <= q; i++)
        if (t[i] == 2)
            printf("%d\n", ans[i]);

    return 0;
}