#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

long iden = 98765431, hpow[N];

struct item {
    long d, hsh1, hsh2;
    int lz, prio, sz;
    item *l, *r;
    item(long d) : d(d), hsh1(d), hsh2(d), lz(0), prio(rand()), sz(1), l(NULL), r(NULL) { }
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }
long hsh1(pitem t) { return t ? t->hsh1 : 0; }
long hsh2(pitem t) { return t ? t->hsh2 : 0; }
void updt(pitem t) {
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->hsh1 = hsh1(t->l) * hpow[1 + sz(t->r)] + t->d * hpow[sz(t->r)] + hsh1(t->r);
    t->hsh2 = hsh2(t->r) * hpow[1 + sz(t->l)] + t->d * hpow[sz(t->l)] + hsh2(t->l);
}

void push(pitem t) {
    if(!t || !t->lz) return;
    swap(t->l, t->r);
    if(t->l) t->l->lz ^= 1, swap(t->l->hsh1, t->l->hsh2);
    if(t->r) t->r->lz ^= 1, swap(t->r->hsh1, t->r->hsh2);
    t->lz = 0;
}

void split(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
    push(t);
    if(!t) return void(l = r = NULL);
    int cur_pos = add + sz(t->l) + 1;
    if(cur_pos <= pos) split(t->r, t->r, r, pos, cur_pos), l = t;
    else split(t->l, l, t->l, pos, add), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    push(l), push(r);
    if(!l || !r) return void(t = l ? l : r);
    if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updt(t);
}

int n, q;
char S[N];
pitem t;

int main() {
    hpow[0] = 1;
    for(int i = 1; i < N; i++) hpow[i] = hpow[i-1] * iden;
    scanf("%d %d %s", &n, &q, S+1);
    for(int i = 1; i <= n; i++) merge(t, t, new item(S[i]));
    for(int i = 1; i <= q; i++) {
        char T;
        int a, b, c, d;
        scanf(" %c %d %d", &T, &a, &b);
        if(T == 'Q') {
            pitem l, r;
            split(t, t, r, b), split(t, l, t, a-1);
            if(t->hsh1 == t->hsh2) printf("YES\n");
            else printf("NO\n");
            merge(t, l, t), merge(t, t, r);
        } else {
            if(a == 1) {
                scanf("%d %d", &c, &d);
                pitem m, r;
                split(t, t, r, c), split(t, t, m, b-1);
                merge(t, t, r), split(t, t, r, d);
                merge(t, t, m), merge(t, t, r);
            } else if(a == 2) {
                scanf("%d", &c);
                pitem l, r;
                split(t, t, r, c), split(t, l, t, b-1);
                t->lz ^= 1;
                merge(t, l, t), merge(t, t, r);
            } else {
                scanf(" %c", &T);
                pitem r;
                split(t, t, r, b-1);
                merge(t, t, new item(T)), merge(t, t, r);
            }
        }
    } 

    return 0;
}