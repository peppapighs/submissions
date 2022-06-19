#include <bits/stdc++.h>

#define pii pair<long long, long long>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;
const int M = 1e9 + 7;

int n, q;
long long A[N], w[N << 1], wa[N << 1];

void update(int x, long long k) {
    w[x + n] = k, wa[x + n] = (k * A[x]) % M;
    for (x += n; x != 1; x >>= 1) {
        w[x >> 1] = w[x] + w[x ^ 1];
        wa[x >> 1] = (wa[x] + wa[x ^ 1]) % M;
    }
}

long long query(int l, int r) {
    int ret = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = (ret + wa[l++]) % M;
        if (r & 1)
            ret = (ret + wa[--r]) % M;
    }
    return ret;
}

long long sum(int l, int r) {
    long long ret = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret += w[l++];
        if (r & 1)
            ret += w[--r];
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
        scanf("%lld", &A[i]), A[i] -= i;
    for (int i = 0; i < n; i++)
        scanf("%lld", &w[n + i]), wa[n + i] = (w[n + i] * A[i]) % M;
    for (int i = n - 1; i; i--) {
        w[i] = w[i << 1] + w[i << 1 | 1];
        wa[i] = (wa[i << 1] + wa[i << 1 | 1]) % M;
    }
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a < 0) {
            a = -a - 1;
            update(a, b);
        } else {
            --a, --b;
            long long k = sum(a, b) >> 1;
            int l = a, r = b;
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (sum(a, m - 1) <= k)
                    l = m;
                else
                    r = m - 1;
            }
            int left = query(a, l - 1), right = query(l + 1, b);
            long long sl = sum(a, l - 1), sr = sum(l + 1, b);
            long long lhs = (A[l] * sl) % M;
            lhs = (lhs - left + M) % M;
            long long rhs = right % M;
            rhs = (rhs - ((A[l] * sr) % M) + M) % M;
            printf("%lld\n", (lhs + rhs + M) % M);
        }
    }

    return 0;
}