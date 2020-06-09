#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e3 + 5;
const int M = 1e9 + 7;

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int n;
int mnx = 1e9, mny = 1e9, mxx = -1e9, mxy = -1e9;
int x[N], y[N];

bool chk(int k) {
    bool b1 = true, b2 = true;
    for(int i = 1; i <= n; i++) {
        b1 &= (x[i] - mnx <= k && y[i] - mny <= k) || (mxx - x[i] <= k && mxy - y[i] <= k);
        b2 &= (x[i] - mnx <= k && mxy - y[i] <= k) || (mxx - x[i] <= k && y[i] - mny <= k);
    }
    return b1 || b2;
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        x[i] = a + b, y[i] = a - b;
        mnx = min(mnx, x[i]), mny = min(mny, y[i]);
        mxx = max(mxx, x[i]), mxy = max(mxy, y[i]);
    }
    int l = 0, r = 1e9;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(chk(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);

    bool b1 = true, b2 = true;
    long cnt = 0;
    for(int i = 1; i <= n; i++) {
        b1 &= (x[i] - mnx <= r && y[i] - mny <= r) || (mxx - x[i] <= r && mxy - y[i] <= r);
        b2 &= (x[i] - mnx <= r && mxy - y[i] <= r) || (mxx - x[i] <= r && y[i] - mny <= r);
        if(x[i] - mnx <= r && y[i] - mny <= r && mxx - x[i] <= r && mxy - y[i] <= r) ++cnt;
    }
    printf("%lld\n", modpow(2, cnt + 1 + (b1 && b2 && r < mxx - mnx && r < mxy - mny)) % M);

    return 0;
}