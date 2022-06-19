#include <bits/stdc++.h>

using namespace std;

const int N = 35;

int l, w, m;
int A[N][N], dp[N][N][N][N];
int cnt[N * N], win[N * N], alive;
int rig[N][N][N], dwn[N][N][N];

int add(int i, int j) {
    ++win[A[i][j]];
    if (win[A[i][j]] == cnt[A[i][j]])
        ++alive;
    return alive;
}

int del(int i, int j) {
    if (win[A[i][j]] == cnt[A[i][j]])
        --alive;
    --win[A[i][j]];
    return alive;
}

int solve(int r, int c, int L, int W) {
    if (L == 0 || W == 0)
        return 0;
    int &ret = dp[r][c][L][W];
    if (~ret)
        return ret;
    ret = 0;
    ret = max(ret, solve(r, c, L, W - 1) + dwn[r][c + W - 1][L]);
    ret = max(ret, solve(r, c + 1, L, W - 1) + dwn[r][c][L]);
    ret = max(ret, solve(r, c, L - 1, W) + rig[r + L - 1][c][W]);
    ret = max(ret, solve(r + 1, c, L - 1, W) + rig[r][c][W]);
    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d %d %d", &l, &w, &m);
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= w; j++) {
            scanf("%d", &A[i][j]);
            ++cnt[A[i][j]];
        }
    for (int len = 1; len <= w; len++)
        for (int i = 1; i <= l; i++) {
            memset(win, 0, sizeof win), alive = 0;
            for (int j = 1; j <= len; j++)
                add(i, j);
            rig[i][1][len] = alive;
            for (int j = len + 1; j <= w; j++) {
                add(i, j);
                rig[i][j - len + 1][len] = del(i, j - len);
            }
        }
    for (int len = 1; len <= l; len++)
        for (int j = 1; j <= w; j++) {
            memset(win, 0, sizeof win), alive = 0;
            for (int i = 1; i <= len; i++)
                add(i, j);
            dwn[1][j][len] = alive;
            for (int i = len + 1; i <= l; i++) {
                add(i, j);
                dwn[i - len + 1][j][len] = del(i - len, j);
            }
        }
    printf("%d\n", solve(1, 1, l, w));

    return 0;
}