#include "boxes.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e7+5;

long l[N], r[N];

long delivery(int n, int k, int L, int p[]) {
    for(int i = 1; i <= n; i++) {
        l[i] = 2ll * p[i-1], r[i] = 2ll * (L - p[n - i]);
        if(i >= k) l[i] += l[i - k], r[i] += r[i - k];
    }
    long ans = 1e18;
    for(int i = 0; i <= n; i++) {
        ans = min(ans, l[i] + r[n - i]);
        if(n - i - k >= 0) ans = min(ans, l[i] + r[n - i - k] + L);
    }
    return ans;
}