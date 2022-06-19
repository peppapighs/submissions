#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int sieve[N], fact[N], a;

void solve() {
    int a, b, c, d;
    int r1 = 0, r2 = 0, fac = 0;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = 2; i <= N; i++) {
        int n1 = b - (b % i), n2 = d - (d % i);
        if (n1 < a || n2 < c)
            continue;
        if (fact[i] > fac) {
            fac = fact[i];
            r1 = n1;
            r2 = n2;
        } else if (fact[i] == fac) {
            if (r1 + r2 < n1 + n2) {
                r1 = n1;
                r2 = n2;
            } else if (r1 + r2 == n1 + n2 && n1 > r1) {
                r1 = n1;
                r2 = n2;
            }
        }
    }

    printf("%d %d\n", r1, r2);
}

int main() {
    for (int i = 2; i <= N; i++) {
        if (!sieve[i]) {
            fact[i] = 1;
            for (int j = i + i; j <= N; j += i)
                sieve[j] = i;
        }
    }
    for (int i = 4; i <= N; i++)
        if (sieve[i])
            fact[i] = fact[i / sieve[i]] + 1;

    solve();

    return 0;
}