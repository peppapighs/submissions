#include <bits/stdc++.h>

#define long long long

using namespace std;

struct item {
    int cnt[5];
    long inc, inv;
    int val, prio, sz, lz, st;
    item *l, *r;
    item(int val)
        : val(val), l(NULL), r(NULL), inc(0), inv(0), prio(rand()), sz(1),
          lz(0), st(0) {
        memset(cnt, 0, sizeof cnt);
        cnt[val] = 1;
    }
};

typedef item *pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) {
    if (!t)
        return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    memset(t->cnt, 0, sizeof t->cnt);
    t->cnt[t->val] = 1;
    t->inc = t->inv = 0;
    for (int i = 0; i < 5; i++) {
        if (t->l)
            t->cnt[i] += t->l->cnt[i];
        if (t->r)
            t->cnt[i] += t->r->cnt[i];
    }
    if (t->l) {
        t->inc += t->l->inc, t->inv += t->l->inv;
        for (int i = 0; i < t->val; i++)
            t->inc += t->l->cnt[i];
        for (int i = t->val + 1; i < 5; i++)
            t->inv += t->l->cnt[i];
    }
    if (t->r) {
        t->inc += t->r->inc, t->inv += t->r->inv;
        for (int i = 0; i < t->val; i++)
            t->inv += t->r->cnt[i];
        for (int i = t->val + 1; i < 5; i++)
            t->inc += t->r->cnt[i];
    }
    if (t->l && t->r) {
        for (int i = 0; i < 5; i++)
            for (int j = i + 1; j < 5; j++)
                t->inc += (t->l->cnt[i] * t->r->cnt[j]);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < i; j++)
                t->inv += (t->l->cnt[i] * t->r->cnt[j]);
    }
}

void push(pitem t) {
    if (!t || !t->st)
        return;
    if (t->st == 2) {
        t->val = t->lz;
        if (t->l) {
            t->l->st = 2, t->l->lz = t->lz;
            t->l->inc = t->l->inv = 0;
            memset(t->l->cnt, 0, sizeof t->l->cnt);
            t->l->cnt[t->lz] = sz(t->l);
        }
        if (t->r) {
            t->r->st = 2, t->r->lz = t->lz;
            t->r->inc = t->r->inv = 0;
            memset(t->r->cnt, 0, sizeof t->r->cnt);
            t->r->cnt[t->lz] = sz(t->r);
        }
    } else if (t->st == 1) {
        swap(t->l, t->r);
        if (t->l && t->l->st != 2) {
            t->l->st ^= 1;
            swap(t->l->inc, t->l->inv);
        }
        if (t->r && t->r->st != 2) {
            t->r->st ^= 1;
            swap(t->r->inc, t->r->inv);
        }
    }
    t->lz = t->st = 0;
    updt(t);
}

void split(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
    push(t);
    if (!t)
        return void(l = r = NULL);
    int now = add + sz(t->l) + 1;
    if (now <= pos)
        split(t->r, t->r, r, pos, now), l = t;
    else
        split(t->l, l, t->l, pos, add), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    push(l), push(r);
    if (!l || !r)
        return void(t = l ? l : r);
    if (l->prio < r->prio)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    updt(t);
}

const int N = 1e5 + 5;

int n, q;
char A[N];
pitem t;

template <typename T> void proc(int a, int b, const T &f) {
    pitem l, r;
    split(t, l, t, a - 1), split(t, t, r, b - a + 1);
    f(t);
    merge(t, l, t), merge(t, t, r);
}

int main() {
    scanf("%d %d", &n, &q);
    scanf(" %s", A + 1);
    for (int i = 1; i <= n; i++)
        merge(t, t, new item(A[i] - '0'));

    while (q--) {
        int T, a, b, c;
        scanf("%d %d %d", &T, &a, &b);
        if (T == 1) {
            scanf("%d", &c);
            proc(a, b, [&](pitem t) { t->lz = c, t->st = 2; });
        } else if (T == 2)
            proc(a, b, [&](pitem t) {
                if (t->st != 2)
                    t->st ^= 1;
            });
        else
            proc(a, b, [&](pitem t) { printf("%lld\n", t->inv); });
    }

    return 0;
}