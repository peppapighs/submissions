#include <bits/stdc++.h>

#define iii tuple<int, int, int, int>

using namespace std;

struct item {
    int pos, d, sum, prio;
    item *l, *r;
    item(int pos, int d)
        : pos(pos), d(d), sum(d), prio(rand()), l(NULL), r(NULL) {}
};

typedef item *pitem;

int sum(pitem t) { return t ? t->sum : 0; }
void updt(pitem t) {
    if (t)
        t->sum = sum(t->l) + t->d + sum(t->r);
}

void split(pitem t, pitem &l, pitem &r, int key) {
    if (!t)
        return void(l = r = NULL);
    if (t->pos <= key)
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

void print(pitem t) {
    if (!t)
        return;
    print(t->l);
    printf("(%d, %d) ", t->pos, t->d);
    print(t->r);
}

const int N = 2e5 + 5;

int n, l;
vector<int> coord;
vector<iii> Q;
pitem t[N];

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

void update(int x, int pos, int d) {
    for (int i = x; i <= coord.size(); i += i & -i) {
        pitem r;
        split(t[i], t[i], r, pos);
        merge(t[i], t[i], new item(pos, d));
        merge(t[i], t[i], r);
    }
}

int query(int x, int pos) {
    int ret = 0;
    for (int i = x; i; i -= i & -i) {
        pitem r;
        split(t[i], t[i], r, pos);
        ret += sum(t[i]);
        merge(t[i], t[i], r);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 1, T, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &T, &a, &b);
        if (T == 1)
            scanf("%d", &c);
        coord.emplace_back(a - b);
        Q.emplace_back(T, a, b, c);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (iii q : Q) {
        int T, a, b, c;
        tie(T, a, b, c) = q;
        if (T == 1)
            update(get(a - b), a + b, c);
        else
            printf("%d\n", query(get(a - b), a + b));
    }

    return 0;
}