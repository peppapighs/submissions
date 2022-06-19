#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5 + 5;

int n;
long a[N], b[N], cnt[N];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld %lld", a + i, b + i);
    cnt[1] = a[1];
    for (int i = 2; i <= n; i++)
        cnt[i] = cnt[i - 1] + max(0ll, a[i] - b[i - 1]);
    long ans = cnt[n], sub = 0;
    for (int i = 2; i <= n; i++) {
        sub += (cnt[i - 1] - sub) - min(b[i - 1], a[i]);
        int pre = i - 2 ? i - 2 : n;
        cnt[i - 1] = cnt[pre] + max(0ll, a[i - 1] - b[pre]);
        ans = min(ans, cnt[i - 1] - sub);
    }
    printf("%lld\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}