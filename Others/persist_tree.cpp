#include <bits/stdc++.h>
#define long long long
using namespace std;

struct item {
    int v;
    item *l, *r;
    item() { }
    item(int v, item *l, item *r) : v(v), l(l), r(r) { }
};

const int N = 1e3+5;

int n, m, q, pref[100005];
item* ver[N];

item* newleaf(int v) {
    return new item(v, nullptr, nullptr);
}

item* newpar(item *l, item *r) {
    return new item(l->v + r->v, l, r);
}

item* build(int l = 1, int r = n) {
    if(l == r) return newleaf(0);
    int m = l + r >> 1;
    return newpar(build(l, m), build(m+1, r));
}

item* update(int x, int v, item *p, int l = 1, int r = n) {
    if(l == r) return newleaf(p->v + v);
    int m = l + r >> 1;
    if(x <= m) return newpar(update(x, v, p->l, l, m), p->r);
    else return newpar(p->l, update(x, v, p->r, m+1, r));
}

int query(int x, int y, item *p, int l = 1, int r = n) {
    if(x > r || l > y) return 0;
    if(x <= l && r <= y) return p->v;
    int m = l + r >> 1;
    return query(x, y, p->l, l, m) + query(x, y, p->r, m+1, r); 
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", pref+i), pref[i] += pref[i-1];
    ver[0] = build(); 
    for(int i = 1, a, b; i <= m; ++i) {
        scanf("%d %d", &a, &b);
        ver[i] = update(a, b, ver[i-1]);
    }
    int k = 0; m++;
    for(int i = 0, a, b; i < q; ++i) {
        scanf("%d %d", &a, &b);
        int ans =  pref[b] - pref[a-1] + query(a, b, ver[k]);
        printf("%d\n", ans);
        k = (ans % m + m) % m;
    } 
}