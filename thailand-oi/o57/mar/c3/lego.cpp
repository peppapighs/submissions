#include <bits/stdc++.h>

using namespace std;

struct item {
    int data;
    int sz, prio;
    item *l, *r;
    item(int data) : data(data), sz(1), prio(rand()), l(NULL), r(NULL) {}
};

typedef item *pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) {
    if (t)
        t->sz = sz(t->l) + 1 + sz(t->r);
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

int n, q;
pitem t;

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        merge(t, t, new item(a));
    }
    for (int i = 1; i <= q; i++) {
        int T, a, L, b;
        scanf("%d %d", &T, &a);
        if (T == 1) {
            scanf("%d %d", &L, &b);
            if (b > a) {
                pitem last, l, r;
                split(t, t, last, b - 1);
                split(t, t, r, a + L - 1);
                split(t, l, t, a - 1);
                merge(l, l, r), merge(t, l, t), merge(t, t, last);
            } else {
                pitem front, l, r;
                split(t, t, r, a + L - 1);
                split(t, l, t, a - 1);
                split(l, front, l, b - 1);
                merge(t, front, t), merge(t, t, l), merge(t, t, r);
            }
        } else {
            pitem l, r;
            split(t, t, r, a), split(t, l, t, a - 1);
            printf("%d\n", t->data);
            merge(t, l, t), merge(t, t, r);
        }
    }

    return 0;
}