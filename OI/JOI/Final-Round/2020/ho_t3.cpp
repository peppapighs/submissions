#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 205;

int n, l, ans;
int x[N], t[N];
long L[N][N][N], R[N][N][N];

long d(int a, int b) { return min(abs(x[b] - x[a]), l - abs(x[b] - x[a])); }

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 1; i <= n; i++)
        scanf("%d", x + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", t + i);
    x[n + 1] = l;

    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = n + 1; j; j--) {
                if (j <= i || (!i && j == n + 1 && !k))
                    continue;

                L[k][i][j] = R[k][i][j] = 1e18;
                if (i)
                    L[k][i][j] = min({L[k][i][j], L[k][i - 1][j] + d(i - 1, i),
                                      R[k][i - 1][j] + d(j, i)});
                if (j <= n)
                    R[k][i][j] = min({R[k][i][j], L[k][i][j + 1] + d(i, j),
                                      R[k][i][j + 1] + d(j + 1, j)});

                if (k) {
                    long T;
                    if (i) {
                        T = min(L[k - 1][i - 1][j] + d(i - 1, i),
                                R[k - 1][i - 1][j] + d(j, i));
                        if (T <= t[i])
                            L[k][i][j] = min(L[k][i][j], T);
                    }
                    if (j <= n) {
                        T = min(L[k - 1][i][j + 1] + d(i, j),
                                R[k - 1][i][j + 1] + d(j + 1, j));
                        if (T <= t[j])
                            R[k][i][j] = min(R[k][i][j], T);
                    }
                }
                if (L[k][i][j] != 1e18 || R[k][i][j] != 1e18)
                    ans = max(ans, k);
            }
    printf("%d\n", ans);

    return 0;
}