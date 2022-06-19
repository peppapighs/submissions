#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, m, ans = -1e9;
int A[N][N], row[N][N], col[N][N];
int drow[N][N][N], dcol[N][N][N];

int main() {
    fill_n(drow[0][0], N * N * N, -1e9);
    fill_n(dcol[0][0], N * N * N, -1e9);

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &A[i][j]);
            row[i][j] = col[i][j] = A[i][j];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            row[i][j] += row[i][j - 1];
            col[i][j] += col[i - 1][j];
        }
    for (int len = 1; len <= n; len++)
        for (int i = len, j = 1; i <= n; i++, j++) {
            int mx = 0;
            for (int k = 1; k <= m; k++) {
                mx += col[i][k] - col[j - 1][k];
                drow[i][j][k] = max(
                    {drow[i][j][k - 1], drow[i - 1][j][k], drow[i][j + 1][k]});
                drow[i][j][k] = max(drow[i][j][k], mx);
                if (mx < 0)
                    mx = 0;
            }
            mx = 0;
            for (int k = m; k > 2; k--) {
                mx += col[i][k] - col[j - 1][k];
                ans = max(ans, mx + drow[i][j][k - 2]);
                if (mx < 0)
                    mx = 0;
            }
        }
    for (int len = 1; len <= m; len++)
        for (int i = len, j = 1; i <= m; i++, j++) {
            int mx = 0;
            for (int k = 1; k <= n; k++) {
                mx += row[k][i] - row[k][j - 1];
                dcol[i][j][k] = max(
                    {dcol[i][j][k - 1], dcol[i - 1][j][k], dcol[i][j + 1][k]});
                dcol[i][j][k] = max(dcol[i][j][k], mx);
                if (mx < 0)
                    mx = 0;
            }
            mx = 0;
            for (int k = n; k > 2; k--) {
                mx += row[k][i] - row[k][j - 1];
                ans = max(ans, mx + dcol[i][j][k - 2]);
                if (mx < 0)
                    mx = 0;
            }
        }

    fill_n(drow[0][0], N * N * N, -1e9);
    fill_n(dcol[0][0], N * N * N, -1e9);

    for (int len = 1; len <= n; len++)
        for (int i = len, j = 1; i <= n; i++, j++) {
            int mx = 0;
            for (int k = m; k; k--) {
                mx += col[i][k] - col[j - 1][k];
                drow[i][j][k] = max(
                    {drow[i][j][k + 1], drow[i - 1][j][k], drow[i][j + 1][k]});
                drow[i][j][k] = max(drow[i][j][k], mx);
                if (mx < 0)
                    mx = 0;
            }
            mx = 0;
            for (int k = 1; k <= m - 2; k++) {
                mx += col[i][k] - col[j - 1][k];
                ans = max(ans, mx + drow[i][j][k + 2]);
                if (mx < 0)
                    mx = 0;
            }
        }
    for (int len = 1; len <= m; len++)
        for (int i = len, j = 1; i <= m; i++, j++) {
            int mx = 0;
            for (int k = n; k; k--) {
                mx += row[k][i] - row[k][j - 1];
                dcol[i][j][k] = max(
                    {dcol[i][j][k + 1], dcol[i - 1][j][k], dcol[i][j + 1][k]});
                dcol[i][j][k] = max(dcol[i][j][k], mx);
                if (mx < 0)
                    mx = 0;
            }
            mx = 0;
            for (int k = 1; k <= n - 2; k++) {
                mx += row[k][i] - row[k][j - 1];
                ans = max(ans, mx + dcol[i][j][k + 2]);
                if (mx < 0)
                    mx = 0;
            }
        }
    printf("%d\n", ans);

    return 0;
}