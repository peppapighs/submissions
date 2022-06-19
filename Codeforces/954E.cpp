#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    long long t;
    scanf("%d%lld", &n, &t);
    long long wsum = 0LL;
    long long sum = 0LL;
    pair<long long, long long> taps[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &taps[i].second);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &taps[i].first);
        wsum += taps[i].first * taps[i].second;
        sum += taps[i].second;
    }

    sort(taps, taps + n);

    if (wsum <= t * sum) {
        t *= -1;
        for (int i = 0; i < n; i++) {
            taps[i].first *= -1;
        }
        reverse(taps, taps + n);
        wsum *= -1;
    }

    int k = n - 1;
    while (k >= 0 && wsum > t * sum) {
        wsum -= taps[k].first * taps[k].second;
        sum -= taps[k].second;
        k--;
    }

    k++;
    long double low = 0.0L, high = taps[k].second;
    for (int e = 0; e < 100; e++) {
        long double mid = (low + high) / 2.0L;
        long double kwsum = wsum + (mid * taps[k].first);
        long double ksum = sum + mid;
        if (kwsum <= t * ksum) {
            low = mid;
        } else {
            high = mid;
        }
    }

    printf("%.10Lf", sum + low);

    return 0;
}
