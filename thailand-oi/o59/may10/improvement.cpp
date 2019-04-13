#include <bits/stdc++.h>

#define long long long
#define pii pair<int, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, weight[N];
long cnt[N];
vector<pii> g[N];
vector<int> coord;
bitset<N> fac;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }
void update(long t[], int x, int k) { for(int i = x; i < N; i += i & -i) t[i] += k; }
long query(long t[], int x, long ret = 0) { for(int i = x; i; i -= i & -i) ret += t[i]; return ret; }

int sz[N], chk[N];

int getsz(int u, int p) { sz[u] = 1; for(pii v : g[u]) if(v.x != p && !chk[v.x]) sz[u] += getsz(v.x, u); return sz[u]; }

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(pii v : g[u]) if(v.x != p && !chk[v.x])
        mx = max(mx, find_cen(v.x, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

int idx;
int hv[N], in[N], out[N], pos[N], mxval[N];
long t1[N], t2[N];

int pre(int u, int p, int mx) {
    in[u] = ++idx, pos[idx] = u;
    if(fac[u]) update(t1, get(mxval[u] = mx), 1);
    int sz = 1; pii ret(0, -1);
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) {
        int z = pre(v.x, u, max(mx, weight[v.y]));
        sz += z, ret = max(ret, pii(z, v.x));
    }
    hv[u] = ret.y, out[u] = idx;
    return sz;
}


void add(int u, int p, int k) {
    if(fac[u]) update(t1, get(mxval[u]), k);
    for(pii v : g[u]) if(v.x != p && !chk[v.x])
        add(v.x, u, k);
}

void dfs(int u, int p, int ep, int mx, bool keep) {
    mx = max(mx, weight[ep]);

    for(pii v : g[u]) if(v.x != p && v.x != hv[u] && !chk[v.x])
        dfs(v.x, u, v.y, mx, 0);
    for(pii v : g[u]) if(v.x == hv[u])
        dfs(v.x, u, v.y, mx, 1);

    for(pii v : g[u]) if(v.x != p && v.x != hv[u] && !chk[v.x])
        for(int i = in[v.x]; i <= out[v.x]; i++) if(fac[pos[i]])
            update(t2, get(mxval[pos[i]]), 1);
    if(fac[u]) update(t2, get(mxval[u]), 1);

    if(weight[ep] == mx) cnt[ep] += 1ll * query(t1, get(mx)) * query(t2, get(mx));

    if(!keep) for(int i = in[u]; i <= out[u]; i++) if(fac[pos[i]])
        update(t2, get(mxval[pos[i]]), -1);
}

void proc(int u) {
    getsz(u, u);
    pii ret(sz[u]+1, -1);
    find_cen(u, u, sz[u], ret);
    chk[u = ret.y] = true, idx = 0;
    pre(u, u, 0);
    for(pii v : g[u]) if(!chk[v.x]) {
        add(v.x, u, -1);
        dfs(v.x, u, v.y, 0, 0);
        add(v.x, u, 1);
    } 
    add(u, u, -1);
    for(pii v : g[u]) if(!chk[v.x]) proc(v.x);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        fac[a] = true;
    }
    for(int i = 0, a, b; i < n-1; i++) {
        scanf("%d %d %d", &a, &b, weight+i);
        g[a].emplace_back(b, i), g[b].emplace_back(a, i);
        coord.emplace_back(weight[i]);
    }
    coord.emplace_back(0);
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    proc(0);

    long mx = 0;
    vector<int> ans;
    for(int i = 0; i < n-1; i++) {
        if(cnt[i] == mx) ans.emplace_back(i);
        else if(cnt[i] > mx) mx = cnt[i], ans = vector<int>(1, i);
    }
    printf("%d %lld\n", (int)ans.size(), mx);
    for(int i : ans) printf("%d ", i);
    printf("\n");

    return 0;
}