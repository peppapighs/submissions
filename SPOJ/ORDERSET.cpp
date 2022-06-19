#include <bits/stdc++.h>

using namespace std;

struct item {
    int val, prior, size;
    item *l, *r;
    item(int val) : val(val), prior(rand()), size(1), l(NULL), r(NULL) {}
};

typedef item *pitem;

int sz(pitem t) { return t ? t->size : 0; }
void updt(pitem t) {
    if (t)
        t->size = sz(t->l) + 1 + sz(t->r);
}

void split(pitem t, pitem &l, pitem &r, int key) {
    if (!t)
        return void(l = r = NULL);
    if (t->val <= key)
        split(t->r, t->r, r, key), l = t;
    else
        split(t->l, l, t->l, key), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    updt(t);
}

bool find(pitem t, int key) {
    if (!t)
        return false;
    else if (t->val == key)
        return true;
    else if (t->val < key)
        return find(t->r, key);
    else
        return find(t->l, key);
}

void print(pitem t) {
    if (!t)
        return;
    print(t->l);
    printf("%d ", t->val);
    print(t->r);
}

int kth(pitem t, int x, int add = 0) {
    if (!t)
        return -1;
    int cur_pos = add + sz(t->l) + 1;
    if (cur_pos == x)
        return t->val;
    else if (cur_pos < x)
        return kth(t->r, x, cur_pos);
    else
        return kth(t->l, x, add);
}

int count(pitem t, int x) {
    if (!t)
        return 0;
    if (t->val < x)
        return count(t->r, x) + sz(t->l) + 1;
    else
        return count(t->l, x);
}

pitem t;

int q;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> q;
    while (q--) {
        char T;
        int x;
        cin >> T >> x;
        if (T == 'I' && !find(t, x)) {
            pitem r;
            split(t, t, r, x);
            merge(t, t, new item(x));
            merge(t, t, r);
        } else if (T == 'D' && find(t, x)) {
            pitem tmp, r;
            split(t, t, r, x);
            split(t, t, tmp, x - 1);
            free(tmp);
            merge(t, t, r);
        } else if (T == 'K') {
            if (x > sz(t)) {
                printf("invalid\n");
                continue;
            }
            printf("%d\n", kth(t, x));
        } else if (T == 'C')
            printf("%d\n", count(t, x));
    }

    return 0;
}