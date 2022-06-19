#include <bits/stdc++.h>

using namespace std;

struct node {
    int n4, n7, n47, n74;
    node() : n4(0), n7(0), n47(0), n74(0) {}
    node(int n4, int n7, int n47, int n74)
        : n4(n4), n7(n7), n47(n47), n74(n74) {}
    void swp() {
        swap(n4, n7);
        swap(n47, n74);
    }
    friend node operator+(const node &lhs, const node &rhs) {
        node ret;
        ret.n4 = lhs.n4 + rhs.n4;
        ret.n7 = lhs.n7 + rhs.n7;
        ret.n47 = max(lhs.n4 + rhs.n47, max(lhs.n47 + rhs.n7, lhs.n4 + rhs.n7));
        ret.n74 = max(lhs.n7 + rhs.n74, max(lhs.n74 + rhs.n4, lhs.n7 + rhs.n4));
        return ret;
    }
};

const int N = 1 << 20;

node tree[N << 1];
bool lz[N << 1];

int n, m;
string str;

void pushlz(int rt, int l, int r) {
    if (lz[rt]) {
        tree[rt].swp();
        if (l != r) {
            lz[rt << 1] = 1 - lz[rt << 1];
            lz[rt << 1 | 1] = 1 - lz[rt << 1 | 1];
        }
        lz[rt] = false;
    }
}

void build(int rt = 1, int l = 1, int r = n) {
    if (l == r) {
        if (str[l - 1] == '4')
            tree[rt] = node(1, 0, 1, 1);
        else
            tree[rt] = node(0, 1, 1, 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void update(int x, int y, int rt = 1, int l = 1, int r = n) {
    pushlz(rt, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz[rt] = true;
        pushlz(rt, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(x, y, rt << 1, l, mid);
    update(x, y, rt << 1 | 1, mid + 1, r);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

int main() {
    scanf("%d%d", &n, &m);
    cin >> str;
    build();
    while (m--) {
        string com;
        cin >> com;
        if (com == "switch") {
            int l, r;
            scanf("%d%d", &l, &r);
            update(l, r);
        } else
            printf("%d\n", tree[1].n47);
    }
    return 0;
}