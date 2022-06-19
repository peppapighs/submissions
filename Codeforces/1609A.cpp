#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, cnt;
long A[20];

void solve() {
    cnt = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        while (A[i] % 2 == 0) {
            ++cnt;
            A[i] /= 2;
        }
    }
    sort(A + 1, A + n + 1);

    long sum = 0;
    for (int i = 1; i < n; i++)
        sum += A[i];
    while (cnt--)
        A[n] *= 2;
    sum += A[n];

    printf("%lld\n", sum);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}