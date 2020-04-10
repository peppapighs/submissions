#include <bits/stdc++.h>

#define long long long

using namespace std;

int n;
long l, r;

void solve() {
    scanf("%d %lld %lld", &n, &l, &r);
    int cnt = 1;
    long idx = 0;
    int L = 1, R = n;
    while(L < R) {
        int mid = (L + R + 1) >> 1;
        long now = 2ll * n * (mid - 1) - 1ll * mid * (mid - 1);
        if(now < l) L = mid;
        else R = mid - 1;
    }
    cnt = L, idx = 2ll * n * (cnt - 1) - 1ll * cnt * (cnt - 1);
    for(long i = l; i <= r; i++) {
        if(i == 1ll * n * (n - 1) + 1) printf("1 ");
        else if((i - idx) & 1) printf("%d ", cnt);
        else {
            printf("%d ", (i - idx) / 2 + cnt);
            if((i - idx) / 2 + cnt == n) {
                idx += 2ll * (n - cnt);
                ++cnt;
            }
        }
    }
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}