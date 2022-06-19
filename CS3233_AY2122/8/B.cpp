#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

long modpow(long a, long b, long P) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a % P;
        a = a * a % P;
    }
    return ret;
}

long m, n, P;
long fac[N], inv[N];

long ncr(long x, long y) {
    vector<long> a, b;
    for (; x; x /= P)
        a.emplace_back(x % P);
    for (; y; y /= P)
        b.emplace_back(y % P);

    while (b.size() < a.size())
        b.emplace_back(0);
    long ans = 1;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] < b[i])
            ans = 0;
        else
            ans = (ans * fac[a[i]] % P * modpow(fac[b[i]], P - 2, P) % P *
                   modpow(fac[a[i] - b[i]], P - 2, P) % P) %
                  P;
    }
    return ans;
}

void solve() {
    scanf("%lld %lld %lld", &m, &n, &P);

    fac[0] = 1;
    for (int i = 1; i <= P; i++)
        fac[i] = fac[i - 1] * i % P;

    long x = (n - m) / 2 + m - 1;
    long r = m - 1;

    printf("%lld\n", ncr(x, r));
}

int T;

int main() {

    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}