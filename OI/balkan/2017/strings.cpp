#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;
const long iden = 98765431;

long hpow[N];

struct item {
    char c;
    long h1, h2;
    int sz, prio, lz;
    item *l, *r;
    item(char c) : c(c), h1(c), h2(c), sz(1), prio(rand()), lz(0), l(NULL), r(NULL) {}
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }

long h1(pitem t) { return t ? t->h1 : 0; }
long h2(pitem t) { return t ? t->h2 : 0; }

void updt(pitem t) {
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->h1 = hpow[sz(t->r) + 1] * h1(t->l) + hpow[sz(t->r)] * t->c + h1(t->r);
    t->h2 = hpow[sz(t->l) + 1] * h2(t->r) + hpow[sz(t->l)] * t->c + h2(t->l);
}

void push(pitem t) {
    if(!t || !t->lz) return;
    swap(t->l, t->r);
    if(t->l) swap(t->l->h1, t->l->h2), t->l->lz ^= 1;
    if(t->r) swap(t->r->h1, t->r->h2), t->r->lz ^= 1;
    t->lz = 0;
    updt(t);
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

int n, m;
char str[N];
pitem t;

int main() {
    hpow[0] = 1;
    for(int i = 1; i < N; i++) hpow[i] = hpow[i-1] * iden;

    scanf("%d %d %s", &n, &m, str + 1);
    for(int i = 1; i <= n; i++) merge(t, t, new item(str[i]));

    while(m--) {
        char C;
        pitem l, r;
        scanf(" %c", &C);
        if(C == 'Q') {
            int a, b;
            scanf("%d %d", &a, &b);
            
            split(t, t, r, b), split(t, l, t, a-1);
            if(h1(t) == h2(t)) printf("YES\n");
            else printf("NO\n");
            merge(t, t, r), merge(t, l, t);
        } else {
            char x;
            int T, a, b, c;
            scanf("%d", &T);
            if(T == 1) {
                scanf("%d %d %d", &a, &b, &c);

                split(t, t, r, b), split(t, l, t, a-1);
                merge(l, l, r);
                split(l, l, r, c);
                merge(t, t, r), merge(t, l, t);
            } else if(T == 2) {
                scanf("%d %d", &a, &b);

                split(t, t, r, b), split(t, l, t, a-1);
                if(t) t->lz ^= 1;
                merge(t, t, r), merge(t, l, t);
            } else {
                scanf("%d %c", &a, &x);

                split(t, l, t, a-1);
                merge(l, l, new item(x));
                merge(t, l, t);
            }
        }
    }

    return 0;
}