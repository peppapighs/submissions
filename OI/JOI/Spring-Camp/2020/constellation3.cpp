#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

const int N = 1 << 18;

struct UnionFind {
    int par[N], l[N], r[N];

    UnionFind() {
        iota(par, par + N, 0);
        iota(l, r + N, 0);
        iota(r, r + N, 0);
    }

    int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return;
        par[a] = b, l[b] = min(l[b], l[a]), r[b] = max(r[b], r[a]);
    }
} dsu;

int n, k;
long t[N << 1], lz[N << 1];

void push(var) {
    if (lz[p] != 0) {
        t[p] += lz[p];
        if (l != r)
            lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
        lz[p] = 0;
    }
}

void update(int x, int y, long k, var) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz[p] += k, push(p, l, r);
        return;
    }
    update(x, y, k, lb), update(x, y, k, rb);
    t[p] = max(t[p << 1], t[p << 1 | 1]);
}

long query(int x, int y, var) {
    push(p, l, r);
    if (x > r || l > y)
        return 0;
    if (x <= l && r <= y)
        return t[p];
    return max(query(x, y, lb), query(x, y, rb));
}

int A[N];
vector<int> Y[N];
vector<pii> star_x[N], star_y[N];
bitset<N> chk;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        Y[A[i] + 1].emplace_back(i);
    }
    scanf("%d", &k);

    long sum = 0;
    for (int i = 1, x, y, c; i <= k; i++) {
        scanf("%d %d %d", &x, &y, &c);
        star_x[x].emplace_back(y, c);
        sum += c;
    }
    for (int i = 1; i <= n; i++) {
        sort(star_x[i].begin(), star_x[i].end());
        int pre = 0;
        for (pii p : star_x[i])
            if (p.y > pre) {
                star_y[p.x].emplace_back(i, p.y - pre);
                pre = p.y;
            }
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int x : Y[i]) {
            long val_l = 0, val_r = 0;
            if (x > 1 && chk[x - 1]) {
                int par_l = dsu.find(x - 1);
                val_l = query(dsu.l[par_l], dsu.r[par_l]);
            }
            if (x < n && chk[x + 1]) {
                int par_r = dsu.find(x + 1);
                val_r = query(dsu.l[par_r], dsu.r[par_r]);
            }
            if (x > 1 && chk[x - 1]) {
                int par_l = dsu.find(x - 1);
                update(dsu.l[par_l], dsu.r[par_l], val_r);
            }
            if (x < n && chk[x + 1]) {
                int par_r = dsu.find(x + 1);
                update(dsu.l[par_r], dsu.r[par_r], val_l);
            }
            update(x, x, val_l + val_r);
            if (x > 1 && chk[x - 1])
                dsu.unite(x - 1, x);
            if (x < n && chk[x + 1])
                dsu.unite(x, x + 1);
            chk[x] = 1;
        }
        for (pii p : star_y[i])
            update(p.x, p.x, p.y);
    }

    printf("%lld\n", sum - t[1]);

    return 0;
}