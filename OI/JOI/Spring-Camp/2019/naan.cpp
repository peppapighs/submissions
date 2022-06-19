#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;

struct Fraction {
    long x, y;
    Fraction() {}
    Fraction(long x, long y) : x(x), y(y) {}
    friend bool operator<(const Fraction &a, const Fraction &b) {
        if (a.x / a.y != b.x / b.y)
            return a.x / a.y < b.x / b.y;
        return (a.x % a.y) * b.y < (b.x % b.y) * a.y;
    }
} pos[N][N];

int n, m;
int ans[N], chk[N];
long v[N][N];

Fraction get_pos(int idx, long x, long y) {
    int l = 1, r = m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (v[idx][mid] * y > x)
            r = mid;
        else
            l = mid + 1;
    }
    x -= v[idx][r - 1] * y;
    y *= (v[idx][r] - v[idx][r - 1]);
    x += (r - 1) * y;
    return Fraction(x, y);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", v[i] + j);
            v[i][j] += v[i][j - 1];
        }
        for (int j = 1; j <= n; j++)
            pos[i][j] = get_pos(i, 1ll * j * v[i][m], n);
    }
    for (int i = 1; i <= n; i++) {
        int nex = -1;
        for (int j = 1; j <= n; j++)
            if (!chk[j] && (nex == -1 || pos[j][i] < pos[nex][i]))
                nex = j;
        ans[i] = nex, chk[nex] = 1;
        if (i < n)
            printf("%lld %lld\n", pos[nex][i].x, pos[nex][i].y);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}