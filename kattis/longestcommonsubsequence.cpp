#include <bits/stdc++.h>

using namespace std;

int n, k;
int cnt[30][30], dp[30], indeg[30], chk[30];
char S[30];
vector<int> g[30];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf(" %s", S);
        for (int j = 0; j < k; j++) {
            ++cnt[S[j] - 'A'][S[j] - 'A'];
            for (int l = j + 1; l < k; l++)
                ++cnt[S[j] - 'A'][S[l] - 'A'];
        }
    }

    for (int i = 0; i < k; i++) {
        if (cnt[i][i] == n)
            chk[i] = 1;
        for (int j = 0; j < k; j++) {
            if (i == j || cnt[i][j] != n)
                continue;
            g[i].emplace_back(j);
            ++indeg[j];
        }
    }

    queue<int> Q;
    vector<int> order;
    for (int i = 0; i < k; i++)
        if (!indeg[i] && chk[i])
            Q.emplace(i);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        order.emplace_back(u);
        for (int v : g[u])
            if (!--indeg[v])
                Q.emplace(v);
    }

    for (int &x : order)
        for (int v : g[x])
            dp[v] = max(dp[v], dp[x] + 1);

    int ans = 0;
    for (int i = 0; i < k; i++)
        if (chk[i])
            ans = max(ans, dp[i] + 1);

    printf("%d\n", ans);

    return 0;
}