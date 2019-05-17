#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

const int N = 1<<17;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, q;
int t[N<<1];
pii lz[N<<1];

void build(var) {
    if(l == r) return void(t[p] = 10);
    build(lb), build(rb);
    t[p] = t[p<<1] + t[p<<1|1];
}

void push(var) {
    if(lz[p].x == 0) return;
    if(lz[p].x == 1) {
        t[p] = (r - l + 1) * lz[p].y;
        if(l != r) lz[p<<1] = lz[p<<1|1] = lz[p];
    } else {
        t[p] += (r - l + 1) * lz[p].y;
        if(l != r) {
            lz[p<<1].y += lz[p].y;
            lz[p<<1|1].y += lz[p].y;
            if(lz[p<<1].x != 1) lz[p<<1].x = 2;
            if(lz[p<<1|1].x != 1) lz[p<<1|1].x = 2;
        }
    }
    lz[p] = pii(0, 0);
}

template<typename T>
void travel(int x, int y, const T &f, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    travel(x, y, f, lb), travel(x, y, f, rb);
    t[p] = t[p<<1] + t[p<<1|1];
}

int findl(int k, int add = 0, var) {
    push(p, l, r);
    if(l == r) return l;
    push(p<<1|1, mid+1, r);
    int sum = t[p<<1|1] + add;
    if(sum >= k) return findl(k, add, rb);
    else return findl(k, sum, lb);
}

int findr(int k, int add = 0, var) {
    push(p, l, r);
    if(l == r) return l;
    push(p<<1, l, mid);
    int sum = t[p<<1] + add;
    if(sum >= k) return findr(k, add, lb);
    else return findr(k, sum, rb);
}

int main() {
    scanf("%d %d", &n, &q); --n;
    build();
    for(int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if(T == 1) {
            scanf("%d", &b);
            int half = b >> 1, now;
            travel(a, a, [&](var) { now = t[p]; });
            travel(a, a, [&](var) {
                lz[p].y += b;
                if(lz[p].x != 1) lz[p].x = 2;
                push(p, l, r);
            });
            int suml = 0, sumr = 0;
            travel(1, a-1, [&](var) { suml += t[p]; });
            travel(a+1, n, [&](var) { sumr += t[p]; });
            if(suml < half) {
                travel(1, a-1, [&](var) {
                    lz[p] = pii(1, 0);
                    push(p, l, r);
                });
                half = b - suml;
            } 
            if(sumr < half) {
                travel(a+1, n, [&](var) {
                    lz[p] = pii(1, 0);
                    push(p, l, r);
                });
                half = b - sumr;
            }
            if(suml >= half) {
                int sum = 0;
                travel(a, n, [&](var) { sum += t[p]; });
                int l = findl(half + sum);
                int now = 0;
                travel(l+1, a-1, [&](var) { now += t[p]; });
                travel(l+1, a-1, [&](var) {
                    lz[p] = pii(1, 0);
                    push(p, l, r);
                });
                travel(l, l, [&](var) {
                    lz[p].y -= half - now;
                    if(lz[p].x != 1) lz[p].x = 2;
                    push(p, l, r);
                });
            }
            if(sumr >= half) {
                int sum = 0;
                travel(1, a, [&](var) { sum += t[p]; });
                int r = findr(half + sum);
                int now = 0;
                travel(a+1, r-1, [&](var) { now += t[p]; });
                travel(a+1, r-1, [&](var) {
                    lz[p] = pii(1, 0);
                    push(p, l, r);
                });
                travel(r, r, [&](var) {
                    lz[p].y -= half - now;
                    if(lz[p].x != 1) lz[p].x = 2;
                    push(p, l, r);
                });
            }
        } else travel(a, a, [&](var) { printf("%d\n", t[p]); });
    }

    return 0;
}