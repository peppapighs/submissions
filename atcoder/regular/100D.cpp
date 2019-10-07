#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

int n;
long A[N];
vector<long> pre, suf;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", A + i);
    for(int i = 1; i <= n; i++) {
        if(pre.empty()) pre.emplace_back(A[i]);
        else pre.emplace_back(pre.back() + A[i]);
    }
    for(int i = n; i; i--) {
        if(suf.empty()) suf.emplace_back(A[i]);
        else suf.emplace_back(suf.back() + A[i]);
    }
    long p, q, r, s, ans = 1e18;
    for(int i = 3; i < n; i++) {
        long left = pre[i - 2], right = suf[n - i];
        bool L = false, R = false;

        auto it1 = lower_bound(pre.begin(), pre.end(), left / 2);
        if(it1 != pre.end() && *it1 != left) {
            p = *it1, q = left - *it1;
            L = true;
        }
        if(it1 != pre.begin()) {
            --it1;
            if(!L || abs(p - q) > abs(left - 2ll * (*it1)))
                p = *it1, q = left - *it1;
        }
        auto it2 = lower_bound(suf.begin(), suf.end(), right / 2);
        if(it2 != suf.end() && *it2 != right) {
            r = *it2, s = right - *it2;
            R = true;
        }
        if(it2 != suf.begin()) {
            --it2;
            if(!R || abs(r - s) > abs(right - 2ll * (*it2)))
                r = *it2, s = right - *it2;
        }
        ans = min(ans, max({p, q, r, s}) - min({p, q, r, s}));
    }
    printf("%lld\n", ans);

    return 0;
}