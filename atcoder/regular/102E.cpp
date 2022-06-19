#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;
const int M = 998244353;

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

long f[2 * N], inv[2 * N];

long ncr(int a, int b) {
    if (b > a || a < 0 || b < 0)
        return 0;
    return f[a] * inv[b] % M * inv[a - b] % M;
}

int n, k;

void solve(int x) {
    int cnt = 0, left;
    for (int i = 1; i <= k; i++)
        if (1 <= x - i && x - i <= k)
            ++cnt;
    left = k - cnt, cnt >>= 1;
    long ans = 0;
    for (int i = 0; i <= cnt; i++) {
        long now;
        if (x & 1)
            now = ncr(n + left - 1, i + left - 1);
        else {
            now = ncr(n + left - 1, i + left - 1);
            now = (now + ncr(n + left - 2, i + left - 1)) % M;
        }
        now = now * ncr(cnt, i) % M * modpow(2, i) % M;
        ans = (ans + now) % M;
    }
    printf("%lld\n", ans);
}

int main() {
    f[0] = inv[0] = 1;
    for (int i = 1; i < 2 * N; i++) {
        f[i] = (f[i - 1] * i) % M;
        inv[i] = modpow(f[i], M - 2);
    }

    scanf("%d %d", &k, &n);
    for (int i = 2; i <= 2 * k; i++)
        solve(i);

    return 0;
}