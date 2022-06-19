#include <bits/stdc++.h>

using namespace std;

long long n, m;

int main() {
    scanf("%lld %lld", &n, &m);
    long long mn = max(n - 2LL * m, 0LL);
    for (long long i = 0; i <= n; i++)
        if (i * (i - 1) / 2 >= m)
            return !printf("%lld %lld\n", mn, n - i);

    return 0;
}
