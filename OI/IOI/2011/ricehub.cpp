#include "ricehub.h"
#include <bits/stdc++.h>

using namespace std;

long long min(long long a, int b) { return a < b ? a : b; }

int besthub(int R, int L, int X[], long long B) {
    long long qs[R];
    qs[0] = X[0];
    for (int i = 1; i < R; i++)
        qs[i] = (qs[i - 1] + X[i]);
    int l = 0, r = R;
    int ret = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int wm = mid >> 1;
        long long mn = LLONG_MAX;
        for (int i = 0; i < R - mid + 1; i++) {
            if (mid == 1)
                mn = min(mn, 0);
            else if (mid == 2)
                mn = min(mn, X[i + wm] - X[i + wm - 1]);
            else {
                long long cost;
                if (mid & 1)
                    cost = qs[i + mid - 1] - qs[i + wm] - qs[i + wm - 1] +
                           (i > 0 ? qs[i - 1] : 0);
                else
                    cost = qs[i + mid - 1] - qs[i + wm] - qs[i + wm - 1] +
                           (i > 0 ? qs[i - 1] : 0) + X[i + wm];
                mn = min(mn, cost);
            }
        }
        if (mn <= B) {
            ret = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return ret;
}