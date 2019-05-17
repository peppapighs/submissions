#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, long, long>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int dsu[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int n, m;
long dp[N];
vector<pii> g[N];
vector<iii> E;

void dfs(int u, int p) {
    for(pii v : g[u]) if(v.x != p) {
        dp[v.x] = dp[u] ^ v.y;
        dfs(v.x, u);
    }
}

int main() {
    iota(dsu, dsu+N, 0);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; long c;
        scanf("%d %d %lld", &a, &b, &c);
        if(find(a) != find(b)) {
            dsu[find(a)] = find(b);
            g[a].emplace_back(b, c);
            g[b].emplace_back(a, c);
        } else E.emplace_back(a, b, c);
    }
    dfs(1, 1);
    vector<long> gauss, basis;
    for(iii e : E) {
        long a, b, c; tie(a, b, c) = e;
        gauss.emplace_back(dp[a] ^ dp[b] ^ c);
    }
    for(int i = 62; ~i; i--) {
        long ret = 0;
        for(long b : gauss) if(b >> i & 1) ret = b;
        if(!ret) continue;
        basis.emplace_back(ret);
        for(long& b : gauss) if(b >> i & 1) b ^= ret;
    }
    long ans = 0;
    for(long b : basis) if((ans ^ b) > ans) ans ^= b;
    printf("%lld\n", ans);

    return 0;
}