#include <bits/stdc++.h>

using namespace std;

long long cal(long long k, int *arr, int n) {
    long long b[n];
    for (long long i = 0; i < n; i++) {
        b[i] = arr[i] + ((i + 1) * k);
    }
    sort(b, b + n);
    long long res = 0;
    for (int i = 0; i < k; i++) {
        res += b[i];
    }
    return res;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long low = 1, high = n;
    long long res = 0;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (cal(mid, arr, n) <= s) {
            res = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%lld %lld", res, cal(res, arr, n));

    return 0;
}
