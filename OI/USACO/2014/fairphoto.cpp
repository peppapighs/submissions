#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, k, ans = -1;
int pre[N][8], suf[N][8], qs[N][8];
pii cow[N];

int main() {
    freopen("fairphoto.in", "r", stdin);
    freopen("fairphoto.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &cow[i].x, &cow[i].y);
        --cow[i].y;
    }
    sort(cow + 1, cow + n + 1);
    for (int i = 1; i <= n; i++) {
        ++qs[i][cow[i].y];
        for (int j = 0; j < 8; j++)
            qs[i][j] += qs[i - 1][j];
    }

    for (int i = 1; i <= n; i++) {
        pre[i][0] = 1 << cow[i].y;
        for (int j = 1; j < 8; j++) {
            if (pre[i - 1][j] >> cow[i].y & 1)
                pre[i][j] = pre[i - 1][j];
            else
                pre[i][j] = pre[i - 1][j - 1] + (1 << cow[i].y);
        }
    }
    for (int i = n; i; i--) {
        suf[i][0] = 1 << cow[i].y;
        for (int j = 1; j < 8; j++) {
            if (suf[i + 1][j] >> cow[i].y & 1)
                suf[i][j] = suf[i + 1][j];
            else
                suf[i][j] = suf[i + 1][j - 1] + (1 << cow[i].y);
        }
    }
    for (int j = k - 1; j < 8; j++) {
        vector<int> dp(9);
        map<vector<int>, int> mp;

        for (int i = n; i; i--) {
            int base = -1;
            int bit = dp[8] = suf[i][j];
            if (__builtin_popcount(bit) <= j)
                continue;
            for (int k = 0; k < 8; k++) {
                if (bit >> k & 1) {
                    if (base == -1)
                        base = qs[i - 1][k];
                    dp[k] = qs[i - 1][k] - base;
                } else
                    dp[k] = qs[i - 1][k];
            }
            mp[dp] = cow[i].x;
        }

        for (int i = 1; i <= n; i++) {
            int base = -1;
            int bit = dp[8] = pre[i][j];
            if (__builtin_popcount(bit) <= j)
                continue;
            for (int k = 0; k < 8; k++) {
                if (bit >> k & 1) {
                    if (base == -1)
                        base = qs[i][k];
                    dp[k] = qs[i][k] - base;
                } else
                    dp[k] = qs[i][k];
            }
            if (mp.count(dp) && cow[i].x - mp[dp] > 0)
                ans = max(ans, cow[i].x - mp[dp]);
        }
    }
    printf("%d\n", ans);

    return 0;
}