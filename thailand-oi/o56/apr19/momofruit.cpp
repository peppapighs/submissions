#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n, t[N << 1];
long A[N];
vector<long> coord;

int get(long x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

void update(int x, long k) {
    for (t[x += N] = k; x != 1; x >>= 1)
        t[x >> 1] = max(t[x], t[x ^ 1]);
}

int query(int l, int r) {
    int ret = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = max(ret, t[l++]);
        if (r & 1)
            ret = max(ret, t[--r]);
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i), A[i] += A[i - 1];
    for (int i = 1; i <= n; i++)
        coord.emplace_back(A[i]);
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (int i = 1; i <= n; i++) {
        int now = query(0, get(A[i]) - 1);
        if (now)
            update(get(A[i]), now + 1);
        else if (A[i] > 0)
            update(get(A[i]), 1);
    }
    printf("%d\n", query(get(A[n]), get(A[n])));

    return 0;
}