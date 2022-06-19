#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

#define var int p = 1, int l = 1, int r = leaf.size() - 1
#define mid (l + r >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

const int N = 1 << 20;

int n, q, out[N];
long d[N], t[N << 1], lz[N << 1], ans[N];
vector<int> leaf;
vector<pii> g[N];
vector<iii> Q[N], E;

int get(int x) {
    return lower_bound(leaf.begin(), leaf.end(), x) - leaf.begin();
}

void push(var) {
    if (!lz[p])
        return;
    t[p] += lz[p];
    if (l != r)
        lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
    lz[p] = 0;
}

template <typename T> void travel(int x, int y, const T &f, var) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y)
        return f(p, l, r);
    travel(x, y, f, lb), travel(x, y, f, rb);
    t[p] = min(t[p << 1], t[p << 1 | 1]);
}

int proc(int u, int p) {
    int now = u;
    if (g[u].size() == 1)
        leaf.emplace_back(u);
    for (pii v : g[u])
        if (v.x != p) {
            d[v.x] = d[u] + v.y;
            now = max(now, proc(v.x, u));
        }
    out[u] = now;
    return now;
}

void dfs(int u, int p) {
    for (iii now : Q[u]) {
        int l, r, idx;
        tie(l, r, idx) = now;
        ans[idx] = LLONG_MAX;
        travel(get(l), get(r) - (leaf[get(r)] != r),
               [&](var) { ans[idx] = min(ans[idx], t[p]); });
    }
    for (pii v : g[u])
        if (v.x != p) {
            travel(1, leaf.size() - 1, [&](var) {
                lz[p] += v.y;
                push(p, l, r);
            });
            travel(get(v.x), get(out[v.x]) - (leaf[get(out[v.x])] != out[v.x]),
                   [&](var) {
                       lz[p] -= 2 * v.y;
                       push(p, l, r);
                   });
            dfs(v.x, u);
            travel(1, leaf.size() - 1, [&](var) {
                lz[p] -= v.y;
                push(p, l, r);
            });
            travel(get(v.x), get(out[v.x]) - (leaf[get(out[v.x])] != out[v.x]),
                   [&](var) {
                       lz[p] += 2 * v.y;
                       push(p, l, r);
                   });
        }
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 2, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        g[i].emplace_back(a, b), g[a].emplace_back(i, b);
        E.emplace_back(a, i, b);
    }
    for (int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        Q[a].emplace_back(b, c, i);
    }
    leaf.emplace_back(0);
    proc(1, 1);
    sort(leaf.begin(), leaf.end());
    for (iii e : E) {
        int a, b, c;
        tie(a, b, c) = e;
        a = max(a, b);
        travel(get(a), get(out[a]) - (leaf[get(out[a])] != out[a]), [&](var) {
            lz[p] += c;
            push(p, l, r);
        });
    }
    dfs(1, 1);
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}