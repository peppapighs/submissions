#include <bits/stdc++.h>

using namespace std;

const int M = 10007;

int T;

int n, m;
int a[15], b[15], expo[13];
int dp[13][600005];

int main() {
    scanf("%d", &T);
    a[0] = b[0] = -1;
    while (T--) {
        scanf("%d %d", &n, &m);

        expo[0] = 1;
        for (int i = 1; i <= m; i++) {
            scanf("%d %d", a + i, b + i);
            expo[i] = expo[i - 1] * 3;
        }

        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= m; i++)
            dp[i][expo[i - 1]] = 1;
        for (int mask = 0; mask < expo[m]; mask++) {
            for (int last = 1; last <= m; last++) {
                for (int i = 1; i <= m; i++) {
                    if (a[i] == a[last] || a[i] == b[last] || b[i] == a[last] ||
                        b[i] == b[last])
                        continue;
                    if ((mask / expo[i - 1]) % 3 == 2)
                        continue;
                    dp[i][mask + expo[i - 1]] =
                        (dp[i][mask + expo[i - 1]] + dp[last][mask]) % M;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++)
            ans = (ans + dp[i][expo[m] - 1]) % M;
        printf("%d\n", ans);
    }

    return 0;
}