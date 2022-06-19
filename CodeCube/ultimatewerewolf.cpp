#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int q;
int par[N], deg[N];
pii dp[N], incyc[N];

int main() {
    scanf("%d", &q);

    while (q--) {
        int n, ans = 0;
        scanf("%d", &n);
        memset(par, 0, sizeof par);
        memset(deg, 0, sizeof deg);
        fill_n(dp, N, pii(0, 1));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &par[i]);
            deg[par[i]]++;
        }
        queue<int> Q;
        for (int i = 1; i <= n; i++)
            if (!deg[i])
                Q.emplace(i);
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            dp[par[now]].x += max(dp[now].x, dp[now].y);
            dp[par[now]].y += dp[now].x;
            if (!--deg[par[now]])
                Q.emplace(par[now]);
        }

        for (int k = 1; k <= n; k++)
            if (deg[k]) {
                vector<int> cyc;
                int p = k;
                while (deg[p]) {
                    deg[p]--;
                    cyc.emplace_back(p);
                    p = par[p];
                }
                incyc[0] = dp[cyc[0]];
                for (int i = 1; i < cyc.size(); i++) {
                    incyc[i].x =
                        max(incyc[i - 1].x, incyc[i - 1].y) + dp[cyc[i]].x;
                    incyc[i].y = incyc[i - 1].x + dp[cyc[i]].y;
                }
                int ret = incyc[cyc.size() - 1].x;
                incyc[0].y = INT_MIN;
                for (int i = 1; i < cyc.size(); i++) {
                    incyc[i].x =
                        max(incyc[i - 1].x, incyc[i - 1].y) + dp[cyc[i]].x;
                    incyc[i].y = incyc[i - 1].x + dp[cyc[i]].y;
                }
                ret = max(ret, incyc[cyc.size() - 1].y);
                ans += ret;
            }

        printf("%d\n", n - ans);
    }

    return 0;
}
