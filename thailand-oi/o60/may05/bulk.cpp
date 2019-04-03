#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;
const int INF = 1e9+1;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

struct node {
    int d, cnt; pii p;
    node() { }
    node(int d, int cnt, pii p) : d(d), cnt(cnt), p(p) { }
    friend node operator+(const node &a, const node &b) {
        node ret;
        ret.d = a.d + b.d;
        ret.cnt = a.cnt + b.cnt;
        if(a.p.x != b.p.x) ret.p = max(a.p, b.p);
        else ret.p = pii(a.p.x, a.p.y + b.p.y);
        return ret;
    }
};

int n, q, deg[N], sum;
node t[N<<1];
pii lz[N<<1];
vector<int> g[N];
vector<iii> E;

void push(var) {
    if(!lz[p].x) return;
    if(lz[p].x == 1) {
        t[p].d += (r - l + 1) * lz[p].y;
        if(t[p].p.x != -INF) t[p].p.x += lz[p].y;
        if(l != r) {
            if(lz[p<<1].x != 2) lz[p<<1].x = 1;
            if(lz[p<<1|1].x != 2) lz[p<<1|1].x = 1;
            lz[p<<1].y += lz[p].y;
            lz[p<<1|1].y += lz[p].y;
        }
    } else {
        t[p].d = (r - l + 1) * lz[p].y;
        if(t[p].p.x != -INF) t[p].p = pii(lz[p].y, t[p].cnt);
        if(l != r) lz[p<<1] = lz[p<<1|1] = lz[p];
    }
    lz[p] = pii(0, 0);
}

void build(var) {
    if(l == r) {
        int a, b, c;
        tie(a, b, c) = E[l-1];
        bool cyc = (deg[a] > 1 && deg[b] > 1);
        t[p] = node(c, cyc, cyc ? pii(c, 1) : pii(-INF, 0));
        return;
    }
    build(lb), build(rb);
    t[p] = t[p<<1] + t[p<<1|1]; 
}

void update(int x, int y, int st, int k, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        lz[p].y += k;
        if(lz[p].x != 2) lz[p].x = st;
        push(p, l, r);
        return;
    }
    update(x, y, st, k, lb), update(x, y, st, k, rb);
    t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b), g[b].emplace_back(a);
        E.emplace_back(a, b, c);
        ++deg[a], ++deg[b];
    }
    queue<int> Q;
    for(int i = 1; i <= n; i++) if(deg[i] == 1) Q.emplace(i);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int v : g[u]) if(--deg[v] == 1)
            Q.emplace(v);
    }
    build();
    for(int i = 1, T, a, b, c; i <= q; i++) {
        scanf("%d %d %d %d", &T, &a, &b, &c);
        update(a, b, T, c);
        printf("%d %d\n", t[1].d - t[1].p.x, t[1].p.y);
    }

    return 0;
}
