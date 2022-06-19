#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e5 + 5;
const int M = 1e9 + 7;

long modpow(long a, long b) {
    if (b < 0)
        return 0;
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int n, cnt_q, cnt_o;
char S[N];

int main() {
    scanf(" %s", S + 1);
    n = strlen(S + 1);
    for (int i = 1; i <= n; i++) {
        if (S[i] == '?')
            ++cnt_q;
        if (S[i] == '1')
            ++cnt_o;
    }

    long ans = 0;
    for (int i = 1, a = 0, b = 0; i <= n; i++) {
        if (S[i] == '?') {
            ans = (ans + (modpow(2, cnt_q - 2) * a % M)) % M;
            ans = (ans + (modpow(2, cnt_q - 1) * b % M)) % M;
            ++a;
        } else if (S[i] == '0') {
            ans = (ans + (modpow(2, cnt_q - 1) * a % M)) % M;
            ans = (ans + (modpow(2, cnt_q) * b % M)) % M;
        } else
            ++b;
    }
    printf("%lld\n", ans);

    return 0;
}