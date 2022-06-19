#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

struct item {
    int val, sz, prio;
    item *l, *r;

    item(int val) : val(val), sz(1), prio(rand()), l(NULL), r(NULL) {}
};

using pitem = item *;

int sz(pitem t) { return t ? t->sz : 0; }

void update(pitem t) {
    if (t)
        t->sz = sz(t->l) + 1 + sz(t->r);
}

void split(pitem t, pitem &l, pitem &r, int key) {
    if (!t)
        return void(l = r = NULL);
    if (t->val <= key)
        split(t->r, t->r, r, key), l = t;
    else
        split(t->l, l, t->l, key), r = t;
    update(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r)
        return void(t = l ? l : r);
    if (l->prio < r->prio)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    update(t);
}

int order(pitem t, int key, int add = 0) {
    if (!t)
        return 0;
    if (t->val == key)
        return add + sz(t->l) + 1;
    else if (t->val < key)
        return order(t->r, key, add + sz(t->l) + 1);
    else
        return order(t->l, key, add);
}

int n, pos;
int A[N];
pitem t;
long ans;

int main() {
    scanf("%d", &n);
    ans = n, pos = 1;
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        A[a] = i;
        merge(t, t, new item(i));
    }
    for (int i = 1; i <= n; i++) {
        int rank = order(t, A[i]);
        ans += min(abs(pos - rank), sz(t) - abs(pos - rank));
        pitem l, r;
        split(t, l, t, A[i] - 1), split(t, t, r, A[i]);
        pos = r ? sz(l) + 1 : 1;
        merge(t, l, r);
    }
    printf("%lld\n", ans);

    return 0;
}