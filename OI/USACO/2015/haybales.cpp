#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, q, A[N];
long mn[N<<1], sum[N<<1], lz[N<<1];

void build(var) {
    if(l == r) return void(mn[p] = sum[p] = A[l]);
    build(lb), build(rb);
    mn[p] = min(mn[p<<1], mn[p<<1|1]);
    sum[p] = sum[p<<1] + sum[p<<1|1];
}

void push(var) {
    if(!lz[p]) return;
    mn[p] += lz[p], sum[p] += lz[p] * (r - l + 1);
    if(l != r) lz[p<<1] += lz[p], lz[p<<1|1] += lz[p];
    lz[p] = 0;
}

void update(int x, int y, long k, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        lz[p] += k;
        push(p, l, r);
        return;
    }
    update(x, y, k, lb), update(x, y, k, rb);
    mn[p] = min(mn[p<<1], mn[p<<1|1]);
    sum[p] = sum[p<<1] + sum[p<<1|1];
}

pii query(int x, int y, var) {
    push(p, l, r);
    if(x <= l && r <= y) return pii(mn[p], sum[p]);
    if(y <= mid) return query(x, y, lb);
    else if(x > mid) return query(x, y, rb);
    pii L = query(x, y, lb), R = query(x, y, rb);
    return pii(min(L.x, R.x), L.y + R.y);
}

int main() {
    freopen("haybales.in", "r", stdin);    
    freopen("haybales.out", "w", stdout);    

    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    build();

    for(int i = 1; i <= q; i++) {
        char T;
        int a, b, c;
        scanf(" %c %d %d", &T, &a, &b);
        if(T == 'P') {
            scanf("%d", &c);
            update(a, b, c);
        } else {
            pii now = query(a, b);
            printf("%lld\n", T == 'M' ? now.x : now.y);
        }
    }

    return 0;
}