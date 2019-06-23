#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

int n;
long k, now, high;
multiset<long> L, R;

int main() {
    scanf("%d %lld", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &now);
        high += now;
        L.emplace(now + i * k), R.emplace(now - i * k);
        while(*L.rbegin() - i * k > *R.begin() + i * k) {
            long l = *L.rbegin(), r = *R.begin();
            L.erase(L.find(l)), R.erase(R.find(r));
            L.emplace(r + 2 * i * k), R.emplace(l - 2 * i * k);
        }
        long pv = 0;
        while(!L.empty() && *L.begin() - (i + 1) * k <= 0) {
            high -= L.size() * abs(*L.begin() - i * k - pv);
            pv = *L.begin() - i * k;
            L.erase(L.begin());
        }
        high -= L.size() * abs(pv - k);
    }
    long pv = 0, m = L.size(), ans = high;
    for(long x : L) {
        ans -= abs(x - n * k - pv) * m--;
        pv = x - n * k;
    }
    printf("%lld\n", ans);

    return 0;
}