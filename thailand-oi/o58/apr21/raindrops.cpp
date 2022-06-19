#include <bits/stdc++.h>

#define long long long

using namespace std;

struct item {
    long d, sum;
    int prio, sz;
    item *l, *r;
    item(long d) : d(d), sum(d), prio(rand()), sz(1), l(NULL), r(NULL) {}
};

typedef item *pitem;

int sz(pitem t) { return t ? t->sz : 0; }
long sum(pitem t) { return t ? t->sum : 0; }
void updt(pitem t) {
    if (!t)
        return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->sum = sum(t->l) + t->d + sum(t->r);
}

void split(pitem t, pitem &l, pitem &r, long key) {
    if (!t)
        return void(l = r = NULL);
    if (t->d <= key)
        split(t->r, t->r, r, key), l = t;
    else
        split(t->l, l, t->l, key), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r)
        return void(t = l ? l : r);
    if (l->prio < r->prio)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    updt(t);
}

const int N = 1e5 + 5;

int n, q, w, h;
pitem t[N];

void update(int x, int k) {
    for (int i = x; i <= w; i += i & -i) {
        pitem r;
        split(t[i], t[i], r, k);
        merge(t[i], t[i], new item(k));
        merge(t[i], t[i], r);
    }
}

long query(int x, int low, int high) {
    long ret = 0;
    for (int i = x; i; i -= i & -i) {
        pitem l, r;
        split(t[i], t[i], r, high);
        split(t[i], l, t[i], low);
        ret += sum(t[i]) - 1ll * low * sz(t[i]);
        ret += 1ll * sz(r) * (high - low);
        merge(t[i], l, t[i]);
        merge(t[i], t[i], r);
    }
    return ret;
}

int main() {
    scanf("%d %d %d %d", &n, &q, &w, &h);
    q += n, ++w, ++h;
    for (int i = 1; i <= q; i++) {
        int T, a, b, c, d;
        scanf("%d %d %d", &T, &a, &b);
        ++a;
        if (T == 1)
            update(a, b);
        else {
            scanf("%d %d", &c, &d);
            ++c;
            printf("%lld\n", query(c, b, d) - query(a - 1, b, d));
        }
    }

    return 0;
}