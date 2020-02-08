#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e3+5;

int n, M;
long fac[N], inv[N], dp[N][N];

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

long ncr(int a, int b) {
    if(a < b) return 0;
    return fac[a] * inv[b] % M * inv[a - b] % M;
}

int main() {
    scanf("%d %d", &n, &M);

    for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) {
        if(i == 0 && j == 0) dp[i][j] = 1;
        else {
            if(i && j) dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % M;
            if(i) dp[i][j] = (dp[i][j] + dp[i-1][j] * (j + 1) % M) % M;
        }
    }

    fac[0] = inv[0] = 1;
    for(int i = 1; i < N; i++) {
        fac[i] = fac[i-1] * i % M;
        inv[i] = modpow(fac[i], M - 2);
    }

    long ans = 0;
    for(int i = 0; i <= n; i++) {
        long add = 0;

        long mul = modpow(2, n - i), k = 1;
        for(int j = 0; j <= i; j++) {
            add = (add + dp[i][j] * k % M) % M;
            k = k * mul % M;
        }
        long p = 2;
        for(int j = 1; j <= n - i; j++) p = p * p % M;
        add = add * ncr(n, i) % M * p % M;

        if(i & 1) ans = (ans - add + M) % M;
        else ans = (ans + add) % M;
    }
    printf("%lld\n", ans);

    return 0;
}