#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 6e3 + 5;
const int M = 1e6 + 5;

int n, k, ans = 1e9, A[N];
int chk[N], sz[N], cnt;
int t[M << 1];
vector<int> g[N];

void update(int x, int k, bool clear = false) {
    for (t[x += M] = clear ? k : min(t[x], k); x != 1; x >>= 1)
        t[x >> 1] = min(t[x], t[x ^ 1]);
}

int query(int l, int r) {
    int ret = 1e9;
    for (l += M, r += M + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = min(ret, t[l++]);
        if (r & 1)
            ret = min(ret, t[--r]);
    }
    return ret;
}

int getsz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u])
        if (!chk[v] && v != p)
            sz[u] += getsz(v, u);
    return sz[u];
}

int findcen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for (int v : g[u])
        if (!chk[v] && v != p)
            mx = max(mx, findcen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int len, int sum, int st, bool fill) {
    if (!fill) {
        if (sum + A[st] >= k)
            ans = min(ans, len);
        else
            ans = min(ans, query(k - A[st] - sum, M - 1) + len);
    } else if (sum + A[st] < k)
        update(sum, len);
    for (int v : g[u])
        if (!chk[v] && v != p)
            dfs(v, u, len + 1, sum + A[v], st, fill);
}

void clear(int u, int p, int sum) {
    update(sum, 1e9, true);
    for (int v : g[u])
        if (!chk[v] && v != p)
            clear(v, u, sum + A[v]);
}

void proc(int u) {
    if (getsz(u, u) <= 1)
        return;
    pii ret(sz[u] + 1, -1);
    findcen(u, u, sz[u], ret);
    ++cnt, u = ret.y;
    for (int v : g[u])
        if (!chk[v]) {
            dfs(v, u, 1, A[v], u, 0);
            dfs(v, u, 1, A[v], u, 1);
        }
    for (int v : g[u])
        if (!chk[v])
            clear(v, u, A[v]);
    chk[u] = 1;
    for (int v : g[u])
        if (!chk[v])
            proc(v);
}

int main() {
    fill_n(t, M << 1, 1e9);
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", A + i);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    proc(0);
    printf("%d\n", ans);

    return 0;
}