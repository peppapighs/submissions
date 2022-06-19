#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

struct item {
    int x, id, mx, prio;
    item *l, *r;
    item(int x, int id)
        : x(x), id(id), mx(id), prio(rand()), l(NULL), r(NULL) {}
};

typedef item *pitem;

int mx(pitem t) { return t ? t->mx : 0; }
void updt(pitem t) {
    if (t)
        t->mx = max({mx(t->l), t->id, mx(t->r)});
}

void split(pitem t, pitem &l, pitem &r, int key) {
    if (!t)
        return void(l = r = NULL);
    if (t->x <= key)
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

const int N = 1e5 + 5;

int n, dp[N], pos[N];
int x1[N], x2[N], y[N];
vector<int> coord;
pitem t[N];

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

void update(int x, int a, int b) {
    for (int i = x; i <= (int)coord.size(); i += i & -i) {
        pitem r;
        split(t[i], t[i], r, a);
        merge(t[i], t[i], new item(a, b));
        merge(t[i], t[i], r);
    }
}

int query(int x, int r) {
    int ret = 0;
    if (!x)
        return 0;
    for (int i = x; i; i -= i & -i) {
        pitem l;
        split(t[i], l, t[i], r);
        ret = max(ret, mx(t[i]));
        merge(t[i], l, t[i]);
    }
    return ret;
}

int main() {
    iota(pos, pos + N, 0);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", x1 + i, x2 + i, y + i);
        coord.emplace_back(x1[i]);
    }
    sort(pos + 1, pos + n + 1,
         [&](const int &a, const int &b) { return y[a] < y[b]; });
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (int i = 1; i <= n; i++) {
        int now = query(get(x2[pos[i]]) - 1, x2[pos[i]]);
        dp[pos[i]] = dp[pos[now]] + 1;
        update(get(x1[pos[i]]), x2[pos[i]], i);
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", dp[i]);

    return 0;
}