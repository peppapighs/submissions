#include <bits/stdc++.h>

#define long long long

using namespace std;

long count_coprime(long a, long b) {
    if(a == 0) return 0;
    if(a == 1) return b;

    long cnt = 0;
    vector<int> fac;
    for(int i = 2; i * i <= a; i++) if(a % i == 0) {
        fac.emplace_back(i);
        while(a % i == 0) a /= i;
    }
    if(a != 1) fac.emplace_back(a);

    int n = fac.size();
    for(int i = 1; i < (1 << n); i++) {
        int mul = __builtin_popcount(i) & 1 ? 1 : -1;
        int cur = 1;
        for(int j = 0; j < n; j++) if(i >> j & 1)
            cur *= fac[j];
        cnt += mul * b / cur;
    }
    return b - cnt;
}

int A, B;
long L, ans1, ans2, ans3;

int main() {
    scanf("%d %d %lld", &A, &B, &L);
    for(int i = -A; i <= B; i++) {
        int d_a = i + A, d_b = B - i;
        long co_a = count_coprime(d_a, L);
        long co_b = count_coprime(d_b, L);
        long co_ab = count_coprime(1ll * d_a * d_b, L);

        ans1 += L - (co_a + co_b - co_ab);
        ans2 += co_a + co_b - 2ll * co_ab;
        ans3 += co_ab;
    }

    ans2 -= 2, ans3 += 2;
    printf("%lld\n%lld\n%lld", ans1, ans2, ans3);

    return 0;
}