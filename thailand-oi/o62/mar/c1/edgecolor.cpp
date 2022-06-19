#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

struct item {
    bool tag;
    int d, lz, sz, prio;
    item *l, *r, *p;
    item(int d)
        : tag(false), d(d), lz(0), sz(1), prio(rand()), l(NULL), r(NULL),
          p(NULL) {}
};

typedef item *pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) {
    if (!t)
        return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    if (t->l)
        t->l->p = t;
    if (t->r)
        t->r->p = t;
}
void push(pitem t) {
    if (!t || !t->lz)
        return;
    swap(t->l, t->r);
    if (t->l)
        t->l->lz ^= 1;
    if (t->r)
        t->r->lz ^= 1;
    t->lz = 0;
}

void split(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
    push(t);
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
    push(l), push(r);
    if (!l || !r)
        return void(t = l ? l : r);
    if (l->prio < r->prio)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    updt(t);
}

pitem root(pitem t) {
    while (t->p)
        t = t->p;
    return t;
}

int getpos(pitem t) {
    vector<bool> vec;
    while (t->p) {
        if (t->p->l == t)
            vec.emplace_back(0);
        else
            vec.emplace_back(1);
        t = t->p;
    }
    int add = 0;
    for (int i = vec.size() - 1; ~i; i--) {
        if (t->lz)
            push(t), vec[i] = !vec[i];
        if (!vec[i])
            t = t->l;
        else
            add += sz(t->l) + 1, t = t->r;
    }
    push(t);
    return add + sz(t->l) + 1;
}

const int N = 3e5 + 5;

int n, m, cnt;
pitem t[N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        t[i] = new item(i);
    for (int i = 1, T, a, b; i <= m; i++) {
        scanf("%d %d %d", &T, &a, &b);
        pitem tmp, l, r;
        if (T == 1) {
            if (root(t[a]) != root(t[b])) {
                if (getpos(t[a]) == 1)
                    root(t[a])->lz ^= 1;
                if (getpos(t[b]) == sz(root(t[b])))
                    root(t[b])->lz ^= 1;
                merge(tmp, root(t[a]), root(t[b]));
                tmp->p = NULL;
            } else {
                root(t[a])->tag = true;
                if (sz(root(t[a])) & 1)
                    ++cnt;
            }
        } else {
            int pa = getpos(t[a]), pb = getpos(t[b]), size = sz(root(t[a]));
            bool rot = root(t[a])->tag;
            if (pa > pb)
                swap(pa, pb);
            if (rot) {
                if (size & 1)
                    --cnt;
                root(t[a])->tag = false;
                if (pa != 1 || pb != sz(root(t[a]))) {
                    split(root(t[a]), l, r, pa);
                    l->p = r->p = NULL;
                    tmp = root(t[a]);
                    merge(tmp, r, l);
                    tmp->p = NULL;
                }
            } else {
                split(root(t[a]), l, r, pa);
                l->p = r->p = NULL;
            }
        }
        if (cnt)
            printf("no\n");
        else
            printf("yes\n");
    }

    return 0;
}
