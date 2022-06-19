#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int t[N << 1];

void update(int x, int k) {
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

int n, x;
int A[N], pos[N];
vector<int> coord;

int main() {
    scanf("%d %d", &n, &x);
    vector<int> V;
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        coord.emplace_back(A[i]), V.emplace_back(i);
    }
    sort(coord.begin(), coord.end());
    sort(V.begin(), V.end(), [&](int a, int b) { return A[a] < A[b]; });
    for (int i = 0; i < n; i++)
        pos[V[i]] = i + 1;

    V.clear();
    for (int i = 1, z; i <= n; i++) {
        if (V.empty() || V.back() < A[i])
            V.emplace_back(A[i]), z = V.size();
        else {
            auto it = lower_bound(V.begin(), V.end(), A[i]);
            *it = A[i], z = it - V.begin() + 1;
        }
        update(pos[i], z);
    }
    int ans = V.size();
    V.clear();
    for (int i = n, z; i; i--) {
        update(pos[i], 0);
        if (V.empty() || V.back() > A[i])
            V.emplace_back(A[i]), z = V.size();
        else {
            auto it = lower_bound(V.begin(), V.end(), A[i], greater<int>());
            *it = A[i], z = it - V.begin() + 1;
        }
        int idx =
            lower_bound(coord.begin(), coord.end(), A[i] + x) - coord.begin();
        ans = max(ans, z + query(1, idx));
    }
    printf("%d\n", ans);

    return 0;
}