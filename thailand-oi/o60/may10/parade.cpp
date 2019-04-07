#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;
const int M = 1e9+7;

long add(long a, long b) { return (a + b) % M; }
long mul(long a, long b) { return (a * b) % M; }
long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = mul(ret, a);
        a = mul(a, a);
    }
    return ret;
}

int n, sz[N];
long dp[N], fac[N], inv[N], ans;
vector<int> g[N];

void pre(int u, int p) {
    sz[u] = 1, dp[u] = 1;
    for(int v : g[u]) if(v != p) {
        pre(v, u);
        sz[u] += sz[v];
        dp[u] = mul(dp[u], mul(dp[v], inv[sz[v]]));
    }
    dp[u] = mul(dp[u], fac[sz[u]-1]);
}

void dfs(int u, int p, long k) {
    long now = mul(dp[u], inv[sz[u]-1]);
    now = mul(now, mul(k, inv[n-sz[u]]));
    ans = add(ans, mul(now, fac[n-1]));
    for(int v : g[u]) if(v != p) {
        long nex = mul(dp[u], inv[sz[u]-1]);
        nex = mul(nex, modpow(dp[v], M-2));
        nex = mul(nex, fac[sz[v]]);
        nex = mul(nex, mul(k, inv[n-sz[u]]));
        nex = mul(nex, fac[n-sz[v]-1]);
        dfs(v, u, nex);
    }
}

int main() {
    scanf("%d", &n);
    fac[0] = inv[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = mul(fac[i-1], i), inv[i] = modpow(fac[i], M-2);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    pre(0, 0), dfs(0, 0, 1);
    printf("%lld\n", ans);

    return 0;
}
