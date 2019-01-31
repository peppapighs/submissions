#include <bits/stdc++.h>

#define iiii tuple<int, int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

int n, m;
int ans[N];
int dsu[N], par[N][18], dep[N], mx[N][18];
int spi[N], rot[N], pos[N];
int t[N], lz[N<<1];
vector<pii> g[N];
vector<iiii> E;

void push(int p, int l, int r) {
    if(!lz[p]) return;
    if(l != r) {
        lz[p<<1] = lz[p<<1] ? min(lz[p<<1], lz[p]) : lz[p];
        lz[p<<1|1] = lz[p<<1|1] ? min(lz[p<<1|1], lz[p]) : lz[p];
    } else t[l] = t[l] ? min(t[l], lz[p]) : lz[p];
    lz[p] = 0;
}

template<typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    int mid = (l + r) >> 1;
    travel(x, y, f, p<<1, l, mid), travel(x, y, f, p<<1|1, mid+1, r);
}

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int dfs(int u, int p) {
    int sz = 1; pii hv(0, -1);
    dep[u] = dep[p] + 1, par[u][0] = p;
    for(int i = 1; i <= 17; i++) {
        par[u][i] = par[par[u][i-1]][i-1];
        mx[u][i] = max(mx[u][i-1], mx[par[u][i-1]][i-1]);
    }
    for(pii v : g[u]) if(v.x != p) {
        mx[v.x][0] = v.y;
        int z = dfs(v.x, u);
        sz += z;
        hv = max(hv, pii(z, v.x));
    }
    spi[u] = hv.y;
    return sz;
}

void hld() {
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i][0]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
}

int lca(int a, int b) {
    int ret = 0;
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) {
        ret = max(ret, mx[a][i]);
        a = par[a][i];
    }
    if(a == b) return ret;
    for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) {
        ret = max({ret, mx[a][i], mx[b][i]});
        a = par[a][i], b = par[b][i];
    }
    return max({ret, mx[a][0], mx[b][0]});
}

int main() {
    fill_n(ans, N, -2);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) dsu[i] = i;
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(a, b, c, i);
    }
    sort(E.begin(), E.end(), [&](const iiii &a, const iiii &b) {
        return get<2>(a) < get<2>(b);
    });
    for(iiii &e : E) {
        int a, b, c, idx;
        tie(a, b, c, idx) = e;
        int pa = find(a), pb = find(b);
        if(pa != pb) {
            dsu[pa] = pb;
            g[a].emplace_back(b, c), g[b].emplace_back(a, c);
        }
    }
    dfs(1, 0), hld();
    for(int i = 1; i <= n; i++) dsu[i] = i;
    for(iiii &e : E) {
        int a, b, c, idx;
        tie(a, b, c, idx) = e;
        int pa = find(a), pb = find(b);
        if(pa == pb) {
            ans[idx] = lca(a, b) - 1;
            while(rot[a] != rot[b]) {
                if(dep[rot[a]] < dep[rot[b]]) swap(a, b);
                travel(pos[rot[a]], pos[a], [&](int p, int l, int r) {
                    lz[p] = lz[p] ? min(lz[p], c) : c;
                    push(p, l, r);
                });
                a = par[rot[a]][0];
            }
            if(dep[a] < dep[b]) swap(a, b);
            travel(pos[b]+1, pos[a], [&](int p, int l, int r) {
                lz[p] = lz[p] ? min(lz[p], c) : c;
                push(p, l, r);
            });
        } else dsu[pa] = pb;
    }
    for(iiii &e : E) {
        int a, b, c, idx;
        tie(a, b, c, idx) = e;
        if(ans[idx] != -2) continue;
        if(par[a][0] != b) swap(a, b);
        travel(pos[a], pos[a], [&](int p, int l, int r) {
            ans[idx] = t[l] - 1;
        });
    }
    for(int i = 1; i <= m; i++) printf("%d ", ans[i]);
    printf("\n");

    return 0;
}