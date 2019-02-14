#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 6e3+5;

int n, k, A[N];
int chk[N], sz[N], dp[N], t[N], cnt, L, ans;
vector<int> g[N];

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(!chk[v] && v != p) sz[u] += getsz(v, u); return sz[u]; }

int findcen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(!chk[v] && v != p) mx = max(mx, findcen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int len, int val, int st, bool fill) {
    if(len > L) return;
    if(!fill) {
        if(len == L) ans = max(ans, val + A[st]);
        else if(t[L - len] == cnt) ans = max(ans, val + dp[L - len] + A[st]);
    } else if(t[len] < cnt || dp[len] < val) dp[len] = val, t[len] = cnt;
    for(int v : g[u]) if(!chk[v] && v != p) dfs(v, u, len + 1, val + A[v], st, fill);
}

void proc(int u) {
    if(getsz(u, u) <= 1) return;
    pii ret(sz[u] + 1, -1);
    findcen(u, u, sz[u], ret);
    ++cnt, u = ret.y;
    for(int v : g[u]) if(!chk[v]) {
        dfs(v, u, 1, A[v], u, 0);
        dfs(v, u, 1, A[v], u, 1);
    } 
    chk[u] = 1;
    for(int v : g[u]) if(!chk[v]) proc(v);
}

int f(int mid) {
    L = mid, ans = -1;
    memset(chk, 0, sizeof chk), memset(sz, 0, sizeof sz);
    proc(0);
    return ans;
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", A+i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    int l = 1, r = n;
    bool valid = false;
    while(l < r) {
        int mid = l + r >> 1;
        if(f(mid) >= k) r = mid, valid = true;
        else l = mid + 1;
    }
    if(valid) printf("%d\n", r);
    else printf("-1\n");

    return 0;
}