#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

int n;
long l;
long t[N<<1], lz[N<<1], A[N];
vector<long> Q;
vector<pii> seg;

void push(int p, int l, int r) {
        if(lz[p] == -1) {
                t[p] *= -1;
                if(l != r) {
                        lz[p<<1] *= -1;
                        lz[p<<1|1] *= -1;
                }
                lz[p] = 1;
        }
}

void build(int p = 1, int l = 1, int r = n+1) {
        lz[p] = 1;
        if(l == r) return void(t[p] = seg[l-1].y - seg[l-1].x);
        int m = (l + r) >> 1;
        build(p<<1, l, m), build(p<<1|1, m+1, r);
        t[p] = t[p<<1] + t[p<<1|1];
}

void update(int x, int y, int p = 1, int l = 1, int r = n+1) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) {
                lz[p] *= -1;
                push(p, l, r);
                return;
        }
        int m = (l + r) >> 1;
        update(x, y, p<<1, l, m), update(x, y, p<<1|1, m+1, r);
        t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
        scanf("%lld %d", &l, &n);
        for(int i = 1; i <= n; i++) scanf("%lld", A+i), Q.emplace_back(A[i]);
        sort(A+1, A+n+1);

        for(int i = 1; i <= n; i++) seg.emplace_back(A[i-1], A[i]);
        seg.emplace_back(A[n], l);
       
        build();

        for(long q : Q) {
               int x = lower_bound(seg.begin(), seg.end(), pii(q, INT_MIN)) - seg.begin(); 
               update(x+1, n+1);
               printf("%lld\n", (t[1] + l) / 2LL);
        }

        return 0;
}
