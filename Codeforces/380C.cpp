#include <bits/stdc++.h>

using namespace std;

struct node {
    int ob, cb, mx;
    node() : ob(0), cb(0), mx(0) {}
    node(int ob, int cb, int mx) : ob(ob), cb(cb), mx(mx) {}
    friend node operator+(const node &lhs, const node &rhs) {
        node ret;
        int t = min(lhs.ob, rhs.cb);
        ret.ob = lhs.ob + rhs.ob - t;
        ret.cb = lhs.cb + rhs.cb - t;
        ret.mx = lhs.mx + rhs.mx + t;
        return ret;
    }
};

const int N = 1 << 20;

node tree[N << 1];

string str;
int n, m;

void build(int rt = 1, int l = 1, int r = n) {
    if (l == r) {
        if (str[l - 1] == '(')
            tree[rt] = node(1, 0, 0);
        else
            tree[rt] = node(0, 1, 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

node query(int x, int y, int rt = 1, int l = 1, int r = n) {
    if (x > r || l > y)
        return node();
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return query(x, y, rt << 1, l, mid) + query(x, y, rt << 1 | 1, mid + 1, r);
}

int main() {
    cin >> str;
    n = str.length();
    build();
    scanf("%d", &m);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r).mx * 2);
    }

    return 0;
}