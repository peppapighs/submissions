#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, k, A[N];
int sz[N], chk[N], book;
long dp[N], t[N], ans[N];
vector<int> g[N];

int getsz(int u, int p) { 
    sz[u] = 1; 
    for(int v : g[u]) if(v != p && !chk[v]) 
        sz[u] += getsz(v, u); 
    return sz[u]; 
}

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v]) 
        mx = max(mx, find_cen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int len, bool fill) {
    if(!fill) {
        for(int i = 1; i <= k; i++) if(len <= A[i]) {
            if(len == A[i]) ++ans[i];
            if(t[A[i] - len] == book) ans[i] += dp[A[i] - len];
        }
    } else {
        if(t[len] < book) dp[len] = 0;
        ++dp[len], t[len] = book;
    }
    for(int v : g[u]) if(v != p && !chk[v]) dfs(v, u, len+1, fill);
}

void proc(int u) {
    if(getsz(u, u) <= 1) return;
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    u = ret.y;
    ++book;
    for(int v : g[u]) if(!chk[v]) {
        dfs(v, u, 1, 0);
        dfs(v, u, 1, 1);
    }
    chk[u] = true;
    for(int v : g[u]) if(!chk[v]) proc(v);
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= k; i++) scanf("%d", A+i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    proc(1);
    for(int i = 1; i <= k; i++) printf("%lld\n", ans[i] * 2ll);

    return 0;
}
