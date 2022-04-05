#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;
const int M = 1e9 + 7;

struct item {
    long l, r;
    long sum, pre, suf, ans;
    bool valid;
    item() {}
    item(long x) : l(x), r(x), sum(x), pre(x), suf(x), ans(x), valid(true) {}
    friend item operator+(const item &lhs, const item &rhs) {
        item ret;

        ret.l = lhs.l;
        ret.r = rhs.r;

        ret.pre = lhs.pre;
        if(lhs.valid && lhs.r >= rhs.l) ret.pre = max(ret.pre, lhs.sum + rhs.pre);	

        ret.suf = rhs.suf;
        if(rhs.valid && lhs.r >= rhs.l) ret.suf = max(ret.suf, lhs.suf + rhs.sum);

        if(lhs.valid && rhs.valid && lhs.r >= rhs.l) {
            ret.valid = true;
            ret.sum = lhs.sum + rhs.sum;
        } else {
            ret.valid = false;
            ret.sum = -1e9;
        }
        
        ret.ans = max(lhs.ans, rhs.ans);
        if(lhs.r >= rhs.l) ret.ans = max(ret.ans, lhs.suf + rhs.pre);
        return ret;
    }
} t[N << 1];

int n, q;

void update(int x, int k) {
    t[x + n] = item(k);
    for(x += n; x != 1; x >>= 1) {
        if(x & 1) t[x >> 1] = t[x ^ 1] + t[x];
        else t[x >> 1] = t[x] + t[x ^ 1];
    }
}

void solve() {
    for(int i = 0; i < n; i++) t[i + n] = item(-1);
    for(int i = n - 1; i; i--) t[i] = t[i << 1] + t[i << 1 | 1];

    long ans = 0;
    for(int i = 1, u, au; i <= q; i++) {
        scanf("%d %d", &u, &au);
        update(u, au);
        ans = (ans + t[1].ans + M) % M;	
    }
    printf("%lld\n", ans);
}

int main() {
    while(scanf("%d %d", &n, &q) != EOF) solve();	

    return 0;
}