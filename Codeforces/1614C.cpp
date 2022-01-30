#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;
const int M = 1e9 + 7;

int n, m;

void solve() {
    scanf("%d %d", &n, &m);
    int total = 0;
    long pow2 = 1;
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        total |= c;
    }
    for(int i = 1; i < n; i++) pow2 = pow2 * 2 % M;
    printf("%lld\n", pow2 * total % M);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}