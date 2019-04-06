#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

int n, ans, A[N], t[N<<1];
vector<int> coord;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin(); }

void update(int x, int k) {
    x += N;
    for(t[x] = min(t[x], k); x != 1; x >>= 1)
        t[x>>1] = min(t[x], t[x^1]);
}

int query(int l, int r) {
    int ret = 1e9;
    for(l += N, r += N+1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = min(ret, t[l++]);
        if(r & 1) ret = min(ret, t[--r]);
    }
    return ret;
}

int main() {
    fill_n(t, N<<1, 1e9);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A+i), coord.emplace_back(A[i]);
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for(int i = 1; i <= n; i++) {
        ans = max(ans, i - min(query(0, get(A[i])-1), query(get(A[i]+1), N-1)));
        update(get(A[i]), i);
    }
    printf("%d\n", ans);

    return 0;
}
