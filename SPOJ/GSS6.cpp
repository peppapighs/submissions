#include <bits/stdc++.h>

using namespace std;

struct data {
    int pre, suf, sum, mx;
    data() {}
    data(int d) : pre(d), suf(d), sum(d), mx(d) {}
    data(int pre, int suf, int sum, int mx)
        : pre(pre), suf(suf), sum(sum), mx(mx) {}
    friend data operator+(const data &a, const data &b) {
        data ret;
        ret.pre = max(a.pre, a.sum + b.pre);
        ret.suf = max(b.suf, b.sum + a.suf);
        ret.sum = a.sum + b.sum;
        ret.mx = max({a.mx, b.mx, a.suf + b.pre});
        return ret;
    }
};

struct item {
    data d, sum;
    int prio, sz;
    item *l, *r;
    item(data d) : d(d), sum(d), prio(rand()), sz(1), l(NULL), r(NULL) {}
};

typedef item *pitem;

int sz(pitem t) { return t ? t->sz : 0; }
data sum(pitem t) { return t ? t->sum : data(-1e9, -1e9, 0, -1e9); }
void updt(pitem t) {
    if (!t)
        return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->sum = sum(t->l) + t->d + sum(t->r);
}

void split(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
    if (!t)
        return void(l = r = NULL);
    int cur_pos = add + sz(t->l) + 1;
    if (cur_pos <= pos)
        split(t->r, t->r, r, pos, cur_pos), l = t;
    else
        split(t->l, l, t->l, pos, add), r = t;
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
}

int n, q;
pitem t;

int main() {
    scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        merge(t, t, new item(data(a)));
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        char T;
        int a, b;
        scanf(" %c %d", &T, &a);
        if (T == 'I') {
            scanf("%d", &b);
            pitem r;
            split(t, t, r, a - 1);
            merge(t, t, new item(data(b)));
            merge(t, t, r);
        } else if (T == 'D') {
            pitem m, r;
            split(t, t, r, a);
            split(t, t, m, a - 1);
            merge(t, t, r);
        } else if (T == 'R') {
            scanf("%d", &b);
            pitem m, r;
            split(t, t, r, a);
            split(t, t, m, a - 1);
            merge(t, t, new item(data(b)));
            merge(t, t, r);
        } else {
            scanf("%d", &b);
            pitem l, r;
            split(t, t, r, b);
            split(t, l, t, a - 1);
            printf("%d\n", t->sum.mx);
            merge(t, t, r);
            merge(t, l, t);
        }
    }

    return 0;
}