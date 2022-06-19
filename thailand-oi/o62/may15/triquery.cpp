#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 4e3 + 5;

int n, m;
int r[N][N], c[N][N], a[N][N];
long t1[N][N], t2[N][N];

void update(long t[N][N], int x, int y, int k) {
    for (int i = x + 1; i < N; i += i & -i)
        for (int j = y + 1; j < N; j += j & -j)
            t[i][j] += k;
}

long query(long t[N][N], int x, int y, long ret = 0) {
    for (int i = x + 1; i; i -= i & -i)
        for (int j = y + 1; j; j -= j & -j)
            ret += t[i][j];
    return ret;
}

long rect1(int x1, int y1, int x2, int y2) {
    return query(t1, x2, y2) - query(t1, x1 - 1, y2) - query(t1, x2, y1 - 1) +
           query(t1, x1 - 1, y1 - 1);
}

long rect2(int x1, int y1, int x2, int y2) {
    return query(t2, x2, y2) - query(t2, x1 - 1, y2) - query(t2, x2, y1 - 1) +
           query(t2, x1 - 1, y1 - 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int sum = 2; sum <= 2 * n; sum++)
        for (int i = 1; i < sum && i <= n; i++) {
            if (sum - i < 1 || sum - i > n)
                continue;
            r[i][sum - i] = sum - 1;
            c[i][sum - i] = n - i + 1;
        }
    for (int i = 1, t, x, y, k; i <= m; i++) {
        scanf("%d %d %d %d", &t, &x, &y, &k);
        if (t == 1) {
            int x1 = x, y1 = y - k + 1, x2 = x - k + 1, y2 = y;

            long ans = rect1(r[x1][y1], c[x1][y1], r[x2][y2], c[x2][y2]) / 2;
            if (k > 1) {
                ans += rect1(r[x1][y1 + 1], c[x1][y1 + 1], 2 * n - 1,
                             c[x2 + 1][y2]);
                ans -= rect2(x2 + 1, y + 1, x, n);
            }

            printf("%lld\n", ans);
        } else {
            update(t1, r[x][y], c[x][y], k - a[x][y]);
            update(t2, x, y, k - a[x][y]);
            a[x][y] = k;
        }
    }

    return 0;
}