#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n;
int A[N];

int T;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);

        long ans = 0;
        for (int i = 1, a; i <= n; i++) {
            scanf("%d %d", &a, A + i);
            ans += a;
        }
        sort(A + 1, A + n + 1, greater<int>());
        for (int i = 1; i <= n; i++)
            ans += 1ll * (i - 1) * A[i];
        printf("%lld\n", ans);
    }

    return 0;
}