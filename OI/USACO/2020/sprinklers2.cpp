#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;
const int M = 1e9 + 7;

int n;
long d2 = 5e8 + 4, ans;
long dp_c[N][N], dp_a[N][N];
char A[N][N];

long solve_a(int r, int c);

long solve_c(int r, int c) {
    if (r == n + 1 || c == n + 1)
        return c != n + 1;
    if (~dp_c[r][c])
        return dp_c[r][c];
    long &now = dp_c[r][c];
    now = 0;
    if (A[r][c] == '.')
        now = (now + solve_a(r, c + 1) * d2) % M;
    now = (now + solve_c(r, c + 1)) % M;
    return now;
}

long solve_a(int r, int c) {
    if (r == n + 1 || c == n + 1)
        return r != n + 1;
    if (~dp_a[r][c])
        return dp_a[r][c];
    long &now = dp_a[r][c];
    now = 0;
    if (A[r][c] == '.')
        now = (now + solve_c(r + 1, c) * d2) % M;
    now = (now + solve_a(r + 1, c)) % M;
    return now;
}

int main() {
    freopen("sprinklers2.in", "r", stdin);
    freopen("sprinklers2.out", "w", stdout);

    memset(dp_c, -1, sizeof dp_c), memset(dp_a, -1, sizeof dp_a);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf(" %s", A[i] + 1);

    ans = solve_a(1, 1);
    for (int i = 2; i <= n + 1; i++)
        if (A[1][i - 1] == '.')
            ans = (ans + solve_a(1, i) * d2 % M) % M;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (A[i][j] == '.')
                ans = (ans * 2) % M;
    printf("%lld\n", ans);

    return 0;
}