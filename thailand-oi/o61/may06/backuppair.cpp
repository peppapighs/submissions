#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;
const int M = 1e4+7;

long fac[N], inv[N];

void pre() {
    auto modpow = [&](long a, long b) {
        long ret = 1;
        for( ; b; b >>= 1) {
            if(b & 1) ret = (ret * a) % M;
            a = (a * a) % M;
        }
        return ret;
    };
    fac[0] = 1, inv[0] = 1;
    for(int i = 1; i < 65; i++) fac[i] = (fac[i-1] * i) % M;
    for(int i = 1; i < 65; i++) inv[i] = modpow(fac[i], M-2);
}

long ncr(int n, int r) {
    return (inv[n-r] * (fac[n] * inv[r]) % M) % M;
}

int n, m, k, rot;
long dp[N][65];
bitset<N> leaf;
vector<int> g[N];

void dfs(int u, int p) {
    if(g[u].size() == 1) { dp[u][1] = 1, leaf[u] = true; return;  }
    for(int v : g[u]) if(v != p) dfs(v, u);

    int sz = 0;
    vector<long> aux(65); aux[0] = 1;
    for(int v : g[u]) if(v != p) {
        vector<long> tmp(65);
        for(int i = 0; i <= (leaf[v] ? 1 : k); i++) for(int p = 0; p <= i; p++) for(int j = p; j <= sz; j++) {
            long &now = tmp[i + j - 2 * p];
            now += ((aux[j] * dp[v][i]) % M) * ((1ll * ncr(i, p) * ncr(j, p) * fac[p]) % M);
            now %= M;
        }
        swap(aux, tmp);
        sz += leaf[v] ? 1 : k;
        sz = min(sz, 35);
    }
    for(int i = 0; i <= k; i++) dp[u][i] = aux[i];
}

int main() {
    pre();
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1, a, b; i < n + m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        if(g[a].size() > 1) rot = a;
        if(g[b].size() > 1) rot = b;
    }
    dfs(rot, rot);
    printf("%lld\n", dp[rot][0]);

    return 0;
}