#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    long long arr[n], pre[n], k[q];

    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
        pre[i] = arr[i];
        if (i > 0) {
            pre[i] += pre[i - 1];
        }
    }
    for (int i = 0; i < q; i++) {
        scanf("%lld", &k[i]);
    }
    int cur = 0;
    long long hit = 0;

    for (int t = 0; t < q; t++) {
        if (k[t] + hit < arr[cur]) {
            hit += k[t];
            printf("%d\n", n - cur);
        } else {
            int low = cur, high = n - 1;
            int res = n;
            long long x = cur > 0 ? pre[cur - 1] : 0;
            while (low <= high) {
                long long mid = (low + high) / 2;
                if (k[t] + hit < pre[mid] - x) {
                    res = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            if (res == n) {
                hit = 0;
                cur = 0;
                printf("%d\n", n);
            } else {
                hit = arr[res] - pre[res] + hit + k[t] + x;
                cur = res;
                printf("%d\n", n - cur);
            }
        }
    }

    return 0;
}
