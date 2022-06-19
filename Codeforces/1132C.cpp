#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e3 + 5;

int n, q, ans;
int dp[N], cnt[N];
pii A[N], a1(1e9, -1), a2(1e9, -1);

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &A[i].x, &A[i].y);
        dp[A[i].x]++, dp[A[i].y + 1]--;
    }
    for (int i = 1; i <= n; i++)
        dp[i] += dp[i - 1];
    for (int i = 1; i <= q; i++)
        for (int j = A[i].x; j <= A[i].y; j++)
            if (dp[j] == 1)
                cnt[i]++;
    for (int i = 1; i <= q; i++)
        a1 = min(a1, pii(cnt[i], i));
    memset(dp, 0, sizeof dp), memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= q; i++)
        if (i != a1.y)
            dp[A[i].x]++, dp[A[i].y + 1]--;
    for (int i = 1; i <= n; i++)
        dp[i] += dp[i - 1];
    for (int i = 1; i <= q; i++)
        if (i != a1.y)
            for (int j = A[i].x; j <= A[i].y; j++)
                if (dp[j] == 1)
                    cnt[i]++;
    for (int i = 1; i <= q; i++)
        if (i != a1.y)
            a2 = min(a2, pii(cnt[i], i));
    for (int i = A[a2.y].x; i <= A[a2.y].y; i++)
        --dp[i];
    for (int i = 1; i <= n; i++)
        ans += !!dp[i];
    printf("%d\n", ans);

    return 0;
}
