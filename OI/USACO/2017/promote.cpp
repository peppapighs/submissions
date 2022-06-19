#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int t[N];

void update(int x, int k) {
    if (x)
        t[x] += k, update(x - (x & -x), k);
}

int query(int x, int ret = 0) {
    return t[x] + (x + (x & -x) < N ? query(x + (x & -x)) : 0);
}

int n, A[N], ans[N];
int in[N], out[N], pos[N], hv[N];
vector<int> g[N], coord;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int pre_process(int u) {
    static int idx = 0;
    pos[in[u] = ++idx] = u;
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u]) {
        int z = pre_process(v);
        sz += z, ret = max(ret, pii(z, v));
    }
    out[u] = idx, hv[u] = ret.y;
    return sz;
}

void sack(int u, bool keep) {
    for (int v : g[u])
        if (v != hv[u])
            sack(v, 0);
    if (hv[u] != -1)
        sack(hv[u], 1);
    update(get(A[u]), 1);
    for (int v : g[u])
        if (v != hv[u])
            for (int i = in[v]; i <= out[v]; i++)
                update(get(A[pos[i]]), 1);
    ans[u] = query(get(A[u]) + 1);
    if (!keep)
        for (int i = in[u]; i <= out[u]; i++)
            update(get(A[pos[i]]), -1);
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        coord.emplace_back(A[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[p].emplace_back(i);
    }
    pre_process(1);
    sack(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);

    return 0;
}