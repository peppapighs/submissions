#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n;
long k, pref[N], t[N];
vector<long> coord;

int get(long x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}
void update(int x, long k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}
long query(int x, long ret = 0) {
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", pref + i);
        pref[i] += pref[i - 1];
        coord.emplace_back(pref[i]);
    }

    coord.emplace_back(0);
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    long l = -1e11, r = 1e11;
    while (l < r) {
        long mid = (l + r + 1) >> 1, now = 0;

        memset(t, 0, sizeof t);
        update(get(0), 1);
        for (int i = 1; i <= n; i++) {
            int pos = get(pref[i] - mid);
            if (coord[pos - 1] > pref[i] - mid)
                --pos;
            if (pos)
                now += query(pos);
            update(get(pref[i]), 1);
        }

        if (now >= k)
            l = mid;
        else
            r = mid - 1;
    }

    printf("%lld\n", l);

    return 0;
}