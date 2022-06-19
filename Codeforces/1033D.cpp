#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 505;
const int M = 998244353;

int n;
long A[N];
map<long, long> mp, dup;

long find_sqrt(long x) {
    long l = 0, r = 2e9;
    while (l < r) {
        long m = (l + r + 1) >> 1;
        if (m * m <= x)
            l = m;
        else
            r = m - 1;
    }
    return l;
}

long find_cbrt(long x) {
    long l = 0, r = 2e6;
    while (l < r) {
        long m = (l + r + 1) >> 1;
        if (m * m * m <= x)
            l = m;
        else
            r = m - 1;
    }
    return l;
}

long find_qdrt(long x) {
    long l = 0, r = 4e4;
    while (l < r) {
        long m = (l + r + 1) >> 1;
        if (m * m * m * m <= x)
            l = m;
        else
            r = m - 1;
    }
    return l;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i);
    for (int i = 1; i <= n; i++) {
        long a = find_sqrt(A[i]), b = find_cbrt(A[i]), c = find_qdrt(A[i]);
        if (c * c * c * c == A[i])
            mp[c] += 4;
        else if (b * b * b == A[i])
            mp[b] += 3;
        else if (a * a == A[i])
            mp[a] += 2;
        else {
            bool valid = false;
            for (int j = 1; j <= n; j++) {
                long g = __gcd(A[i], A[j]);
                if (g == 1 || g == A[i])
                    continue;
                mp[g]++, mp[A[i] / g]++;
                valid = true;
                break;
            }
            if (!valid)
                dup[A[i]]++;
        }
    }
    long ans = 1LL;
    for (auto p : mp)
        ans = (ans * (p.y + 1)) % M;
    for (auto p : dup)
        ans = (ans * (p.y + 1) * (p.y + 1)) % M;
    printf("%lld\n", ans);

    return 0;
}
