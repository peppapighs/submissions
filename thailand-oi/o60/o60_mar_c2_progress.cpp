#include <bits/stdc++.h>

using namespace std;

const int N = 1<<17;

struct node {
    int pre, suf, sum, mx;
    node() { };
    node(int pre, int suf, int sum, int mx) : pre(pre), suf(suf), sum(sum), mx(mx) { }
    friend node operator+(const node &a, const node &b) {
        node ret;
        ret.pre = max(a.pre, a.sum + b.pre);
        ret.suf = max(b.suf, b.sum + a.suf);
        ret.sum = a.sum + b.sum;
        ret.mx = max({a.mx, b.mx, a.suf + b.pre});
        return ret;
    }
};

int n, m, A[N];
node t[N<<1];

void build(int p = 1, int l = 1, int r = n) {
    if(l == r) return void(t[p] = node(A[l], A[l], A[l], A[l]));
    int mid = (l + r) >> 1;
    build(p<<1, l, mid), build(p<<1|1, mid+1, r);
    t[p] = t[p<<1] + t[p<<1|1];
}

void update(int x, int k, int p = 1, int l = 1, int r = n) {
    if(l == r) return void(t[p] = node(k, k, k, k));
    int mid = (l + r) >> 1;
    if(x <= mid) update(x, k, p<<1, l, mid);
    else update(x, k, p<<1|1, mid+1, r);
    t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    build();
    printf("%d\n", t[1].mx);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        ++a;
        update(a, b);
        printf("%d\n", t[1].mx);
    }

    return 0;
}
