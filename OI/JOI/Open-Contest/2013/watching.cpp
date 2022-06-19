#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;

int n, p, q;
int pos[N], dp[N][N];

bool f(int mid) {
    fill_n(dp[0], N * N, 1e9);

    int l1 = 1, l2 = 1;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        while (pos[i] - pos[l1] >= mid)
            ++l1;
        while (pos[i] - pos[l2] >= 2 * mid)
            ++l2;

        for (int j = 0; j <= n; j++) {
            dp[i][j] = dp[l2 - 1][j] + 1;
            if (j)
                dp[i][j] = min(dp[i][j], dp[l1 - 1][j - 1]);
        }
    }
    for (int i = 0; i <= p; i++)
        if (dp[n][i] <= q)
            return true;
    return false;
}

int main() {
    scanf("%d %d %d", &n, &p, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", pos + i);
    sort(pos + 1, pos + 1 + n);

    int l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", r);

    return 0;
}