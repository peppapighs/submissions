#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

long n, a, b, m;
map<pii, long> mp;

void print(const char *c, long x, long y) { printf(c, x, y), fflush(stdout); }

bool get(long x, long y) {
    if (x < 1 || x > n || y < 1 || y > n)
        return false;
    if (!mp.count(pii(x, y))) {
        char s[10];
        print("examine %lld %lld\n", x, y);
        scanf(" %s", s);
        mp[pii(x, y)] = (s[0] == 't');
    }
    return mp[pii(x, y)];
}

long find(long x, long y, long dx, long dy) {
    long d = 1;
    while (get(x + dx * d, y + dy * d))
        d <<= 1;
    long l = d >> 1, r = d;
    while (l < r) {
        long m = (l + r + 1) >> 1;
        if (get(a + dx * m, b + dy * m))
            l = m;
        else
            r = m - 1;
    }
    return l;
}

int main() {
    scanf("%lld %lld %lld", &n, &a, &b);
    long left = find(a, b, -1, 0), right = find(a, b, 1, 0);
    long up = find(a, b, 0, 1), down = find(a, b, 0, -1);
    m = right + left + 1;

    long xm = (2 * a + right - left) / 2, ym = (2 * b + up - down) / 2;

    while (get(xm - 2 * m, ym))
        xm -= 2 * m;
    while (get(xm, ym - 2 * m))
        ym -= 2 * m;
    while (get(xm - m, ym - m))
        xm -= m, ym -= m;

    long ax = xm + m * 2, ay = ym + m * 2;
    print("solution %lld %lld\n", ax, ay);

    return 0;
}
