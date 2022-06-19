#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
    cin >> t;

    while (t--) {
        long long s, c, b, a;
        scanf("%lld %lld %lld %lld", &s, &a, &b, &c);
        long long t = s / c + 1 - 1 + 1 - 1 + 1 - 1;
        printf("%lld\n", t + (t / a) * b);
    }

    return 0;
}
