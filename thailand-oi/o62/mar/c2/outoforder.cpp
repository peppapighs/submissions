#include <bits/stdc++.h>

#define long long long

using namespace std;

struct node {
    int d;
    node *l, *r;
    node(int d, node *l, node *r) : d(d), l(l), r(r) {}
};

node *newleaf(int d) { return new node(d, nullptr, nullptr); }
node *newpar(node *l, node *r) { return new node(l->d + r->d, l, r); }

const int N = 1e5 + 5;

int n, X[N], D[N];
long ans;
node *l[N], *r[N];
vector<int> coord;

node *build(int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

node *update(int x, node *p, int l = 1, int r = coord.size()) {
    if (l == r)
        return newleaf(1);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(x, p->l, l, mid), p->r);
    else
        return newpar(p->l, update(x, p->r, mid + 1, r));
}

int query(int x, int y, node *p1, node *p2, int l = 1, int r = coord.size()) {
    if (x > r || l > y)
        return 0;
    if (x <= l && r <= y)
        return p1->d - p2->d;
    int mid = (l + r) >> 1;
    return query(x, y, p1->l, p2->l, l, mid) +
           query(x, y, p1->r, p2->r, mid + 1, r);
}

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", X + i), coord.emplace_back(X[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", D + i);
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    l[0] = r[n + 1] = build();
    for (int i = 1; i <= n; i++)
        l[i] = update(get(X[i]), l[i - 1]);
    for (int i = n; i; i--)
        r[i] = update(get(X[i]), r[i + 1]);
    for (int i = 1; i <= n; i++) {
        int L = max(1, i - D[i]), R = min(n, i + D[i]);
        ans += query(get(X[i]) + 1, coord.size(), r[L], r[i]);
        ans += query(1, get(X[i]) - 1, l[R], l[i]);
    }
    printf("%lld\n", ans);

    return 0;
}