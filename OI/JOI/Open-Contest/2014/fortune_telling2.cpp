#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 4e5 + 5;

struct SegmentTreeMax {
    int t[N << 1];
    void update(int x, int k) {
        x += N;
        for (t[x] = max(t[x], k); x != 1; x >>= 1)
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
} t1;

struct SegmentTreeSum {
    int t[N << 1];
    void update(int x, int k) {
        for (t[x += N] += k; x != 1; x >>= 1)
            t[x >> 1] = t[x] + t[x ^ 1];
    }
    int query(int l, int r) {
        int ret = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (r & 1)
                ret += t[--r];
        }
        return ret;
    }
} t2;

int n, k;
int A[N], B[N], Q[N], cnt[N], pos[N];
vector<int> coord;
vector<pii> vec[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", A + i, B + i);
        coord.emplace_back(A[i]);
        coord.emplace_back(B[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    auto get = [&](int x) {
        return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
    };
    for (int i = 1; i <= k; i++) {
        scanf("%d", Q + i);
        int idx = upper_bound(coord.begin(), coord.end(), Q[i]) - coord.begin();
        t1.update(idx, i);
    }
    for (int i = 1; i <= n; i++) {
        int ia = get(A[i]), ib = get(B[i]);
        pos[i] = t1.query(min(ia, ib), max(ia, ib) - 1);
        vec[pos[i]].emplace_back(max(ia, ib), i);
    }
    for (int i = k; ~i; i--) {
        int idx = upper_bound(coord.begin(), coord.end(), Q[i]) - coord.begin();
        t2.update(idx, 1);
        for (pii p : vec[i])
            cnt[p.y] += t2.query(p.x, N - 1);
    }

    long ans = 0;
    for (int i = 1; i <= n; i++) {
        int now = (pos[i] && A[i] < B[i]) + cnt[i];
        ans += now & 1 ? B[i] : A[i];
    }
    printf("%lld\n", ans);

    return 0;
}