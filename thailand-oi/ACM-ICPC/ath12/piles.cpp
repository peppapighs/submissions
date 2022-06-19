#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int M = 9871;

int T;
int n, k;
int dp[N][N], fact[N];

int modpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

int ncr(int a, int b) {
    int ret = (fact[a] * modpow(fact[b], M - 2)) % M;
    return (ret * modpow(fact[a - b], M - 2)) % M;
}

int solve(int left, int mn) {
    if (left == 0)
        return 1;
    if (left < mn)
        return 0;
    int &ret = dp[left][mn];
    if (~ret)
        return ret;
    ret = 0;
    for (int i = mn; i <= left; i++)
        for (int j = 1; i * j <= left; j++) {
            int up = fact[left];
            int dwn = (modpow(fact[i], j) * fact[j]) % M;
            dwn = (dwn * fact[left - i * j]) % M;
            int mul = (up * modpow(dwn, M - 2)) % M;
            int tmp = (mul * solve(left - i * j, i + 1)) % M;
            ret = (ret + tmp) % M;
        }
    return ret;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = (fact[i - 1] * i) % M;
    memset(dp, -1, sizeof dp);
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        printf("%d\n", solve(n, k));
    }

    return 0;
}