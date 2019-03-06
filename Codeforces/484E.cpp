#include <bits/stdc++.h>

using namespace std;

struct node {
    int l, r;
    int p, s, m, f;
    node() { }
    node(int l, int r, int p, int s, int m, int f) : l(l), r(r), p(p), s(s), m(m), f(f) { }
    friend node operator+(const node &a, const node &b) {
        node ret;
        ret.p = max(a.p, a.f ? a.p + b.p : 0);
        ret.s = max(b.s, b.f ? b.s + a.s : 0);
        ret.m = max({a.m, b.m, a.s + b.p});
        ret.f = a.f & b.f;
        return ret;
    }
};

const int N = 1e5+5;

int n, q, ptr;
int h[N], ver[N], pos[N];
node t[N * 20];

int build(int p, int l = 1, int r = n) {
    if(l == r) return p;
    int mid = (l + r) >> 1;
    t[p].l = build(++ptr, l, mid), t[p].r = build(++ptr, mid+1, r);
    return p;
}

int update(int x, int p, int l = 1, int r = n) {
    t[++ptr] = t[p];
    p = ptr;
    if(l == r) {
        t[p] = node(0, 0, 1, 1, 1, 1);
        return p;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) t[p].l = update(x, t[p].l, l, mid);
    else t[p].r = update(x, t[p].r, mid+1, r);
    node now = t[t[p].l] + t[t[p].r];
    t[p].p = now.p, t[p].s = now.s, t[p].m = now.m, t[p].f = now.f;
    return p;
}

node query(int x, int y, int p, int l = 1, int r = n) {
    if(x > r || l > y) return node(0, 0, 0, 0, 0, 0);
    if(x <= l && r <= y) return t[p];
    int mid = (l + r) >> 1;
    return query(x, y, t[p].l, l, mid) + query(x, y, t[p].r, mid+1, r);
}

int main() {
    iota(pos, pos+N, 0);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", h+i);
    sort(pos+1, pos+n+1, [&](const int &a, const int &b) {
        return h[a] > h[b];
    });
    ver[0] = build(++ptr);
    for(int i = 1; i <= n; i++) ver[i] = update(pos[i], ver[i-1]);;
    scanf("%d", &q);
    for(int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        int l = 1, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(query(a, b, ver[mid]).m >= c) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", h[pos[r]]);
    }

    return 0;
}
