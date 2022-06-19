#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, m, a, b;
    scanf("%lld%lld%lld%lld", &n, &m, &a, &b);
    long long c1 = n % m;
    long long c2 = m - c1;
    printf("%lld", min(c1 * b, c2 * a));

    return 0;
}