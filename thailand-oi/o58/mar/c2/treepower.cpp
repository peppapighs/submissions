#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int MOD = 9907;

int n, ans;
int X[N], Y[N], Z[N];
int chk[N], sz[N], sum[N], sum2[N];
vector<int> g[N];

void add(int &a, int b) { a = (a + b + MOD) % MOD; }
int sq(int x) { return (x * x) % MOD; }

int modpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % MOD;
        a = (a * a) % MOD;
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
    if (mx < ret.x)
        ret = pii(mx, u);
    return sz[u];
}

void dfs(int u, int p, int st, int len) {
    if (len > 2)
        return;
    if (len == 2) {
        add(sum[st], X[u]), add(sum[u], X[st]);
        add(sum2[st], sq(X[u])), add(sum2[u], sq(X[st]));
    }
    for (int v : g[u])
        if (!chk[v] && v != p)
            dfs(v, u, st, len + 1);
}

void proc(int u) {
    int p = 0, p2 = 0;
    if (getsz(u, u) <= 1)
        return;
    pii ret(sz[u] + 1, -1);
    findcen(u, u, sz[u], ret), u = ret.y;
    for (int v : g[u])
        if (!chk[v]) {
            add(p, X[v]), add(p2, sq(X[v]));
            dfs(v, u, u, 1);
        }
    for (int v : g[u])
        if (!chk[v]) {
            add(sum[v], (p - X[v] + MOD) % MOD);
            add(sum2[v], (p2 - sq(X[v]) + MOD) % MOD);
        }
    chk[u] = 1;
    for (int v : g[u])
        if (!chk[v])
            proc(v);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", X + i, Y + i, Z + i);
    proc(1);
    for (int i = 1; i <= n; i++) {
        int now = (sq(sum[i]) - sum2[i] + MOD) % MOD;
        now = (now * modpow(2, MOD - 2)) % MOD;
        add(ans, ((now * Y[i]) % MOD + Z[i]));
    }
    printf("%d\n", ans);

    return 0;
}