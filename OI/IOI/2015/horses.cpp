#include "horses.h"
#include <bits/stdc++.h>
 
#define long long long
 
using namespace std;
 
const int N = 1<<19;
const int M = 1e9+7;
 
#define var int p = 1, int l = 0, int r = n-1
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r
 
struct node {
    double log;
    long sum;
    node() : log(0), sum(1) { }
    node(double log, long sum) : log(log), sum(sum) { }
    friend node operator+(const node &a, const node &b) {
        node ret;
        ret.log = a.log + b.log;
        ret.sum = (a.sum * b.sum) % M;
        return ret;
    }
    friend bool operator<(const node &a, const node &b) {
        return make_pair(a.log, a.sum) < make_pair(b.log, b.sum);
    }
} t[N<<1], lz[N<<1];
 
int n, x[N], y[N];
node A[N];
 
void build(var) {
    if(l == r) return void(t[p] = A[l]);
    build(lb), build(rb);
    t[p] = t[p<<1] < t[p<<1|1] ? t[p<<1|1] : t[p<<1];
}
 
void push(var) {
    t[p] = t[p] + lz[p];
    if(l != r) {
        lz[p<<1] = lz[p<<1] + lz[p];
        lz[p<<1|1] = lz[p<<1|1] + lz[p];
    }
    lz[p] = node(0, 1);
}
 
void update(int x, int y, node k, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        lz[p] = lz[p] + k;
        push(p, l, r);
        return;
    }
    update(x, y, k, lb), update(x, y, k, rb);
    t[p] = t[p<<1] < t[p<<1|1] ? t[p<<1|1] : t[p<<1];
}
 
int init(int N, int X[], int Y[]) {
    n = N;
    node cul(0, 1);
    for(int i = 0; i < n; i++) {
        x[i] = X[i], y[i] = Y[i];
        cul = cul + node((double)log2(x[i]), x[i]);
        A[i] = cul + node((double)log2(y[i]), y[i]); 
    }
    build();
    return t[1].sum;
}
 
long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}
 
int updateX(int pos, int val) {
    double nlog = (double)log2(val) - (double)log2(x[pos]);
    long nsum = (1ll * val * modpow(x[pos], M-2)) % M;
    x[pos] = val;
    update(pos, n-1, node(nlog, nsum));
    return t[1].sum;
}
 
int updateY(int pos, int val) {
    double nlog = (double)log2(val) - (double)log2(y[pos]);
    long nsum = (1ll * val * modpow(y[pos], M-2)) % M;
    y[pos] = val;
    update(pos, pos, node(nlog, nsum));
    return t[1].sum;
}