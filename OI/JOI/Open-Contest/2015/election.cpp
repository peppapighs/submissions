#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5 + 5;

long t[N];

void update(int x, long k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}

void update(int x, int y, long k) { update(x, k), update(y + 1, -k); }

long query(int x) {
    long ret = 0;
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int n, q;
int par[N][18], dep[N], in[N], out[N];
vector<int> g[N];
vector<iii> Q[N];

void preprocess(int u, int p) {
    static int idx = 0;
    par[u][0] = p, dep[u] = dep[p] + 1, in[u] = ++idx;
    for (int i = 1; i <= 17; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p)
            preprocess(v, u);
    out[u] = idx;
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    return par[a][0];
}

long dp[N];

void solve(int u, int p) {
    long sum = 0;
    for (int v : g[u])
        if (v != p) {
            solve(v, u);
            sum += dp[v];
        }
    dp[u] = sum;
    for (iii t : Q[u]) {
        int a, b, c;
        tie(a, b, c) = t;
        long now = 0;
        if (a != u)
            now += query(in[a]);
        if (b != u)
            now += query(in[b]);
        dp[u] = max(dp[u], sum + now + c);
    }
    update(in[u], out[u], sum - dp[u]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    preprocess(1, 0);

    scanf("%d", &q);
    for (int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        Q[lca(a, b)].emplace_back(a, b, c);
    }
    solve(1, 0);
    printf("%lld\n", dp[1]);

    return 0;
}