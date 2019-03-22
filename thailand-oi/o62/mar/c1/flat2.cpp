#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, w, ans = -1;
int A[N], t[N<<1];
int res[N];

int query(int l, int r) {
    int ret = 1e9;
    for(l += N, r += N+1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = min(ret, t[l++]);
        if(r & 1) ret = min(ret, t[--r]);
    }
    return ret;
}

int main() {
    fill_n(res, N, -1);
    scanf("%d %d", &n, &w);
    for(int i = 1; i <= n; i++) {
        scanf("%d", A+i);
        t[N + i] = A[i];
    }
    for(int i = N-1; i; i--) t[i] = min(t[i<<1], t[i<<1|1]);
    for(int i = 1; i <= n; i++) {
        int low = i, high = i;
        int l = i+1, r = n;
        if(l <= r) {
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(query(i+1, mid) >= A[i]) l = mid;
                else r = mid-1;
            }
            if(query(i, l) >= A[i]) high = l;
            else high = i;
        }
        l = 1, r = i-1;
        if(l <= r) {
            while(l < r) {
                int mid = (l + r) >> 1;
                if(query(mid, i-1) >= A[i]) r = mid;
                else l = mid+1;
            }
            if(query(r, i) >= A[i]) low = r;
            else low = i;
        }
        if(high - low == w) ans = max(ans, A[i]);
        res[high - low] = max(res[high - low], A[i]);
    }
    if(w > 0) printf("%d", ans);
    else for(int i = 1; i <= n; i++) printf("%d ", res[i]);
    printf("\n");

    return 0;
}