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

int n, k;
int par[N], rot[N], pos[N], spi[N];
int t[N<<1][20], lz[N<<1];
vector<int> g[N];

void push(var) {
    if(lz[p]) {
        vector<int> V(20);
        for(int i = 0; i < k; i++) V[(i + lz[p]) % k] = t[p][i];
        for(int i = 0; i < k; i++) t[p][i] = V[i];
        if(l != r) lz[p<<1] += lz[p], lz[p<<1|1] += lz[p];
        lz[p] = 0;
    }
}

void build(var) {
    if(l == r) return void(t[p][0] = 1);
    build(lb), build(rb);
    t[p][0] = t[p<<1][0] + t[p<<1|1][0];
}

void update(int x, int y, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        lz[p] = (lz[p] + 1) % k;
        push(p, l, r);
        return;
    }
    update(x, y, lb), update(x, y, rb);
    for(int i = 0; i < k; i++) t[p][i] = t[p<<1][i] + t[p<<1|1][i];
}

int dfs(int u, int p) {
    par[u] = p;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        sz += z, ret = max(ret, pii(z, v));
    }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
    build();
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 2, a; i <= n; i++) {
        scanf("%d", &a);
        g[i].emplace_back(a), g[a].emplace_back(i);
    }
    dfs(1, 0), hld();
    for(int a = 1; a; a = par[rot[a]]) update(pos[rot[a]], pos[a]);
    for(int i = 2; i <= n; i++) {
        for(int a = i; a; a = par[rot[a]]) update(pos[rot[a]], pos[a]);
        if(i % k) printf("NO\n");
        else if(t[1][0] - n + i == i / k) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
