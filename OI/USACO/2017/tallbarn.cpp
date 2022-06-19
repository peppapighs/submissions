#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n;
long k, A[N];

int main() {
    freopen("tallbarn.in", "r", stdin);
    freopen("tallbarn.out", "w", stdout);

    scanf("%d %lld", &n, &k), k -= n;
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i);

    double l = 0, r = 1e18;
    for (int step = 1; step <= 200; step++) {
        double mid = (l + r) / 2;
        long sum = 0;
        for (int i = 1; i <= n; i++)
            sum += (long)((sqrt(1 + 4.0 * A[i] / mid) - 1) / 2);
        if (sum >= k)
            l = mid;
        else
            r = mid;
    }
    double ans = 0;
    long sum = 0;
    for (int i = 1; i <= n; i++) {
        long now = (long)((sqrt(1 + 4.0 * A[i] / l) - 1) / 2);
        sum += now, ans += 1.0 * A[i] / (now + 1);
    }
    printf("%lld\n", (long)round(ans - (k - sum) * l));

    return 0;
}