#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 17;

struct node {
    int l, r, lz;
    int up, dw;
    node() : l(0), r(0), lz(0), up(0), dw(0) {}
    node(int l, int r, int up, int dw) : l(l), r(r), up(up), dw(dw) {}
    friend node operator+(const node &a, const node &b) {
        if (a.l == -1)
            return b;
        else if (b.l == -1)
            return a;
        node ret;
        ret.l = a.l, ret.r = b.r;
        ret.up = a.up + b.up;
        ret.dw = a.dw + b.dw;
        if (a.r < b.l)
            ret.up++;
        else if (a.r > b.l)
            ret.dw++;
        return ret;
    }
};

int n, m;
node tree[N << 1];

void push(int p, int l, int r) {
    if (tree[p].lz) {
        tree[p].l += tree[p].lz, tree[p].r += tree[p].lz;
        if (l != r) {
            tree[p << 1].lz += tree[p].lz;
            tree[p << 1 | 1].lz += tree[p].lz;
        }
        tree[p].lz = 0;
    }
}

void update(int x, int y, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        tree[p].lz++;
        return push(p, l, r);
    }
    int mid = (l + r) >> 1;
    update(x, y, p << 1, l, mid);
    update(x, y, p << 1 | 1, mid + 1, r);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

node query(int x, int y, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (x > r || l > y)
        return node(-1, -1, 0, 0);
    if (x <= l && r <= y)
        return tree[p];
    int mid = (l + r) >> 1;
    return query(x, y, p << 1, l, mid) + query(x, y, p << 1 | 1, mid + 1, r);
}

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int t, a, b;
        scanf("%d", &t);
        if (t == 1)
            scanf("%d%d", &a, &b), update(a, b);
        if (t == 2) {
            scanf("%d%d", &a, &b);
            node ans = query(a, b);
            printf("%d %d\n", ans.l, ans.r);
        }
        if (t == 3) {
            scanf("%d%d", &a, &b);
            node ans = query(a, b);
            printf("%d %d %d %d\n", ans.l, ans.r, ans.up, ans.dw);
        }
    }

    return 0;
}