#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

int n, dp[N][N][2];
vector<int> V;

int solve(int l, int r, int right) {
    int &now = dp[l][r][right];
    if (~now)
        return now;
    if (l >= r)
        return 0;
    if (right)
        now = min(solve(l, r - 1, 0), solve(l, r - 1, 1)) + 1;
    else
        now = min(solve(l + 1, r, 0), solve(l + 1, r, 1)) + 1;
    if (V[l] == V[r])
        now = min(now, min(solve(l + 1, r - 1, 0), solve(l + 1, r - 1, 1)) + 1);
    return now;
}

int main() {
    fill_n(dp[0][0], N * N * 2, -1);
    scanf("%d", &n);
    V.emplace_back(0);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if (a != V.back())
            V.emplace_back(a);
    }
    n = V.size() - 1;
    printf("%d\n", min(solve(1, n, 0), solve(1, n, 1)));

    return 0;
}