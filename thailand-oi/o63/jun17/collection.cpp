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

int n, m;
long A[N];

class LazySegmentTree {
private:
    long t[N << 1], lz[N << 1];

    void push(var) {
        if(!lz[p]) return;
        t[p] += lz[p];
        if(l != r) lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
        lz[p] = 0;
    }

    template<typename T>
    void travel(int x, int y, const T &f, var) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) return f(p, l, r);
        travel(x, y, f, lb), travel(x, y, f, rb);
        t[p] = max(t[p << 1], t[p << 1 | 1]);
    }
public:
    void update(int x, int y, long k) {
        travel(x, y, [&](var) { lz[p] += k, push(p, l, r); });
    }

    long query(int x, int y, long ret = -1e18) {
        travel(x, y, [&](var) { ret = max(ret, t[p]); });
        return ret;
    }
} tree[20];

class Set {
private:
    priority_queue<long> Q1, Q2;
    
    void balance() {
        while(!Q2.empty() && Q1.top() == Q2.top())
            Q1.pop(), Q2.pop();
    }
public:
    void add(long x) { Q1.emplace(x); }
    void del(long x) { Q2.emplace(x); }

    pii get_max() {
        balance();
        pii ret(Q1.top(), -1e18); Q1.pop();
        balance(), ret.y = Q1.empty() ? -1e18 : Q1.top();
        Q1.emplace(ret.x);
        return ret;
    }
} S[N], ans;

long get_ans(int u) {
    pii ret = S[u].get_max();
    return max(A[u] + ret.x, A[u] + ret.x + ret.y);
}

long pre_ans[N];

vector<int> g[N];

int sz[N], chk[N], idx[20];
int rot[20][N], in[20][N], out[20][N], par[20][N];
long pre[20][N];

int get_sz(int u, int p) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p && !chk[v])
        sz[u] += get_sz(v, u);
    return sz[u];
}

int find_cen(int u, int p, int all, int &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, all, ret));
    if(mx <= (all + 1) / 2) ret = u;
    return sz[u];
}

void dfs(int u, int p, int root, int lvl) {
    par[lvl][u] = p;
    in[lvl][u] = ++idx[lvl], rot[lvl][u] = root;
    for(int v : g[u]) if(v != p && !chk[v])
        dfs(v, u, root, lvl);
    out[lvl][u] = idx[lvl];
    tree[lvl].update(in[lvl][u], out[lvl][u], A[u]);
}

int cpar[N], cdep[N];

void process(int u, int p, int lvl) {
    get_sz(u, u), find_cen(u, u, sz[u], u);
    S[u].add(0);
    for(int v : g[u]) if(!chk[v]) {
        dfs(v, u, v, lvl);
        S[u].add(pre[lvl][v] = tree[lvl].query(in[lvl][v], out[lvl][v]));
    }
    ans.add(pre_ans[u] = get_ans(u));
    cpar[u] = p, cdep[u] = lvl, chk[u] = 1;
    for(int v : g[u]) if(!chk[v])
        process(v, u, lvl + 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", A + i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    process(1, 0, 1);
    printf("%lld\n", ans.get_max().x);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        long dif = b - A[a];
        A[a] = b;
        ans.del(pre_ans[a]);
        ans.add(pre_ans[a] = get_ans(a));
        for(int u = cpar[a]; u; u = cpar[u]) {
            int lvl = cdep[u];
            tree[lvl].update(in[lvl][a], out[lvl][a], dif);
            S[u].del(pre[lvl][rot[lvl][a]]);
            S[u].add(pre[lvl][rot[lvl][a]] = tree[lvl].query(in[lvl][rot[lvl][a]], out[lvl][rot[lvl][a]]));
            ans.del(pre_ans[u]);
            ans.add(pre_ans[u] = get_ans(u));
        }
        printf("%lld\n", ans.get_max().x);
    }

    return 0;
}