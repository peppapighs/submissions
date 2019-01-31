#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, q;
long A[N];
pii t[N<<1];

pii add(pii a, pii b) { return pii(a.x + b.x, max(a.y, b.y)); }

void build(var) {
    if(l == r) return void(t[p] = pii(A[l], A[l]));
    build(lb), build(rb);
    t[p] = add(t[p<<1], t[p<<1|1]);
}

void upd1(int x, int y, int M, var) {
    if(x > r || l > y || t[p].y < M) return;
    if(l == r) { t[p] = pii(t[p].x % M, t[p].x % M); return; }
    upd1(x, y, M, lb), upd1(x, y, M, rb);
    t[p] = add(t[p<<1], t[p<<1|1]);
}

void upd2(int x, int k, var) {
    if(l == r) { t[p] = pii(k, k); return; }
    if(x <= mid) upd2(x, k, lb);
    else upd2(x, k, rb);
    t[p] = add(t[p<<1], t[p<<1|1]);
}

long query(int x, int y, var) {
    if(x > r || l > y) return 0;
    if(x <= l && r <= y) return t[p].x;
    return query(x, y, lb) + query(x, y, rb);
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%lld", A+i);
    build();
    while(q--) {
        int T, a, b, c;
        scanf("%d %d %d", &T, &a, &b);
        if(T == 1) printf("%lld\n", query(a, b));
        else if(T == 2) {
            scanf("%d", &c);
            upd1(a, b, c);
        } else upd2(a, b);
    }

    return 0;
}