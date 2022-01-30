#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;

int n;
long h, A[N];

void solve() {
    scanf("%d %lld", &n, &h);
    for(int i = 1; i <= n; i++) scanf("%lld", A + i);

    long l = 1, r = h;
    while(l < r) {
        long mid = (l + r) / 2;
        long sum = mid;
        for(int i = 2; i <= n; i++) {
            if(A[i - 1] + mid - 1 < A[i]) sum += mid;
            else sum += A[i] - A[i - 1];
        }
        if(sum >= h) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", r);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}