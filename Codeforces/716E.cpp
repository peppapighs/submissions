#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int phi(int x) {
    int now = x, ret = 1;
    for(int i = 2, pro = 1; i*i <= x; i++) {
        if(now % i != 0) continue;
        for(now /= i; now % i == 0; now /= i) pro *= i;
        ret *= pro * (i - 1), pro = 1;
    }
    if(now != 1) ret *= (now -  1);
    return ret;
}

int n, M, PHI;
long ans, tmp;
long pw[N], invpw[N];
int sz[N], chk[N];
vector<pii> g[N];
map<long, long> mp;

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

int find_cen(int u, int p, int cnt, pii &ret) {
    int mx = 0; sz[u] = 1;
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) {
        sz[u] += find_cen(v.x, u, cnt, ret);
        mx = max(mx, sz[v.x]);
    }
    mx = max(mx, cnt - sz[u]);
    if(mx < ret.x) ret = pii(mx, u);
    return sz[u];
}

void dfs(int u, int p, int len, long num, bool fill) {
    if(!fill) {
        if(num == 0) ++tmp;
        ans += mp[(num * invpw[len]) % M];
        for(pii v : g[u]) if(v.x != p && !chk[v.x])
            dfs(v.x, u, len+1, ((num * 10) % M + v.y) % M, fill);
    } else {
        ++mp[num];
        for(pii v : g[u]) if(v.x != p && !chk[v.x])
            dfs(v.x, u, len+1, (((M - v.y % M) % M * pw[len]) % M + num) % M, fill);
    }
}

void proc(int u, int cnt) {
    if(cnt < 2) return;
    pii ret(cnt, -1);
    find_cen(u, u, cnt, ret);
    u = ret.y, tmp = 0;
    for(pii v : g[u]) if(!chk[v.x]) {
        dfs(v.x, u, 1, v.y % M, 0);
        dfs(v.x, u, 1, (M - v.y % M) % M, 1);
    }
    ans += tmp + mp[0];
    mp.clear();
    for(auto it = g[u].rbegin(); it != g[u].rend(); it++) if(!chk[it->x]) {
        pii v = *it;
        dfs(v.x, u, 1, v.y % M, 0);
        dfs(v.x, u, 1, (M - v.y % M) % M, 1);
    }
    mp.clear();
    chk[u] = true;
    for(pii v : g[u]) if(!chk[v.x]) proc(v.x, sz[v.x]);
}

int main() {
    scanf("%d %d", &n, &M);

    PHI = phi(M);
    pw[0] = 1;
    for(int i = 1; i < N; i++) pw[i] = (pw[i-1] * 10) % M;
    for(int i = 0; i < N; i++) invpw[i] = modpow(pw[i], PHI-1);

    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    proc(0, n);
    printf("%lld\n", ans);

    return 0;
}