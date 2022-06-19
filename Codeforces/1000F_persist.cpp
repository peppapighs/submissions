#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int N = 5e5 + 5;

struct node {
    pii d;
    node *l, *r;
    node() {}
    node(pii d, node *l, node *r) : d(d), l(l), r(r) {}
};

node *newleaf(pii a) { return new node(a, nullptr, nullptr); }

node *newpar(node *l, node *r) { return new node(min(l->d, r->d), l, r); }

int n, m, arr[N], pos[N];

node *build(int l = 1, int r = n) {
    if (l == r)
        return newleaf(pii(INT_MAX, 0));
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

node *update(int x, pii val, node *p, int l = 1, int r = n) {
    if (l == r)
        return newleaf(val);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(x, val, p->l, l, mid), p->r);
    return newpar(p->l, update(x, val, p->r, mid + 1, r));
}

pii query(int x, int y, node *p, int l = 1, int r = n) {
    if (x > r || l > y)
        return pii(INT_MAX, 0);
    if (x <= l && r <= y)
        return p->d;
    int mid = (l + r) >> 1;
    return min(query(x, y, p->l, l, mid), query(x, y, p->r, mid + 1, r));
}

node *persist[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    persist[0] = build();
    for (int i = 1; i <= n; i++) {
        node *ret = persist[i - 1];
        if (pos[arr[i]])
            ret = update(pos[arr[i]], pii(INT_MAX, 0), persist[i - 1]);
        persist[i] = update(i, pii(pos[arr[i]], arr[i]), ret);
        pos[arr[i]] = i;
    }
    scanf("%d", &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        pii ans = query(a, b, persist[b]);
        if (ans.first < a)
            printf("%d\n", ans.second);
        else
            printf("0\n");
    }

    return 0;
}