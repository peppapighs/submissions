#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e5 + 5;
const int M = 998244353;

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int n;
long dp[N][2];

void solve() {
    scanf("%d", &n);

    dp[0][0] = 1;
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if(a > 0) dp[a - 1][1] = (2ll * dp[a - 1][1] + dp[a - 1][0]) % M;
        dp[a + 1][0] = (dp[a][0] + 2ll * dp[a + 1][0]) % M;
        dp[a + 1][1] = 2ll * dp[a + 1][1] % M;
    }
    long ans = M - 1;
    for(int i = 0; i <= n + 1; i++) ans = (ans + dp[i][0] + dp[i][1]) % M;
    printf("%lld\n", ans);

    // clean up
    for(int i = 0; i <= n + 1; i++) dp[i][0] = dp[i][1] = 0;
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}