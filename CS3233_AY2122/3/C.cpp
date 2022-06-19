#include <bits/stdc++.h>

#define long long long

using namespace std;

const int ZIGZAG = 830169;

long n, k;
int zig[830170], up[830170];
unordered_map<long, int> upper, lower;

long f(int dg, int m) { return (long)1e7 * dg + m; }

void clear() {
    upper.clear();
    lower.clear();
}

int solve() {
    long cnt = 0;

    scanf("%lld %lld", &n, &k);
    if (n >= (long)1e7) {
        for (long i = n; i <= (long)1e14; i += n) {
            long x = i;
            if (x % 10 == (x / 10) % 10)
                continue;
            int bruh = (x % 10 < (x / 10) % 10);
            bool valid = true;
            for (; x; x /= 10) {
                int a = x % 10, b = (x / 10) % 10;
                if (x / 10 == 0)
                    continue;
                if ((bruh && a > b) || (!bruh && a < b) || a == b) {
                    valid = false;
                    break;
                }
                bruh ^= 1;
            }
            if (valid) {
                ++cnt;
                if (cnt == k) {
                    clear();
                    return !printf("%lld\n", i);
                }
            }
        }
    }

    cnt = 0;
    for (int i = 1; i <= ZIGZAG; i++) {
        if (zig[i] % n == 0) {
            ++cnt;
            if (cnt == k) {
                clear();
                return !printf("%d\n", zig[i]);
            }
        }
        if (zig[i] >= (int)1e5) {
            int dg = zig[i] / (int)1e6;
            if (dg == 0 && up[i] != 1)
                continue;

            if (up[i])
                ++upper[f(dg, zig[i] % n)];
            else
                ++lower[f(dg, zig[i] % n)];
        }
    }

    for (int i = 1; i <= ZIGZAG; i++) {
        int m = (n - ((long)1e7 * zig[i] % n)) % n;
        int last = zig[i] % 10;

        for (int j = (up[i] == 1 ? last + 1 : 0);
             j <= (up[i] == 0 ? last - 1 : 9); j++) {
            if (j == last)
                continue;

            int sum = 0,
                stat = (up[i] == 1 || (up[i] == -1 && j > last)) ? 0 : 1;
            if (!stat)
                sum += lower[f(j, m)];
            else
                sum += upper[f(j, m)];

            if (cnt < k && k <= cnt + sum) {
                for (int ans = 1; ans <= ZIGZAG; ans++)
                    if (zig[ans] >= 1e5) {
                        if (zig[ans] / (int)1e6 != j || zig[ans] % n != m ||
                            up[ans] != stat)
                            continue;
                        ++cnt;
                        if (cnt == k) {
                            clear();
                            return !printf("%lld\n",
                                           (long)1e7 * zig[i] + zig[ans]);
                        }
                    }
            } else
                cnt += sum;
        }
    }

    return 0;
}

int T;

int main() {
    memset(up, -1, sizeof up);

    int ptr = 0;
    for (int i = 1; i < 1e7; i++) {
        long x = i;
        if (x < 10)
            zig[++ptr] = i;
        else {
            if (x % 10 == (x / 10) % 10)
                continue;
            int bruh = (x % 10 < (x / 10) % 10);
            bool valid = true;
            for (; x; x /= 10) {
                int a = x % 10, b = (x / 10) % 10;
                if (x / 10 == 0)
                    continue;
                if ((bruh && a > b) || (!bruh && a < b) || a == b) {
                    valid = false;
                    break;
                }
                bruh ^= 1;
            }
            if (valid) {
                zig[++ptr] = i;
                up[ptr] = (i % 10 < (i / 10) % 10);
            }
        }
    }

    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}