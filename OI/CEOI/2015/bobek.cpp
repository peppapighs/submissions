#include <bits/stdc++.h>

#define long long long

using namespace std;

vector<long> process(vector<long> &v) {
    vector<long> ret;
    for (int i = 0; i < (1 << (int)v.size()); i++) {
        long now = 0;
        for (int j = 0; j < v.size(); j++)
            if (i >> j & 1)
                now += v[j];
        ret.emplace_back(now);
    }
    return ret;
}

int n;
long m;

int main() {
    scanf("%d %lld", &n, &m);
    vector<long> l, r;
    long a;
    for (int i = 1; i <= n / 2; i++) {
        scanf("%lld", &a);
        l.emplace_back(a);
    }
    for (int i = n / 2 + 1; i <= n; i++) {
        scanf("%lld", &a);
        r.emplace_back(a);
    }
    vector<long> sum_l = process(l);
    vector<long> sum_r = process(r);
    sort(sum_l.begin(), sum_l.end());

    long ans = 0;
    for (long x : sum_r)
        ans += upper_bound(sum_l.begin(), sum_l.end(), m - x) - sum_l.begin();
    printf("%lld\n", ans);

    return 0;
}