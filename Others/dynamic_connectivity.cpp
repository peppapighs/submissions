#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5 + 5;

int ans, par[N], sz[N];
stack<int> S;

int find(int u) {
    while (par[u] != u)
        u = par[u];
    return u;
}

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)
        return;
    if (sz[u] > sz[v])
        swap(u, v);
    par[u] = v, sz[v] += sz[u], --ans;
    S.emplace(u);
}

void rollback(int x) {
    while ((int)S.size() > x) {
        int u = S.top();
        S.pop();
        sz[par[u]] -= sz[u];
        par[u] = u, ++ans;
    }
}

int n, k;
int op[N], u[N], v[N], o[N];
map<pii, int> mp;

void solve(int l, int r) {
    if (l == r) {
        if (op[l] == '?')
            printf("%d\n", ans);
        return;
    }

    int mid = (l + r) >> 1, now = S.size();

    for (int i = mid + 1; i <= r; i++)
        if (o[i] < l && op[i] != '?')
            unite(u[i], v[i]);
    solve(l, mid), rollback(now);

    for (int i = l; i <= mid; i++)
        if (o[i] > r && op[i] != '?')
            unite(u[i], v[i]);
    solve(mid + 1, r), rollback(now);
}

int main() {
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);

    iota(par, par + N, 0), fill_n(sz, N, 1);

    scanf("%d %d", &n, &k);
    if (!k)
        return 0;
    for (int i = 1; i <= k; i++) {
        scanf(" %c", op + i);
        if (op[i] == '?')
            continue;
        scanf("%d %d", u + i, v + i);
        if (u[i] > v[i])
            swap(u[i], v[i]);

        pii p(u[i], v[i]);
        if (mp.count(p)) {
            o[i] = mp[p];
            o[o[i]] = i;
            mp.erase(p);
        } else
            mp[p] = i;
    }
    for (auto it : mp)
        o[it.y] = 1e9;

    ans = n;
    solve(1, k);

    return 0;
}