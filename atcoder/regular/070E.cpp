#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n;
int l[N], r[N];
long high, lz_l, lz_r;
multiset<long> L, R;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d %d", l + i, r + i), r[i] -= l[i];
    for(int i = 1; i <= n; i++) {
        high += l[i];
        L.emplace(l[i] + lz_l), R.emplace(l[i] - lz_r);
        while(*L.rbegin() - lz_l > *R.begin() + lz_r) {
            long l = *L.rbegin(), r = *R.begin();
            L.erase(L.find(l)), R.erase(R.find(r));
            L.emplace(r + lz_r + lz_l), R.emplace(l - lz_l - lz_r);
        }
        long pv = 0;
        while(!L.empty() && *L.begin() - lz_l - r[i + 1] <= 0) {
            high -= abs(*L.begin() - lz_l - pv) * L.size();
            pv = *L.begin() - lz_l;
            L.erase(L.begin());
        }
        high -= abs(pv - r[i + 1]) * L.size();
        lz_l += r[i + 1], lz_r += r[i];
    }
    long m = L.size(), pv = 0;
    for(long x : L) {
        high -= abs(x - lz_l - pv) * m--;
        pv = x - lz_l;
    }
    printf("%lld\n", high);

    return 0;
}