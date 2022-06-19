#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1505;

int r, c;
int A[N][N];
long dp1[N][N], dp2[N][N], dp3[N][N], dp4[N][N], ans = 1e18;

int main() {
    fill_n(dp1[0], N * N, 1e18), fill_n(dp2[0], N * N, 1e18);
    fill_n(dp3[0], N * N, 1e18), fill_n(dp4[0], N * N, 1e18);

    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            scanf("%d", &A[i][j]);
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) {
            if (i == 1 && j == 1)
                dp1[i][j] = A[i][j];
            else
                dp1[i][j] = min(dp1[i - 1][j], dp1[i][j - 1]) + A[i][j];
        }
    for (int i = r; i; i--)
        for (int j = 1; j <= c; j++) {
            if (i == r && j == 1)
                dp2[i][j] = A[i][j];
            else
                dp2[i][j] = min(dp2[i + 1][j], dp2[i][j - 1]) + A[i][j];
        }
    for (int i = r; i; i--)
        for (int j = c; j; j--) {
            if (i == r && j == c)
                dp3[i][j] = A[i][j];
            else
                dp3[i][j] = min(dp3[i + 1][j], dp3[i][j + 1]) + A[i][j];
        }
    for (int i = 1; i <= r; i++)
        for (int j = c; j; j--) {
            if (i == 1 && j == c)
                dp4[i][j] = A[i][j];
            else
                dp4[i][j] = min(dp4[i - 1][j], dp4[i][j + 1]) + A[i][j];
        }
    ans = dp1[r][c] + dp2[1][c];
    for (int i = 1; i <= r; i++) {
        long mx = -1e18;
        vector<long> pref(c + 1);
        for (int j = 1; j <= c; j++)
            pref[j] = pref[j - 1] + A[i][j];
        for (int j = 1; j <= c; j++) {
            mx = max(mx, pref[j - 1] - dp1[i][j] - dp2[i][j] + 2ll * A[i][j]);
            ans =
                min(ans, dp3[i][j] + dp4[i][j] - 2ll * A[i][j] + pref[j] - mx);
        }
    }
    for (int i = 1; i <= c; i++) {
        long mx = -1e18;
        vector<long> pref(r + 1);
        for (int j = 1; j <= r; j++)
            pref[j] = pref[j - 1] + A[j][i];
        for (int j = 1; j <= r; j++) {
            mx = max(mx, pref[j - 1] - dp1[j][i] - dp4[j][i] + 2ll * A[j][i]);
            ans =
                min(ans, dp3[j][i] + dp2[j][i] - 2ll * A[j][i] + pref[j] - mx);
        }
    }
    printf("%lld\n", ans);

    return 0;
}