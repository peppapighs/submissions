#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int n, m;
long A[N];

void solve() {
    scanf("%d %d", &n, &m);
    long l = 1e18, r = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        l = min(l, A[i]);
        r += A[i];
    }
    while (l < r) {
        long mid = (l + r) / 2;

        int cnt = 1;
        long sum = 0;

        for (int i = 1; i <= n; i++) {
            if (sum + A[i] > mid) {
                sum = A[i];
                ++cnt;
            } else
                sum += A[i];
        }
        if (cnt <= m)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", r);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}