#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6+5;
const int M = 1e6+3;

long modpow(long a, long b) {
        long ret = 1;
        for( ; b; b >>= 1) {
                if(b & 1) ret = (ret * a) % M;
                a = (a * a) % M;
        }
        return ret;
}

int a, b;
long fact[N];

int main() {
        fact[0] = 1;
        for(int i = 1; i < N; i++) fact[i] = (fact[i-1] * i) % M;
        scanf("%d %d", &a, &b);
        long ans = (fact[a] * modpow(fact[b], M-2)) % M;
        ans = (ans * modpow(fact[a-b], M-2)) % M;
        printf("%lld\n", ans);

        return 0;
}
