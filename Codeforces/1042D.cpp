#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const int M = 2e5 + 5;

int n;
long long k, ans, pref[N];
int t[N << 1];
vector<long long> V;

int get(long long x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

void update(int i, int k) {
    for (t[i += M] += k; i != 1; i >>= 1)
        t[i >> 1] = t[i] + t[i ^ 1];
}

int query(int l, int r) {
    int sum = 0;
    for (l += M, r += M + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            sum += t[l++];
        if (r & 1)
            sum += t[--r];
    }
    return sum;
}

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &pref[i]);
        pref[i] += pref[i - 1];
    }
    V.emplace_back(0);
    for (int i = 1; i <= n; i++)
        V.emplace_back(pref[i]);
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    update(get(0), 1);
    for (int i = 1; i <= n; i++) {
        long long z = pref[i] - k + 1;
        ans += (long long)query(get(z), V.size());
        update(get(pref[i]), 1);
    }

    printf("%lld\n", ans);

    return 0;
}
