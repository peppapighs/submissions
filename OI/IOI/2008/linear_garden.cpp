#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n, m, mx[N], mn[N], cur[N];
long dp[2][3][3][5], ans = 1;
char A[N];

int main() {
    scanf("%d %d", &n, &m);
    scanf(" %s", A + 1);
    for (int i = 1; i <= n; i++) {
        mx[i] = mx[i - 1], mn[i] = mn[i - 1], cur[i] = cur[i - 1];
        if (A[i] == 'L')
            ++cur[i];
        else
            --cur[i];
        mx[i] = max(mx[i], cur[i]), mn[i] = min(mn[i], cur[i]);
    }
    for (int i = n; i; i--) {
        int now = i & 1, pre = now ^ 1;
        for (int a = 0; a <= 2; a++)
            for (int b = -2; b <= 0; b++)
                for (int x = -2; x <= 2; x++) {
                    dp[now][a][2 + b][2 + x] = 0;
                    if (a - b > 2 || x < b || x > a)
                        continue;
                    if (i == n)
                        dp[now][a][2 + b][2 + x] = 1;
                    else {
                        if (x < 2 && max(a, x + 1) - b <= 2)
                            dp[now][a][2 + b][2 + x] +=
                                dp[pre][max(a, x + 1)][2 + b][3 + x];
                        if (x > -2 && a - min(b, x - 1) <= 2)
                            dp[now][a][2 + b][2 + x] +=
                                dp[pre][a][2 + min(b, x - 1)][1 + x];
                        dp[now][a][2 + b][2 + x] %= m;
                    }
                }
        if (A[i] == 'P') {
            int x = cur[i - 1] + 1, a = max(mx[i - 1], x),
                b = min(mn[i - 1], x);
            if (x <= 2 && a - b <= 2) {
                if (i == n)
                    ++ans;
                else
                    ans += dp[now][a][2 + b][2 + x];
                ans %= m;
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}