#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

int n, m, col[N], incyc[N], hd[N];
int cid[N], par[N], dep[N], rot[N], spi[N], pos[N];
vector<int> g[N], cyc;

void findcyc(int u, int p) {
    static vector<int> S;
    col[u] = 1, S.emplace_back(u);
    for (int v : g[u])
        if (v != p) {
            if (!col[v])
                findcyc(v, u);
            else if (col[v] == 1)
                for (int i = S.size() - 1; ~i; i--) {
                    cyc.emplace_back(S[i]);
                    incyc[S[i]] = 1;
                    if (S[i] == v)
                        break;
                }
        }
    col[u] = 2, S.pop_back();
}

int dfs(int u, int p, int h, int id) {
    par[u] = p, dep[u] = dep[p] + 1, cid[u] = id, hd[u] = h;
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u])
        if (v != p && !incyc[v]) {
            int z = dfs(v, u, h, id);
            sz += z, ret = max(ret, pii(z, v));
        }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    for (int i = 1, idx = 0; i <= n; i++)
        if (spi[par[i]] != i)
            for (int j = i; j != -1; j = spi[j])
                rot[j] = i, pos[j] = ++idx;
}

int t1[N << 1], lz1[N << 1];

void push1(var) {
    if (!lz1[p])
        return;
    if (lz1[p] == 1)
        t1[p] = r - l + 1;
    else
        t1[p] = 0;
    if (l != r)
        lz1[p << 1] = lz1[p << 1 | 1] = lz1[p];
    lz1[p] = 0;
}

void update1(int x, int y, int c, var) {
    push1(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz1[p] = c;
        push1(p, l, r);
        return;
    }
    update1(x, y, c, lb), update1(x, y, c, rb);
    t1[p] = t1[p << 1] + t1[p << 1 | 1];
}

int t2[N << 1], lz2[N << 1];

void push2(var) {
    if (!lz2[p])
        return;
    if (lz2[p] == 1)
        t2[p] = r - l + 1;
    else
        t2[p] = 0;
    if (l != r)
        lz2[p << 1] = lz2[p << 1 | 1] = lz2[p];
    lz2[p] = 0;
}

void update2(int x, int y, int c, var) {
    push2(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz2[p] = c;
        push2(p, l, r);
        return;
    }
    update2(x, y, c, lb), update2(x, y, c, rb);
    t2[p] = t2[p << 1] + t2[p << 1 | 1];
}

void walk(int a, int b, int c) {
    while (rot[a] != rot[b]) {
        if (dep[rot[a]] < dep[rot[b]])
            swap(a, b);
        update1(pos[rot[a]], pos[a], c);
        a = par[rot[a]];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update1(pos[a] + 1, pos[b], c);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    findcyc(1, 1);
    int csz = 0;
    for (int u : cyc)
        dfs(u, u, u, ++csz);
    hld();
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        c = c ? -1 : 1;
        if (cid[a] == cid[b])
            walk(a, b, c);
        else {
            if (cid[a] > cid[b])
                swap(a, b);
            int pa = hd[a], pb = hd[b];
            walk(a, pa, c), walk(b, pb, c);
            if (2 * (cid[b] - cid[a]) <= csz)
                update2(cid[a], cid[b] - 1, c);
            if (2 * (cid[b] - cid[a]) >= csz)
                update2(1, cid[a] - 1, c), update2(cid[b], csz, c);
        }
        printf("%d\n", 1 + t1[1] + (t2[1] > 1 ? t2[1] - 1 : 0));
    }

    return 0;
}
