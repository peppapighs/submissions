#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;

int n, m;
int t[N], lz[N << 1];
vector<int> g[N];

int spi[N], par[N], dep[N], rot[N], pos[N];

int dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        sz += z, ret = max(ret, pii(z, v));
    }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    dfs(1, 1);
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
}

void push(int p, int l, int r) {
    if(l == r) return void(t[l] = lz[p]);
    else {
        lz[p<<1] = min(lz[p<<1], lz[p]);
        lz[p<<1|1] = min(lz[p<<1|1], lz[p]);
    }
}

template<typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    int mid = (l + r) >> 1;
    travel(x, y, f, p<<1, l, mid), travel(x, y, f, p<<1|1, mid+1, r);
}

vector<pii> E;

int main() {
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);

    fill_n(t, N, 1e9 + 1), fill_n(lz, N, 1e9 + 1);

    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
        E.emplace_back(a, b);
    }
    hld();
    for(pii &e : E) if(dep[e.x] < dep[e.y]) swap(e.x, e.y);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        while(rot[a] != rot[b]) {
            if(dep[rot[a]] < dep[rot[b]]) swap(a, b);
            travel(pos[rot[a]], pos[a], [&](int p, int l, int r) {
                lz[p] = min(lz[p], c);
                push(p, l, r);
            });
            a = par[rot[a]];
        }
        if(dep[a] < dep[b]) swap(a, b);
        travel(pos[b] + 1, pos[a], [&](int p, int l, int r) {
            lz[p] = min(lz[p], c);
            push(p, l, r);
        });
    }
    for(pii e : E) travel(pos[e.x], pos[e.x], [&](int p, int l, int r) {
        if(t[l] == 1e9 + 1) printf("-1\n");
        else printf("%d\n", t[l]);
    });

    return 0;
}