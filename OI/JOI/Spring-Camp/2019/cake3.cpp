#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

vector<int> coord;
map<int, int> M;

struct node {
    long sum, cnt;
    node *l, *r;
    node(long sum, long cnt, node *l, node *r)
        : sum(sum), cnt(cnt), l(l), r(r) {}
};

node *newleaf(long sum, long cnt) {
    return new node(sum, cnt, nullptr, nullptr);
}
node *newpar(node *l, node *r) {
    return new node(l->sum + r->sum, l->cnt + r->cnt, l, r);
}

node *build(int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(0, 0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

node *update(long sum, int x, node *p, int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(p->sum + sum, p->cnt + 1);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(sum, x, p->l, l, mid), p->r);
    else
        return newpar(p->l, update(sum, x, p->r, mid + 1, r));
}

long query(int k, node *pa, node *pb, int l = 1, int r = coord.size()) {
    if (!k)
        return 0;
    if (l == r)
        return pb->sum - pa->sum;
    long sum_r = pb->r->sum - pa->r->sum, cnt_r = pb->r->cnt - pa->r->cnt;
    int mid = (l + r) >> 1;
    if (cnt_r >= k)
        return query(k, pa->r, pb->r, mid + 1, r);
    else
        return sum_r + query(k - cnt_r, pa->l, pb->l, l, mid);
}

int n, m;
node *t[N];
pii v[N];

long ans[N];

void solve(int l, int r, int optl, int optr) {
    if (l > r)
        return;
    int mid = (l + r) >> 1, idx = optl;
    for (int i = max(mid + m - 1, optl); i <= optr; i++) {
        long now = query(m - 2, t[mid], t[i - 1]) + v[i].x + v[mid].x -
                   2ll * (v[i].y - v[mid].y);
        if (now > ans[mid])
            ans[mid] = now, idx = i;
    }
    solve(l, mid - 1, optl, idx), solve(mid + 1, r, idx, optr);
}

int main() {
    fill_n(ans, N, -2e18);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &v[i].x, &v[i].y);
        coord.emplace_back(v[i].x);
    }
    sort(v + 1, v + n + 1,
         [&](const pii &a, const pii &b) { return a.y < b.y; });
    sort(coord.begin(), coord.end());
    for (int i = 1; i <= n; i++)
        if (!M.count(coord[i - 1]))
            M[coord[i - 1]] = i;

    t[0] = build();
    for (int i = 1; i <= n; i++)
        t[i] = update(v[i].x, M[v[i].x]++, t[i - 1]);

    solve(1, n - m + 1, 1, n);

    long ret = -2e18;
    for (int i = 1; i <= n; i++)
        ret = max(ret, ans[i]);
    printf("%lld\n", ret);

    return 0;
}