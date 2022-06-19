#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 18;
const int INF = 1e9 + 1;

int n, q;
int t1[N << 1], t2[N << 1], lz[N << 1];

void tag(int p, int x) {
    t2[p] = max(t2[p], t1[p] + x);
    lz[p] = max(lz[p], x);
}

void push(int p, int l, int r) {
    if (l != r)
        tag(p << 1, lz[p]), tag(p << 1 | 1, lz[p]);
    lz[p] = -INF;
}

void update(int x, int k, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (l == r)
        return void(t1[p] = k);
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(x, k, p << 1, l, mid);
    else
        update(x, k, p << 1 | 1, mid + 1, r);
    t1[p] = max(t1[p << 1], t1[p << 1 | 1]),
    t2[p] = max(t2[p << 1], t2[p << 1 | 1]);
}

void add(int x, int y, int k, int p = 1, int l = 1, int r = n) {
    if (x <= l && r <= y)
        return void(tag(p, k));
    push(p, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid)
        add(x, y, k, p << 1, l, mid);
    if (mid < y)
        add(x, y, k, p << 1 | 1, mid + 1, r);
    t1[p] = max(t1[p << 1], t1[p << 1 | 1]),
    t2[p] = max(t2[p << 1], t2[p << 1 | 1]);
}

int query(int x, int y, int p = 1, int l = 1, int r = n) {
    if (x <= l && r <= y)
        return t2[p];
    push(p, l, r);
    int mid = (l + r) >> 1, ret = -INF;
    if (x <= mid)
        ret = max(ret, query(x, y, p << 1, l, mid));
    if (mid < y)
        ret = max(ret, query(x, y, p << 1 | 1, mid + 1, r));
    return ret;
}

int H[N], A[N], B[N], ans[N];
vector<int> in[N], out[N];
vector<pii> Q[N];

void solve() {
    fill_n(t1, N << 1, -INF), fill_n(t2, N << 1, -INF),
        fill_n(lz, N << 1, -INF);
    for (int i = 1; i <= n; i++) {
        for (int x : in[i])
            update(x, -H[x]);
        if (i - A[i] > 0)
            add(max(i - B[i], 1), i - A[i], H[i]);
        for (pii p : Q[i])
            ans[p.y] = max(ans[p.y], query(p.x, i));
        for (int x : out[i])
            update(x, -INF);
    }
}

int main() {
    memset(ans, -1, sizeof ans);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", H + i, A + i, B + i);
        if (i + A[i] <= n)
            in[i + A[i]].emplace_back(i);
        if (i + B[i] <= n)
            out[i + B[i]].emplace_back(i);
    }
    scanf("%d", &q);
    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[b].emplace_back(a, i);
    }
    solve();
    for (int i = 1; i <= n; i++)
        H[i] = -H[i];
    solve();

    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);

    return 0;
}