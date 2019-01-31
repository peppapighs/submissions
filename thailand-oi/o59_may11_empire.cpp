#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, q;
int col[N], cid[N], cycsz, id[N];
int idx, par[N], spi[N], rot[N], pos[N], dep[N], head[N];
int t[2][N<<1], lz[2][N<<1];
vector<int> g[N]; 
vector<int> cyc;

void dfs(int u, int p) {
    static vector<int> S;
    col[u] = 1, S.emplace_back(u);
    for(int v : g[u]) if(v != p) {
        if(!col[v]) dfs(v, u);
        else if(col[v] == 1) {
            for(int i = S.size()-1; S[i] != v; i--) 
                cyc.emplace_back(S[i]);
            cyc.emplace_back(v);
        }
    }
    col[u] = 2, S.pop_back();
}

int proc(int u, int p, int k, vector<int> &C) {
    par[u] = p, dep[u] = dep[p] + 1;
    id[u] = k, C.emplace_back(u);
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p && !cid[v]) {
        int z = proc(v, u, k, C);
        sz += z;
        ret = max(ret, pii(z, v));
    }
    spi[u] = ret.y;
    return sz;
}

void hld(int u) {
    vector<int> C;
    proc(u, u, cid[u], C);
    for(int i : C) {
        head[i] = u;
        if(spi[par[i]] != i) for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
    }
}

void push(int i, var) {
    if(!lz[i][p]) return;
    if(lz[i][p] == 1) t[i][p] = 0;
    else t[i][p] = r-l+1;
    if(l != r) lz[i][p<<1] = lz[i][p<<1|1] = lz[i][p];
    lz[i][p] = 0;
}

void update(int i, int x, int y, int k, var) {
    push(i, p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        lz[i][p] = k;
        push(i, p, l, r);
        return;
    }
    update(i, x, y, k, lb), update(i, x, y, k, rb);
    t[i][p] = t[i][p<<1] + t[i][p<<1|1];
}

void apply(int a, int b, int c) {
    while(rot[a] != rot[b]) {
        if(dep[rot[a]] < dep[rot[b]]) swap(a, b);
        update(0, pos[rot[a]], pos[a], c);
        a = par[rot[a]];
    }
    if(dep[a] > dep[b]) swap(a, b);
    update(0, pos[a]+1, pos[b], c);
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(1, 1);
    for(int v : cyc) cid[v] = ++cycsz;
    for(int v : cyc) hld(v);
    for(int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        c = c ? c : -1;
        if(id[a] == id[b]) apply(a, b, c);
        else {
            int x = head[a], y = head[b];
            apply(a, x, c), apply(b, y, c);
            if(cid[x] > cid[y]) swap(x, y);
            int d = cid[y] - cid[x];
            if(d<<1 == cycsz) update(1, 1, cycsz, c);
            else if(d<<1 < cycsz) update(1, cid[x], cid[y]-1, c);
            else update(1, 1, cid[x]-1, c, 1, 1, cycsz), update(1, cid[y], cycsz, c);
        }
        printf("%d\n", 1 + t[0][1] + (t[1][1] > 1 ? t[1][1]-1 : 0));
    }

    return 0;
}