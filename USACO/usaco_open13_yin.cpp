#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, book;
long ans;
int sz[N], chk[N], mxnode, mxsub;
int cnt[2*N], dp[2][N], t[2][N];
vector<pii> g[N];

int getsz(int u, int p) {
    sz[u] = 1;
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) sz[u] += getsz(v.x, u);
    return sz[u];
}

void find_cen(int u, int p, int all) {
    int ret = all - sz[u];
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) {
        find_cen(v.x, u, all);
        ret = max(ret, sz[v.x]);
    }
    if(ret < mxsub) mxnode = u, mxsub = ret;
}

void dfs(int u, int p, int len, bool fill) {
    bool m = (cnt[len + N] > 0);
    if(!fill) {
        if(len == 0 && m) ++ans;
        if(t[1][N - len] == book) ans += dp[1][N - len];
        if((len == 0 || m) && t[0][N - len] == book) ans += dp[0][N - len];
    } else {
        if(t[m][len + N] < book) t[m][len + N] = book, dp[m][len + N] = 1;
        else ++dp[m][len + N];
    }
    ++cnt[len + N];
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) dfs(v.x, u, len + v.y, fill);
    --cnt[len + N];
}

void proc(int u) {
    ++book;
    if(getsz(u, u) <= 1) return;
    mxsub = sz[u] + 1;
    find_cen(u, u, sz[u]);
    u = mxnode;
    for(pii v : g[u]) if(!chk[v.x]) {
        dfs(v.x, u, v.y, 0);
        dfs(v.x, u, v.y, 1);
    }
    chk[u] = 1;
    for(pii v : g[u]) if(!chk[v.x]) proc(v.x);
}

int main() {
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;

    for(int i = 1, a, b, c; i < n; i++) {
        cin >> a >> b >> c;
        c = c ? 1 : -1;
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    } 
    proc(1);
    cout << ans << endl;

    return 0;
}
