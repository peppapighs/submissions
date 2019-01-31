#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
void addto(pii &a, pii b) { a = add(a, b); }

int n, q;
vector<int> g[N];
vector<iii> E;
int in[N], out[N], dep[N], weight[N<<1];
pii t[N<<1], lz[N<<1];

void push(int p, int l, int r) {
    if(lz[p] == pii(0, 0)) return;
    addto(t[p], lz[p]);
    if(l != r) addto(lz[p<<1], lz[p]), addto(lz[p<<1|1], lz[p]);
    lz[p] = { 0, 0 };
}

template<typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    int mid = (l + r) >> 1;
    travel(x, y, f, p<<1, l, mid), travel(x, y, f, p<<1|1, mid+1, r);
    t[p] = pii(0, min(t[p<<1].y, t[p<<1|1].y));
}

void dfs(int u, int p) {
    static int idx = 0;
    dep[u] = dep[p] + 1, in[u] = ++idx;
    for(int v : g[u]) if(v != u) dfs(v, u);
    out[u] = idx;
}

int main() {
    E.emplace_back(0, 0, 0);
    scanf("%d %d", &n, &q);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b); weight[i] = c;
        E.emplace_back(a, b, i);
    }
    dfs(1, 1);
    for(iii &e : E) {
        int a, b, idx;
        tie(a, b, idx) = e;
        travel(in[b], out[b], [&](int p, int l, int r) {
            lz[p].x += weight[idx], lz[p].y += weight[idx];
            push(p, l, r);
        });
    }
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        weight[i+n-1] = c;
        E.emplace_back(b, a, i+n-1);
        travel(in[a], in[a], [&](int p, int l, int r) {
            lz[p].y += c;
            push(p, l, r);
        });
    }
    for(int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d %d", &T, &a, &b);
        if(T == 1) {
            int u = get<1>(E[a]);
            travel(in[u], a < n ? out[u] : in[u], [&](int p, int l, int r) {
                if(a < n) lz[p].x += b - weight[a];
                lz[p].y += b - weight[a];
                push(p, l, r);
            });
            weight[a] = b;
        } else {
            long sum = 0, mn = 1e18;
            travel(in[b], in[b], [&](int p, int l, int r) {
                sum += t[p].x;
            });
            travel(in[a], in[a], [&](int p, int l, int r) {
                sum -= t[p].x;
            });
            if(in[a] > in[b] || out[b] > out[a]) travel(in[a], out[a], [&](int p, int l, int r) {
                mn = min(mn, t[p].y);
            });
            else mn = 0;
            printf("%lld\n", sum + mn);
        }
    }

    return 0;
}