#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>

using namespace std;

const int N = 4e3 + 5;
const int M = 65;

int n, A[N];
int dp_l[N][2 * M][M], dp_r[N][2 * M][M];

int solve_r(int l, int d, int k);

// d = (n - r) - (l - 1)

int solve_l(int l, int d, int k) {
    int r = (n - d) - (l - 1);
    if (r - l + 1 < k)
        return 0;
    if (~dp_l[l][M + d][k])
        return dp_l[l][M + d][k];

    int now = solve_r(l + k, d - k, k) + A[l + k - 1] - A[l - 1];
    if (r - l + 1 >= k + 1)
        now = max(now,
                  solve_r(l + k + 1, d - k - 1, k + 1) + A[l + k] - A[l - 1]);
    return dp_l[l][M + d][k] = now;
}

int solve_r(int l, int d, int k) {
    int r = (n - d) - (l - 1);
    if (r - l + 1 < k)
        return 0;
    if (~dp_r[l][M + d][k])
        return dp_r[l][M + d][k];

    int now = solve_l(l, d + k, k) - A[r] + A[r - k];
    if (r - l + 1 >= k + 1)
        now = min(now, solve_l(l, d + k + 1, k + 1) - A[r] + A[r - k - 1]);
    return dp_r[l][M + d][k] = now;
}

int main() {
    memset(dp_l, -1, sizeof dp_l), memset(dp_r, -1, sizeof dp_r);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        A[i] += A[i - 1];
    }
    printf("%d\n", solve_l(1, 0, 1));

    return 0;
}