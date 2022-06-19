#include <bits/stdc++.h>

using namespace std;

int main() {
    long long arr[14];
    for (int i = 0; i < 14; i++) {
        scanf("%lld", &arr[i]);
    }

    long long ans = 0;

    for (int i = 0; i < 14; i++) {
        if (arr[i] > 0) {
            long long psum[14] = {0};
            for (int j = 0; j < 14; j++) {
                psum[j] += arr[j];
                if (j < 13) {
                    psum[j + 1] -= arr[j];
                }
            }
            long long val = arr[i];
            if (arr[i] <= 13 - i) {
                psum[i] -= arr[i];
                if (i + 1 < 14) {
                    psum[i + 1] += (arr[i] + 1);
                }
                if (i + arr[i] + 1 < 14) {
                    psum[i + arr[i] + 1] -= 1;
                }
            } else {
                psum[i] -= arr[i];
                if (i + 1 < 14) {
                    psum[i + 1] += (arr[i] + 1);
                }
                val -= (13 - i);
                long long k = val / 14;
                psum[0] += k;
                val -= (k * 14);
                psum[0] += 1;
                psum[val] -= 1;
            }
            long long res = 0;
            // printf("%d ",psum[0]);
            for (int j = 1; j < 14; j++) {
                psum[j] += psum[j - 1];
                // printf("%d ",psum[j]);
            }
            // printf("\n");
            for (int j = 0; j < 14; j++) {
                if (psum[j] % 2 == 0) {
                    res += psum[j];
                }
            }

            ans = max(res, ans);
        }
    }

    printf("%lld", ans);

    return 0;
}
