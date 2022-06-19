#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int M = 1e9 + 7;

int n, m;
long long ans = 1LL;
long long fac[N];

long long modpow(int b, int x) {
    long long base = b, ret = 1;
    for (; x; x >>= 1) {
        if (x & 1)
            ret = (ret * base) % M;
        base = (base * base) % M;
    }
    return ret;
}

long long ncr(int a, int b) {
    int ret = fac[a];
    ret = (ret * modpow(fac[b], M - 2)) % M;
    ret = (ret * modpow(fac[a - b], M - 2)) % M;
    return ret;
}

int main() {
    fac[0] = 1LL;
    for (int i = 1; i < N; i++)
        fac[i] = (fac[i - 1] * i) % M;
    scanf("%d %d", &n, &m);
    int t = m;
    for (int i = 2; i * i <= m; i++) {
        int s = 0;
        for (; t % i == 0; t /= i)
            s++;
        ans = (ans * ncr(n + s - 1, s)) % M;
    }
    if (t != 1)
        ans = (ans * n) % M;
    printf("%lld\n", ans);

    return 0;
}
