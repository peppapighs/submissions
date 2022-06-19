#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n, mx, A[N];
long d[N], dp[N], tdp[N];
vector<int> coin[N];

long nex(int idx, int i) {
    int now = coin[idx][i];
    int nex = coin[idx][(i + 1) % (int)coin[idx].size()];
    if (now < nex)
        return d[nex - 1] - d[now - 1];
    return d[n] - (d[now - 1] - d[nex - 1]);
}

int main() {
    fill_n(dp, N, 1e18), fill_n(tdp, N, 1e18);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        coin[A[i]].emplace_back(i);
        mx = max(mx, A[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", d + i);
        d[i] += d[i - 1];
    }
    for (int i = 0; i < coin[1].size(); i++) {
        int pre = i == 0 ? coin[1].size() - 1 : i - 1;
        dp[coin[1][i]] = d[n] - max(nex(1, i), nex(1, pre));
    }
    for (int j = 2; j <= mx; j++) {
        int ptr = 0;
        long mn1 = 1e18, mn2 = 1e18;

        for (int x : coin[j]) {
            while (ptr < coin[j - 1].size() && coin[j - 1][ptr] < x) {
                mn1 = min(mn1, dp[coin[j - 1][ptr]] - d[coin[j - 1][ptr] - 1]);
                mn2 = min(mn2, dp[coin[j - 1][ptr]] + d[coin[j - 1][ptr] - 1]);
                ++ptr;
            }
            tdp[x] = min(tdp[x], mn1 + d[x - 1]);
            tdp[x] = min(tdp[x], mn2 + d[n] - d[x - 1]);
        }

        ptr = coin[j - 1].size() - 1;
        mn1 = mn2 = 1e18;
        for (int i = coin[j].size() - 1; ~i; i--) {
            int x = coin[j][i];
            while (ptr >= 0 && coin[j - 1][ptr] > x) {
                mn1 = min(mn1, dp[coin[j - 1][ptr]] - d[coin[j - 1][ptr] - 1]);
                mn2 = min(mn2, dp[coin[j - 1][ptr]] + d[coin[j - 1][ptr] - 1]);
                --ptr;
            }
            tdp[x] = min(tdp[x], mn1 + d[n] + d[x - 1]);
            tdp[x] = min(tdp[x], mn2 - d[x - 1]);
        }
        for (int i = 0; i < coin[j].size(); i++) {
            int pre = i == 0 ? coin[j].size() - 1 : i - 1;
            int suf = i == coin[j].size() - 1 ? 0 : i + 1;
            dp[coin[j][i]] = min(tdp[coin[j][pre]] + d[n] - nex(j, pre),
                                 tdp[coin[j][suf]] + d[n] - nex(j, i));
        }
    }
    long ans = 1e18;
    for (int x : coin[mx])
        ans = min(ans, dp[x]);
    printf("%lld\n", ans);

    return 0;
}