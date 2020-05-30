#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 100;
const int M1 = 1e9 + 7;
const int M2 = 1e9 + 9;

int ptr;

struct Hash {
    long h1, h2;
    Hash() {}
    Hash(long h) : h1(h % M1), h2(h % M2) {}
    Hash(long h1, long h2) : h1(h1), h2(h2) {}

    bool empty() { return (h1 == 0 && h2 == 0); }

    friend Hash operator+(const Hash &a, const Hash &b) {
        return Hash((a.h1 + b.h1) % M1, (a.h2 + b.h2) % M2);
    }
    friend Hash operator*(const Hash &a, const Hash &b) {
        return Hash((a.h1 * b.h1) % M1, (a.h2 * b.h2) % M2);
    }
    friend bool operator==(const Hash &a, const Hash &b) {
        return (a.h1 == b.h1 && a.h2 == b.h2);
    }
} mpow[N];

struct node {
    Hash h;
    int l, r;
    node() {}
    node(Hash h, int l, int r) : h(h), l(l), r(r) {}
} t[N * 100];

int new_leaf(Hash hsh) {
    t[++ptr] = node(hsh, -1, -1);
    return ptr;
}

int new_par(int l, int r) {
    t[++ptr] = node(t[l].h + t[r].h, l, r);
    return ptr;
}

int build(bool inf, int l = 0, int r = N - 1) {
    if(l == r) return new_leaf(inf ? mpow[l] : Hash(0));
    int mid = (l + r) >> 1;
    return new_par(build(inf, l, mid), build(inf, mid + 1, r));
}

bool get_pos(int x, int p, int l = 0, int r = N - 1) {
    if(l == r) return (!t[p].h.empty()); 
    int mid = (l + r) >> 1;
    if(x <= mid) return get_pos(x, t[p].l, l, mid);
    else return get_pos(x, t[p].r, mid + 1, r);
}

int increment(int x, int p, int l = 0, int r = N - 1) {
    if(l == r) return new_leaf(t[p].h.empty() ? mpow[l] : Hash(0));
    int mid = (l + r) >> 1;
    if(x <= mid) return new_par(increment(x, t[p].l, l, mid), t[p].r);
    else return new_par(t[p].l, increment(x, t[p].r, mid + 1, r));
}

int add(int x, int p) {
    p = increment(x, p);
    while(!get_pos(x++, p)) p = increment(x, p);
    return p;
}

bool compare(int p1, int p2, int l = 0, int r = N - 1) {
    if(l == r) return (t[p1].h.empty() && !t[p2].h.empty());
    int mid = (l + r) >> 1;
    if(t[t[p1].r].h == t[t[p2].r].h) return compare(t[p1].l, t[p2].l, l, mid);
    else return compare(t[p1].r, t[p2].r, mid + 1, r);
}

struct item {
    int d, u;
    item(int d, int u) : d(d), u(u) {}
    friend bool operator<(const item &a, const item &b) {
        return !compare(a.d, b.d);
    }
};

int n, m, s, e;
int d[N], par[N];
vector<pii> g[N];
priority_queue<item> Q;

int main() {
    mpow[0] = Hash(1);
    for(int i = 1; i < N; i++) mpow[i] = mpow[i - 1] * Hash(2);
    
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c); 
    }
    scanf("%d %d", &s, &e);

    int INF = build(true);
    for(int i = 1; i <= n; i++) d[i] = INF;

    par[s] = s;
    Q.emplace(d[s] = build(false), s);
    while(!Q.empty()) {
        item u = Q.top(); Q.pop();
        if(u.d != d[u.u]) continue;
        for(pii v : g[u.u]) {
            int sum = add(v.y, u.d);
            if(compare(sum, d[v.x])) {
                Q.emplace(d[v.x] = sum, v.x);
                par[v.x] = u.u;
            }
        }
    }
    if(!par[e]) return !printf("-1\n");

    printf("%lld\n", t[d[e]].h.h1);
    vector<int> vec;
    for(int i = e; vec.empty() || vec.back() != s; i = par[i])
        vec.emplace_back(i);
    reverse(vec.begin(), vec.end());

    printf("%d\n", (int)vec.size());
    for(int u : vec) printf("%d ", u);
    printf("\n");

    return 0;
}