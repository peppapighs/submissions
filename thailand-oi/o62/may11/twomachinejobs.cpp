#include <bits/stdc++.h>

#define long long long

using namespace std;

struct item {
    long a, b, sum;
    long val, mx, lz;
    int prio;
    item *l, *r;
    item(long a, long b, long val) : a(a), b(b), sum(a), val(val), mx(val), lz(0), prio(rand()), l(NULL), r(NULL) { }
};

typedef item* pitem;

long sum(pitem t) { return t ? t->sum : 0; }
long mx(pitem t) { return t ? t->mx : 0; }

void push(pitem t) {
    if(!t || !t->lz) return;
    t->val += t->lz;
    t->mx += t->lz;
    if(t->l) t->l->lz += t->lz;
    if(t->r) t->r->lz += t->lz;
    t->lz = 0;
}

void updt(pitem t) {
    if(!t) return;
    push(t);
    if(t->l) push(t->l);
    if(t->r) push(t->r);
    t->sum = sum(t->l) + t->a + sum(t->r);
    t->mx = max({mx(t->l), t->val, mx(t->r)});
}

void split(pitem t, pitem &l, pitem &r, long key) {
    push(t);
    if(!t) return void(l = r = NULL);
    if(t->b >= key) split(t->r, t->r, r, key), l = t;
    else split(t->l, l, t->l, key), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    push(l), push(r);
    if(!l || !r) return void(t = l ? l : r);
    if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updt(t);
}

int n, T, M1, M2;
pitem t;

int main() {
    scanf("%d %d %d %d", &n, &T, &M1, &M2);
    long ans = 0;
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        if(T == 2) a += (ans % M1), b += (ans % M2);
        pitem r;
        split(t, t, r, b);
        long sm = sum(t);
        merge(t, t, new item(a, b, sm + a + b));
        if(r) r->lz += a;
        merge(t, t, r);
        printf("%lld\n", ans = t->mx);
    }

    return 0;
}