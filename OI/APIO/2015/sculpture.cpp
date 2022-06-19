#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;

int n, A, B;
long pref[N];
bool C[N][N];

int main() {
    scanf("%d %d %d", &n, &A, &B);
    for (int i = 1; i <= n; i++)
        scanf("%lld", pref + i), pref[i] += pref[i - 1];

    if (A == 1) {
        long ans = 0;
        for (int b = 62; ~b; b--) {
            int dp[N];
            fill_n(dp, N, 1e9);
            dp[0] = 0;
            for (int i = 1; i <= n; i++)
                for (int j = i; j <= n; j++) {
                    long sum = pref[j] - pref[i - 1];
                    if (!(sum >> b & 1) &&
                        ((sum | ans) >> (b + 1)) == (ans >> (b + 1)))
                        dp[j] = min(dp[j], dp[i - 1] + 1);
                }
            if (dp[n] > B)
                ans |= 1ll << b;
        }
        printf("%lld\n", ans);
    } else {
        long ans = 0;
        for (int b = 62; ~b; b--) {
            memset(C, false, sizeof C);
            C[0][0] = true;
            for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                    for (int j = i; j <= n; j++) {
                        long sum = pref[j] - pref[i - 1];
                        if (!(sum >> b & 1) &&
                            ((sum | ans) >> (b + 1)) == (ans >> (b + 1)))
                            C[j][k] |= C[i - 1][k - 1];
                    }
            bool valid = false;
            for (int i = A; i <= B; i++)
                valid |= C[n][i];
            if (!valid)
                ans |= 1ll << b;
        }
        printf("%lld\n", ans);
    }

    return 0;
}