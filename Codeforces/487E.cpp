#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

struct Heap {
    priority_queue<int, vector<int>, greater<int>> P, Q;
    void add(int x) { P.emplace(x); }
    void del(int x) { Q.emplace(x); }
    void adjust() {
        while (!Q.empty() && P.top() == Q.top())
            P.pop(), Q.pop();
    }
    int top() {
        adjust();
        return P.top();
    }
} Q[N];

struct SegmentTree {
    int t[N << 1];
    void update(int x, int k) {
        for (t[x += N] = k; x != 1; x >>= 1)
            t[x >> 1] = min(t[x], t[x ^ 1]);
    }
    int query(int l, int r) {
        int ret = 2e9;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = min(ret, t[l++]);
            if (r & 1)
                ret = min(ret, t[--r]);
        }
        return ret;
    }
} tree;

int n, sz, m, q, w[N];
vector<vector<int>> g(N), bcc;

int low[N], pre[N], art[N], id[N];
bitset<N> idart;

void tarjan(int u, int p) {
    static int idx = 0;
    static stack<int> S;

    pre[u] = low[u] = ++idx;
    S.emplace(u);
    int child = 0;
    for (int v : g[u])
        if (v != p) {
            if (!pre[v]) {
                ++child;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if ((!p && child > 1) || (p && low[v] >= pre[u]))
                    art[u] = true;
                if (low[v] >= pre[u]) {
                    bcc.emplace_back(1, u);
                    while (bcc.back().back() != v) {
                        bcc.back().emplace_back(S.top());
                        S.pop();
                    }
                }
            } else
                low[u] = min(low[u], pre[v]);
        }
}

int par[N], dep[N], spi[N], rot[N], pos[N];

int dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u])
        if (v != p) {
            int z = dfs(v, u);
            sz += z, ret = max(ret, pii(z, v));
        }
    spi[u] = ret.y;
    return sz;
}

void gen_bct() {
    tarjan(1, 0);
    g.clear(), g.emplace_back(0);
    for (int i = 1; i <= n; i++)
        if (art[i]) {
            g.emplace_back(0);
            idart[id[i] = g.size() - 1] = true;
            Q[id[i]].add(w[i]);
        }
    for (vector<int> &cc : bcc) {
        g.emplace_back(0);
        for (int u : cc) {
            if (art[u])
                g[g.size() - 1].emplace_back(id[u]),
                    g[id[u]].emplace_back(g.size() - 1);
            else
                id[u] = g.size() - 1, Q[g.size() - 1].add(w[u]);
        }
    }
    sz = g.size() - 1;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        if (art[i])
            Q[par[id[i]]].add(w[i]);
    for (int i = 1, idx = 0; i <= sz; i++)
        if (spi[par[i]] != i)
            for (int j = i; j != -1; j = spi[j])
                rot[j] = i, pos[j] = ++idx;
    for (int i = 1; i <= sz; i++)
        tree.update(pos[i], Q[i].top());
}

pii hld_query(int a, int b) {
    int ans = 2e9;
    while (rot[a] != rot[b]) {
        if (dep[rot[a]] < dep[rot[b]])
            swap(a, b);
        ans = min(ans, tree.query(pos[rot[a]], pos[a]));
        a = par[rot[a]];
    }
    if (dep[a] < dep[b])
        swap(a, b);
    ans = min(ans, tree.query(pos[b], pos[a]));
    return pii(ans, b);
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    gen_bct();

    for (int i = 1; i <= q; i++) {
        char T;
        int a, b;
        scanf(" %c %d %d", &T, &a, &b);
        if (T == 'A') {
            if (a == b)
                printf("%d\n", w[a]);
            else {
                a = id[a], b = id[b];
                if (a == b) {
                    int now = tree.query(pos[a], pos[a]);
                    if (!idart[a] && par[a])
                        now = min(now, Q[par[a]].top());
                    printf("%d\n", now);
                } else {
                    pii now = hld_query(a, b);
                    if (!idart[now.y] && par[now.y])
                        now.x = min(now.x, Q[par[now.y]].top());
                    printf("%d\n", now.x);
                }
            }
        } else {
            int pre = w[a];
            w[a] = b, a = id[a];
            Q[a].del(pre), Q[a].add(b);
            tree.update(pos[a], Q[a].top());
            if (idart[a] && par[a]) {
                Q[par[a]].del(pre), Q[par[a]].add(b);
                tree.update(pos[par[a]], Q[par[a]].top());
            }
        }
    }

    return 0;
}