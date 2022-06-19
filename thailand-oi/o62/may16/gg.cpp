#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const long INF = 1e18 + 1e16;

int comp(int p, long a, long b) {
    long half = 1ll << (p - 1);
    if (a < half && b < half)
        return 0;
    if (a < half && b >= half)
        return 1;
    if (a >= half && b >= half)
        return 2;
    if (a >= half && b < half)
        return 3;
}

pii f(int p, int c, long a, long b) {
    long sz = 1ll << (p - 1);
    if (c == 0)
        return pii(a, b);
    if (c == 1)
        return pii(a, b - sz);
    if (c == 2)
        return pii(a - sz, b - sz);
    if (c == 3)
        return pii(a - sz, b);
}

long solve(int p, long a, long b, long c, long d) {
    if (p == 1)
        return abs(a - c) + abs(b - d);

    long full = 1ll << p;
    if ((a == 0 || a == full - 1) && (b == 0 || b == full - 1) &&
        (c == 0 || c == full - 1) && (d == 0 || d == full - 1))
        return abs(a - c) + abs(b - d);

    int c1 = comp(p, a, b), c2 = comp(p, c, d);
    if (c1 > c2) {
        swap(c1, c2);
        swap(a, c), swap(b, d);
    }
    pii p1 = f(p, c1, a, b), p2 = f(p, c2, c, d);

    if (c1 == c2)
        return solve(p - 1, p1.x, p1.y, p2.x, p2.y);

    long sz = 1ll << (p - 1);
    if (c1 == 0 && c2 == 1)
        return solve(p - 1, p1.x, p1.y, 0, sz - 1) +
               solve(p - 1, p2.x, p2.y, 0, 0) + 1;
    if (c1 == 0 && c2 == 2) {
        long tmp = 1ll << p;
        long sa1 = solve(p - 1, p1.x, p1.y, 0, sz - 1),
             sa2 = solve(p - 1, p1.x, p1.y, sz - 1, 0);
        long sb1 = solve(p - 1, p2.x, p2.y, 0, sz - 1),
             sb2 = solve(p - 1, p2.x, p2.y, sz - 1, 0);
        return min(sa1 + sb1, sa2 + sb2) + tmp;
    }
    if (c1 == 0 && c2 == 3)
        return solve(p - 1, p1.x, p1.y, sz - 1, 0) +
               solve(p - 1, p2.x, p2.y, 0, 0) + 1;
    if (c1 == 1 && c2 == 2)
        return solve(p - 1, p1.x, p1.y, sz - 1, sz - 1) +
               solve(p - 1, p2.x, p2.y, 0, sz - 1) + 1;
    if (c1 == 1 && c2 == 3) {
        long tmp = 1ll << p;
        long sa1 = solve(p - 1, p1.x, p1.y, 0, 0),
             sa2 = solve(p - 1, p1.x, p1.y, sz - 1, sz - 1);
        long sb1 = solve(p - 1, p2.x, p2.y, 0, 0),
             sb2 = solve(p - 1, p2.x, p2.y, sz - 1, sz - 1);
        return min(sa1 + sb1, sa2 + sb2) + tmp;
    }
    if (c1 == 2 && c2 == 3)
        return solve(p - 1, p1.x, p1.y, sz - 1, 0) +
               solve(p - 1, p2.x, p2.y, sz - 1, sz - 1) + 1;
}

int k;
long a, b, c, d;

int main() {
    scanf("%d %lld %lld %lld %lld", &k, &a, &b, &c, &d);
    printf("%lld\n", solve(k, a, b, c, d));

    return 0;
}