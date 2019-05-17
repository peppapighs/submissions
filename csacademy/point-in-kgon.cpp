#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;
const int M = 1e9+7;

long fac[N], inv[N];

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

void pre_comb() {
    fac[0] = inv[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1] * i) % M;
    for(int i = 1; i < N; i++) inv[i] = modpow(fac[i], M-2);
}

long ncr(int n, int r) { 
    if(r > n) return 0;
    return fac[n] * (inv[r] * inv[n-r] % M) % M; 
}

long cross(pii a, pii b, pii c) {
    pii vec1(b.x - a.x, b.y - a.y);
    pii vec2(c.x - a.x, c.y - a.y);
    return 1ll * vec1.x * vec2.y - 1ll * vec1.y * vec2.x;
}

int n, k, px, py;
pii a[N];

int main() {
    pre_comb();
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d %d", &a[i].x, &a[i].y);
    scanf("%d %d", &px, &py);

    long ans = ncr(n, k);
    for(int l = 0, r = 1; l < n; l++) {
        while(cross(a[l], a[r], pii(px, py)) >= 0) r = (r + 1) % n;
        int cnt = (r - l - 1 + n) % n;
        ans = (ans - ncr(cnt, k - 1) + M) % M;
    } 
    printf("%lld\n", ans);

    return 0;
}