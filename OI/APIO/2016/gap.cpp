#include "gap.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

long findGap(int T, int n) {
    long l, r;
    MinMax(0, 2e18, &l, &r);
    if (T == 1) {
        long ans = 0;
        for (int i = 1; i < (n + 1) / 2; i++) {
            long nl, nr;
            MinMax(l + 1, r - 1, &nl, &nr);
            if (nl != -1)
                ans = max(ans, nl - l), l = nl;
            if (nr != -1)
                ans = max(ans, r - nr), r = nr;
        }
        if (l != r)
            ans = max(ans, r - l);
        return ans;
    } else {
        long gap = (r - l + n - 1) / n, ans = 0, pv = l;
        for (long i = l + 1, j = i + gap;; i = j + 1, j = i + gap) {
            long nl, nr;
            j = min(j, r - 1);
            if (i > j)
                break;
            MinMax(i, j, &nl, &nr);
            if (nl != -1)
                ans = max(ans, nl - pv);
            if (nr != -1)
                pv = nr;
        }
        return max(ans, r - pv);
    }
}