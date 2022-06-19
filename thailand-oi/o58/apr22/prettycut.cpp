#include <bits/stdc++.h>

using namespace std;

const int N = 355;
const int M = 7919;

int W, L, K, dp[N][N][2]; // 0 - horizontal cut, 1 - vertical cut

int solve(int r, int c, int md) {
    if (r == 1 && c == 1)
        return 1;
    int &now = dp[r][c][md];
    if (~now)
        return now;

    now = 0;
    if (r == 1) {
        if (!md)
            return 0;
        if (c <= K)
            ++now;
        for (int i = 0; i <= c - 2 && i <= 2 * K; i++)
            now += min(i, K) - max(i - K, 0) + 1;
    } else if (c == 1) {
        if (md)
            return 0;
        if (r <= K)
            ++now;
        for (int i = 0; i <= r - 2 && i <= 2 * K; i++)
            now += min(i, K) - max(i - K, 0) + 1;
    } else {
        if (!md) {
            for (int i = 1; i <= r - 1 && i <= 2 * K; i++)
                now += (min(i, K) - max(i - K, 0) + 1) *
                       (solve(r - i, c, md ^ 1) - (i == r - 1) + M) % M;
            if (r <= K)
                ++now;
        } else {
            for (int i = 1; i <= c - 1 && i <= 2 * K; i++)
                now += (min(i, K) - max(i - K, 0) + 1) *
                       (solve(r, c - i, md ^ 1) - (i == c - 1) + M) % M;
            if (c <= K)
                ++now;
        }
    }
    return now = (now + M) % M;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %d %d", &W, &L, &K);
    if (W == 1 && L == 1)
        printf("1\n");
    else
        printf("%d\n", (solve(W, L, 0) + solve(W, L, 1)) % M);

    return 0;
}