#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;

int n, k;
long long qs[N], ans;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &qs[i]), qs[i] += qs[i - 1];
    for (int b = 43; ~b; b--) {
        int dp[N];
        fill(begin(dp), end(dp), 1e9);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++) {
                long long sum = qs[j] - qs[i - 1];
                if (!(sum & (1LL << b)) &&
                    ((sum | ans) >> (b + 1)) == (ans >> (b + 1)))
                    dp[j] = min(dp[j], dp[i - 1] + 1);
            }
        if (dp[n] > k)
            ans |= (1LL << b);
    }

    printf("%lld", ans);

    return 0;
}