#include <bits/stdc++.h>

using namespace std;

int n, r;
long long k;

long long check(long long x, long long *arr) {
    long long t[n + r] = {0};
    long long archers = 0, windows = 0;
    for (int i = 0; i < r; i++) {
        windows += arr[i];
    }
    for (int i = 0; i < n; i++) {
        windows += (i + r > n - 1 ? 0 : arr[i + r]);
        if (windows < x) {
            archers += x - windows;
            if (archers > k) {
                return false;
            }
            t[i + r] += x - windows;
            windows = x;
        }
        if (i - r >= 0) {
            windows -= (arr[i - r] + t[i - r]);
        }
    }
    return archers <= k;
}

int main() {
    scanf("%d%d%lld", &n, &r, &k);
    long long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    long long low = 1, high = LONG_LONG_MAX;
    long long res;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(mid, arr)) {
            low = mid + 1;
            res = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%lld", res);

    return 0;
}
