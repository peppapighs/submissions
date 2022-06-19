#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 1;

int n, m;
bitset<N> chk;
int sz[N], mp[N], pos[N], comp;
vector<int> dp(N);

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        mp[a] = b, mp[b] = a;
        ++dp[a], ++dp[b];
    }
    int ptr = 0;
    for (int i = 1; i < N; i++) {
        dp[i] += dp[i - 1];
        if (dp[i] != dp[i - 1])
            pos[ptr++] = i;
    }
    for (int i = 0; i < 2 * n; i++)
        if (!chk[i]) {
            ++comp;
            chk[i] = true;
            int u = i;
            while (1) {
                ++sz[comp];
                int v = dp[mp[pos[u]]];
                if (chk[v] || v == 2 * n)
                    break;
                chk[v] = true;
                u = v;
            }
        }
    int ans = sz[1];
    for (int i = 2; i <= comp; i++)
        dp[i - 2] = sz[i];
    sort(dp.begin(), dp.begin() + comp - 1, greater<int>());
    for (int i = 0; i < comp - 1 && m; i++, m--)
        ans += dp[i] + 2;
    if (m)
        ans += 2 * (m - (m & 1)) + (m & 1);
    printf("%d\n", ans);

    return 0;
}