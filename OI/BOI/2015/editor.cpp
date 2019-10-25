#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

struct node {
    int val;
    node *l, *r;
    node(int val, node *l, node *r) : val(val), l(l), r(r) {}
};

node* newleaf(int val) { return new node(val, NULL, NULL); }
node* newpar(node *l, node *r) { return new node(min(l->val, r->val), l, r); }

int n, ans[N];
node* t[N];

node* build(int l = 1, int r = n) {
    if(l == r) return newleaf(N);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid+1, r));
}

node* update(int x, int k, node *p, int l = 1, int r = n) {
    if(x < l || r < x) return p;
    if(l == r) return newleaf(k);
    int mid = (l + r) >> 1;
    return newpar(update(x, k, p->l, l, mid), update(x, k, p->r, mid+1, r));
}

int find(int x, node *p, int l = 1, int r = n) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(p->r->val < x) return find(x, p->r, mid+1, r);
    else return find(x, p->l, l, mid);
}

int main() {
    scanf("%d", &n);
    t[0] = build();
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if(a > 0) {
            ans[i] = a;
            t[i] = update(i, 0, t[i-1]); 
        } else {
            int pre = find(-a, t[i-1]) - 1;
            ans[i] = ans[pre];
            t[i] = update(i, -a, t[pre]);
        }
        printf("%d\n", ans[i]);
    }

    return 0;
}