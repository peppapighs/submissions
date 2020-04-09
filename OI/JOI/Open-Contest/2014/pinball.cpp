#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5+5;

void update(long t[], int x, long k) {
    x += N;
    for(t[x] = min(t[x], k); x != 1; x >>= 1)
        t[x >> 1] = min(t[x], t[x ^ 1]);
}

long query(long t[], int l, int r) {
    long ret = 1e18;
    for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = min(ret, t[l++]);
        if(r & 1) ret = min(ret, t[--r]);
    }
    return ret;
}

int n, m;
int A[N], B[N], C[N], D[N];
vector<int> coord;
long t1[N << 1], t2[N << 1];

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }

int main() {
    fill_n(t1, N << 1, 1e18), fill_n(t2, N << 1, 1e18);

    scanf("%d %d", &n, &m);
    coord.emplace_back(1), coord.emplace_back(m);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", A + i, B + i, C + i, D + i);
        coord.emplace_back(A[i]), coord.emplace_back(B[i]);
        coord.emplace_back(C[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    
    long ans = 1e18;
    update(t1, 1, 0), update(t2, coord.size(), 0); 
    for(int i = 1; i <= n; i++) {
        long pre = query(t1, get(A[i]), get(B[i]));
        long suf = query(t2, get(A[i]), get(B[i]));
        ans = min(ans, pre + suf + D[i]);
        update(t1, get(C[i]), pre + D[i]), update(t2, get(C[i]), suf + D[i]);
    }
    if(ans == 1e18) printf("-1\n");
    else printf("%lld\n", ans);

    return 0;
}