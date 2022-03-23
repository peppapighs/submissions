#include <bits/stdc++.h>

#define long long long

using namespace std;

long gcd(long a, long b, long &s, long &t) {
    long ss = t = 0;
    long tt = s = 1;

    while(b) {
        long q = a / b, tmp = b;
        b = a % b, a = tmp;
        tmp = ss, ss = s - q * ss, s = tmp;
        tmp = tt, tt = t - q * tt, t = tmp;
    }

    return a;
}

long r, s, q;

void solve() {
    scanf("%lld %lld %lld", &r, &s, &q);
    long a, b;
    long g = gcd(r, -s, a, b);

    long lhs = a * q / g;
    long rhs = -b * q / g;
    long cl = s / g, cr = r / g;

    long bl = (long)ceil((double)-lhs / cl);
    long br = (long)ceil((double)rhs / cr);
    long k = min(bl, br) - 1;

    printf("%lld %lld\n", lhs + cl * k, rhs - cr * k);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}