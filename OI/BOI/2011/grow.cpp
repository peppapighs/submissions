#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct item {
    int d, lz, sz, prio;
    item *l, *r;
    item(int d) : d(d), lz(0), sz(1), prio(rand()), l(NULL), r(NULL) {}
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }

void updt(pitem t) { if(t) t->sz = sz(t->l) + 1 + sz(t->r); }

void push(pitem t) {
    if(!t || !t->lz) return;
    t->d += t->lz;
    if(t->l) t->l->lz += t->lz;
    if(t->r) t->r->lz += t->lz;
    t->lz = 0;
}

void split_val(pitem t, pitem &l, pitem &r, int key) {
    push(t);
    if(!t) return void(l = r = NULL);
    if(t->d <= key) split_val(t->r, t->r, r, key), l = t;
    else split_val(t->l, l, t->l, key), r = t;
    updt(t);
}

void split_idx(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
    push(t);
    if(!t) return void(l = r = NULL);
    int cur_pos = add + sz(t->l) + 1;
    if(cur_pos <= pos) split_idx(t->r, t->r, r, pos, cur_pos), l = t;
    else split_idx(t->l, l, t->l, pos, add), r = t;
    updt(t); 
}

void merge(pitem &t, pitem l, pitem r) {
    push(l), push(r);
    if(!l || !r) return void(t = l ? l : r);
    if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updt(t);
}

int get_left(pitem t) {
    push(t);
    if(!t->l) return t->d;
    return get_left(t->l);
}

int get_right(pitem t) {
    push(t);
    if(!t->r) return t->d;
    return get_right(t->r);
}

int n, m, A[N];
pitem t;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);

    sort(A + 1, A + n + 1);
    for(int i = 1; i <= n; i++) merge(t, t, new item(A[i]));

    for(int i = 1; i <= m; i++) {
        char T; int a, b;
        scanf(" %c %d %d", &T, &a, &b);
        if(T == 'F') {
            pitem l, r1, r2, r3;
            split_val(t, l, t, b - 1), split_idx(t, t, r1, a);
            if(t) {
                ++t->lz;
                if(r1) {
                    int R = get_right(t), L = get_left(r1);
                    if(R > L) {
                        split_val(t, t, r2, R - 1), split_val(r1, r3, r1, L);
                        merge(t, t, r3), merge(r1, r2, r1);
                    }
                }
            }
            merge(t, l, t), merge(t, t, r1);
        } else {
            pitem l, r;
            split_val(t, l, t, a - 1), split_val(t, t, r, b);
            printf("%d\n", sz(t));
            merge(t, l, t), merge(t, t, r);
        }
    }

    return 0;
}