#include <bits/stdc++.h>

using namespace std;

long long n, m, k;

int main() {
    scanf("%lld %lld %lld", &n, &m, &k);
    if (2 * n * m % k != 0)
        return !printf("NO\n");
    bool odd = (k & 1);
    if (!odd)
        k >>= 1;
    long long g = __gcd(n, k);
    long long f = k / g;
    long long a = n / g, b = m / f;
    if (odd) {
        if (a * 2 <= n)
            a <<= 1;
        else
            b <<= 1;
    }
    printf("YES\n");
    printf("0 0\n");
    printf("%lld 0\n", a);
    printf("0 %lld\n", b);

    return 0;
}