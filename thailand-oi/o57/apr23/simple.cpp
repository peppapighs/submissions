#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 55;
const int M = 1e9 + 7;

long x, k, ans, f[N];

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

long ncr(int a, int b) {
    long ret = (f[a] * modpow(f[b], M - 2)) % M;
    return (ret * modpow(f[a - b], M - 2)) % M;
}

long bernoulli(long x, long m) {
    long ret = 0;
    for (int i = 0; i <= m; i++) {
        long sum = 0;
        for (int j = 0; j <= i; j++) {
            long now = (j & 1) ? M - 1 : 1;
            now = (now * ncr(i, j)) % M;
            now = (now * modpow(x + j, m)) % M;
            sum = (sum + now) % M;
        }
        sum = (sum * modpow(i + 1, M - 2)) % M;
        ret = (ret + sum) % M;
    }
    return ret;
}

int main() {
    f[0] = 1;
    for (int i = 1; i < N; i++)
        f[i] = (f[i - 1] * i) % M;
    scanf("%lld %lld", &x, &k);
    for (int p = 1; p <= k; p++) {
        long now = (bernoulli(x + 1, p + 1) - bernoulli(0, p + 1) + M) % M;
        now = (now * modpow(p + 1, M - 2)) % M;
        now = (now * p) % M;
        ans = (ans + now) % M;
    }
    printf("%lld\n", ans);

    return 0;
}