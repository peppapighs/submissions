// Each exam choose a group represents its day, then choose i exam as day change
// but the next exam id is greater

#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;
const int M = 1e9 + 7;

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int n, k;
long fac[N], inv[N];

long ncr(int a, int b) { return fac[a] * inv[b] % M * inv[a - b] % M; }

int main() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % M;
        inv[i] = modpow(fac[i], M - 2);
    }

    scanf("%d %d", &n, &k);
    long ans = 0;
    for (int i = 0; i <= k; i++) {
        long l = ncr(n, i), r = modpow(k - i, n);
        if (i < k)
            r = (r - modpow(k - i - 1, n) + M) % M;
        l = l * r % M;
        if (i & 1)
            ans = (ans - l + M) % M;
        else
            ans = (ans + l) % M;
    }
    printf("%lld\n", ans);

    return 0;
}