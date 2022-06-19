#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long a, b, k;
        scanf("%lld %lld %lld", &a, &b, &k);
        if (k < max(a, b)) {
            puts("-1");
            continue;
        }
        printf("%lld\n", k - ((a ^ k) & 1) - ((b ^ k) & 1));
    }
}
