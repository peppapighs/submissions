#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

struct node {
        int l, r, lz;
        int mx, cnt;
        node() : l(0), r(0), lz(0), mx(0), cnt(1) {}
        node(int l, int r, int lz, int mx, int cnt) : l(l), r(r), lz(0), mx(mx), cnt(cnt) {}
        friend node operator+(const node &a, const node &b) {
                node ret;
                ret.l = a.l, ret.r = b.r;
                if(a.mx == b.mx) ret.mx = a.mx, ret.cnt = a.cnt + b.cnt - (a.r == b.l && a.r == a.mx);
                else tie(ret.mx, ret.cnt) = max(pii(a.mx, a.cnt), pii(b.mx, b.cnt));
                return ret;
        }
} t[N<<1];

int n, m;

void push(int p, int l, int r) {
        if(t[p].lz) {
                t[p].l += t[p].lz, t[p].r += t[p].lz, t[p].mx += t[p].lz;
                if(l != r) {
                        t[p<<1].lz += t[p].lz;
                        t[p<<1|1].lz += t[p].lz;
                }
                t[p].lz = 0;
        }
}

void update(int x, int y, int k, int p = 1, int l = 1, int r = n) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) {
                t[p].lz = k;
                push(p, l, r);
                return;
        }
        int m = (l + r) >> 1;
        update(x, y, k, p<<1, l, m), update(x, y, k, p<<1|1, m+1, r);
        t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
        scanf("%d %d", &n, &m);
        while(m--) {
                int a, b, x;
                scanf("%d %d %d", &a, &b, &x);
                update(a, b, x);
                printf("%d %d\n", t[1].mx, t[1].cnt);
        }

        return 0;
}
