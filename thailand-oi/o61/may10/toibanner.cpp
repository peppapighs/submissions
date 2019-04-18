#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int INF = 1e9+1;

struct item {
    int x, k, sz, prio;
    vector<int> v; //Left-Right Bitmask 1 = Used, 0 = Vacant
    item *l, *r;
    item(int x, int k) : x(x), k(k), sz(1), prio(rand()), l(NULL), r(NULL) {
        v = vector<int>(4, INF);
        v[0] = 0, v[3] = k;
    }
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) {
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->v = vector<int>(4, INF);
    t->v[0] = 0, t->v[3] = t->k;
    vector<int> vec(4, INF);
    if(t->l) {
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) {
            if((i & 1) && (j & 2)) continue;
            int bit = (i & 2) + (j & 1);
            bool a = ((i & 1) == (i >> 1 & 1)) ^ (sz(t->l) & 1);
            bool b = ((j & 1) == (j >> 1 & 1)) ^ 1;
            if(a && b) continue;
            if(!(i & 1) && !(j & 2) && (a || b)) continue;
            vec[bit] = min(vec[bit], t->l->v[i] + t->v[j]);
        }
        for(int i = 0; i < 4; i++) t->v[i] = vec[i], vec[i] = INF;
    }
    if(t->r) {
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) {
            if((i & 1) && (j & 2)) continue;
            int bit = (i & 2) + (j & 1);
            bool a = ((i & 1) == (i >> 1 & 1)) ^ ((sz(t->l) + 1) & 1);
            bool b = ((j & 1) == (j >> 1 & 1)) ^ (sz(t->r) & 1);
            if(a && b) continue;
            if(!(i & 1) && !(j & 2) && (a || b)) continue;
            vec[bit] = min(vec[bit], t->v[i] + t->r->v[j]);
        }
        for(int i = 0; i < 4; i++) t->v[i] = vec[i], vec[i] = INF;
    }
}

void split(pitem t, pitem &l, pitem &r, int key) {
    if(!t) return void(l = r = NULL);
    if(t->x <= key) split(t->r, t->r, r, key), l = t;
    else split(t->l, l, t->l, key), r = t;
    updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if(!l || !r) return void(t = l ? l : r);
    if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updt(t);
}

int n, A[N];
pitem t;
set<int> S;

void add(int x) {
    auto it = S.lower_bound(x);
    if(it != S.begin() && it != S.end()) {
        pitem m, r;
        auto it1 = prev(it);
        split(t, t, r, *it1), split(t, t, m, *it1 - 1);
        merge(t, t, new item(*it1, A[x] - A[*it1]));
        merge(t, t, new item(x, A[*it] - A[x]));
        merge(t, t, r);
    } else if(it == S.begin()) merge(t, new item(x, A[*it] - A[x]), t);
    else --it, merge(t, t, new item(*it, A[x] - A[*it]));
    S.emplace(x);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    int tmp;
    scanf("%d", &tmp), S.emplace(tmp);
    for(int i = 1, a, b; i <= n / 2; i++) {
        scanf("%d %d", &a, &b);
        add(a), add(b);
        printf("%d\n", min({t->v[1], t->v[2], t->v[3]}));
    }

    return 0;
}