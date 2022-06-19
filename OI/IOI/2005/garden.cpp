#include <bits/stdc++.h>

using namespace std;

const int N = 255;

int W, H, n, K;
int A[N][N], mnr[N], mnc[N];

int rect(int x1, int x2, int y1, int y2) {
    return A[x2][y2] - A[x1 - 1][y2] - A[x2][y1 - 1] + A[x1 - 1][y1 - 1];
}

int main() {
    fill_n(mnr, N, 1e9), fill_n(mnc, N, 1e9);

    scanf("%d %d %d %d", &W, &H, &n, &K);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        ++A[b][a];
    }
    for (int i = 1; i <= H; i++)
        for (int j = 1; j <= W; j++)
            A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    for (int i = 1; i <= H; i++)
        for (int j = 1; j <= W; j++)
            for (int k = i; k; k--) {
                int l = 1, r = j;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (rect(k, i, mid, j) >= K)
                        l = mid;
                    else
                        r = mid - 1;
                }
                if (rect(k, i, l, j) == K) {
                    mnr[i] = min(mnr[i], 2 * (i - k + 1 + j - l + 1));
                    mnc[j] = min(mnc[j], 2 * (i - k + 1 + j - l + 1));
                }
            }
    for (int i = 1; i <= H; i++)
        mnr[i] = min(mnr[i], mnr[i - 1]);
    for (int i = 1; i <= W; i++)
        mnc[i] = min(mnc[i], mnc[i - 1]);

    int ans = 1e9;
    for (int i = H; i; i--)
        for (int j = W; j; j--)
            for (int k = i; k <= H; k++) {
                int l = j, r = W;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (rect(i, k, j, mid) >= K)
                        r = mid;
                    else
                        l = mid + 1;
                }
                if (rect(i, k, j, r) == K) {
                    ans = min(ans, mnr[i - 1] + 2 * (k - i + 1 + r - j + 1));
                    ans = min(ans, mnc[j - 1] + 2 * (k - i + 1 + r - j + 1));
                }
            }
    if (ans == 1e9)
        printf("NO\n");
    else
        printf("%d\n", ans);

    return 0;
}