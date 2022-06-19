#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;
const int M = 998244353;

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

long fac[N], inv[N];

long ncr(int a, int b) {
    if (a < b)
        return 0;
    return fac[a] * inv[b] % M * inv[a - b] % M;
}

int n, m;

int main() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % M;
        inv[i] = modpow(fac[i], M - 2);
    }

    scanf("%d %d", &n, &m);

    long ans = 0;
    for (int i = 1; i <= m; i++) {
        long now = ncr(m - 1, n - 2) * modpow(2, n - 2) % M;
        now = (now - ncr(i - 1, n - 2) * modpow(2, n - 2) % M + M) % M;
        ans = (ans + now) % M;
    }
    printf("%lld\n", ans * modpow(2, M - 2) % M);

    return 0;
}