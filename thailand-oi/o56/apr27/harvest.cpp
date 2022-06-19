#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;
const int M = 1e9 + 9;

#define var int p = 1, int l = 1, int r = n
#define mid (l + r >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

int n, q, e;
int dep[N], par[N], rot[N], pos[N], spi[N];
long t[N << 1], lz[N << 1];
vector<int> g[N];

int dfs(int u, int p) {
    dep[u] = dep[p] + 1, par[u] = p;
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u])
        if (v != p) {
            int z = dfs(v, u);
            sz += z;
            ret = max(ret, pii(z, v));
        }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    for (int i = 0, idx = 0; i < n; i++)
        if (spi[par[i]] != i)
            for (int j = i; j != -1; j = spi[j])
                rot[j] = i, pos[j] = ++idx;
}

void build(var) {
    if (l == r)
        return void(t[p] = 1);
    build(lb), build(rb);
    t[p] = (t[p << 1] + t[p << 1 | 1]) % M;
}

void push(var) {
    if (lz[p] == 1)
        return;
    t[p] = (t[p] * lz[p]) % M;
    if (l != r) {
        lz[p << 1] = (lz[p << 1] * lz[p]) % M;
        lz[p << 1 | 1] = (lz[p << 1 | 1] * lz[p]) % M;
    }
    lz[p] = 1;
}

template <typename T> void travel(int x, int y, const T &f, var) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y)
        return f(p, l, r);
    travel(x, y, f, lb), travel(x, y, f, rb);
    t[p] = (t[p << 1] + t[p << 1 | 1]) % M;
}

int main() {
    fill_n(lz, N << 1, 1);
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    dfs(0, 0), hld();
    build();
    scanf("%d %d", &q, &e);
    q += e;
    for (int i = 1, a, b, c; i <= q; i++) {
        scanf("%d", &a);
        if (a == 0) {
            scanf("%d %d", &b, &c);
            while (rot[b] != rot[c]) {
                if (dep[rot[b]] < dep[rot[c]])
                    swap(b, c);
                travel(pos[rot[b]], pos[b], [&](var) {
                    lz[p] = (lz[p] * 2) % M;
                    push(p, l, r);
                });
                b = par[rot[b]];
            }
            if (dep[b] > dep[c])
                swap(b, c);
            travel(pos[b], pos[c], [&](var) {
                lz[p] = (lz[p] * 2) % M;
                push(p, l, r);
            });
        } else
            printf("%lld\n", t[1]);
    }

    return 0;
}