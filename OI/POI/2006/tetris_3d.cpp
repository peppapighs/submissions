#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 10;

int D, S, n;

struct SegmentTree {
    int t[N << 1], lz[N << 1];

    void build(int p = 1, int l = 0, int r = S) {
        t[p] = lz[p] = 0;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        t[p] = max(t[p << 1], t[p << 1 | 1]);
    }

    void push(int p, int l, int r) {
        t[p] = max(t[p], lz[p]);
        if (l != r) {
            lz[p << 1] = max(lz[p << 1], lz[p]);
            lz[p << 1 | 1] = max(lz[p << 1 | 1], lz[p]);
        }
        lz[p] = 0;
    }

    void update(int x, int y, int k, int p = 1, int l = 0, int r = S) {
        push(p, l, r);
        if (x > r || l > y)
            return;
        if (x <= l && r <= y) {
            lz[p] = max(lz[p], k), push(p, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        update(x, y, k, p << 1, l, mid),
            update(x, y, k, p << 1 | 1, mid + 1, r);
        t[p] = max(t[p << 1], t[p << 1 | 1]);
    }

    int query(int x, int y, int p = 1, int l = 0, int r = S) {
        push(p, l, r);
        if (x <= l && r <= y)
            return t[p];
        int mid = (l + r) >> 1;
        if (y <= mid)
            return query(x, y, p << 1, l, mid);
        else if (mid + 1 <= x)
            return query(x, y, p << 1 | 1, mid + 1, r);
        return max(query(x, y, p << 1, l, mid),
                   query(x, y, p << 1 | 1, mid + 1, r));
    }
};

struct SegmentTree2d {
    SegmentTree t[N << 1], lz[N << 1];

    void build(int p = 1, int l = 0, int r = D) {
        t[p].build(), lz[p].build();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    }

    void update(int x1, int y1, int x2, int y2, int k, int p = 1, int l = 0,
                int r = D) {
        t[p].update(x2, y2, k);
        if (x1 == l && r == y1) {
            lz[p].update(x2, y2, k);
            return;
        }
        int mid = (l + r) >> 1;
        if (y1 <= mid)
            update(x1, y1, x2, y2, k, p << 1, l, mid);
        else if (mid + 1 <= x1)
            update(x1, y1, x2, y2, k, p << 1 | 1, mid + 1, r);
        else {
            update(x1, mid, x2, y2, k, p << 1, l, mid);
            update(mid + 1, y1, x2, y2, k, p << 1 | 1, mid + 1, r);
        }
    }

    int query(int x1, int y1, int x2, int y2, int p = 1, int l = 0, int r = D) {
        int ret = lz[p].query(x2, y2);
        if (x1 == l && r == y1)
            return max(ret, t[p].query(x2, y2));
        int mid = (l + r) >> 1;
        if (y1 <= mid)
            ret = max(ret, query(x1, y1, x2, y2, p << 1, l, mid));
        else if (mid + 1 <= x1)
            ret = max(ret, query(x1, y1, x2, y2, p << 1 | 1, mid + 1, r));
        else {
            ret = max(ret, query(x1, mid, x2, y2, p << 1, l, mid));
            ret = max(ret, query(mid + 1, y1, x2, y2, p << 1 | 1, mid + 1, r));
        }
        return ret;
    }
} T;

int main() {
    scanf("%d %d %d", &D, &S, &n);
    T.build();
    for (int i = 1, d, s, w, x, y; i <= n; i++) {
        scanf("%d %d %d %d %d", &d, &s, &w, &x, &y);
        int now = T.query(x + 1, x + d, y + 1, y + s);
        T.update(x + 1, x + d, y + 1, y + s, now + w);
    }
    printf("%d\n", T.query(0, D, 0, S));

    return 0;
}