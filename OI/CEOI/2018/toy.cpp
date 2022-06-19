#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> fac;

int main() {
    scanf("%d", &n);

    for (int i = 1; i * i <= n; i++)
        if (n % i == 0) {
            fac.emplace_back(i);
            if (i * i != n)
                fac.emplace_back(n / i);
        }
    sort(fac.begin(), fac.end());

    vector<vector<int>> dp(fac.size());
    dp[0].emplace_back(0);

    for (int i = 1; i < fac.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (fac[i] % fac[j] != 0)
                continue;
            for (int x : dp[j])
                dp[i].emplace_back(x + fac[i] / fac[j] - 1);
        }
        sort(dp[i].begin(), dp[i].end());
        dp[i].resize(unique(dp[i].begin(), dp[i].end()) - dp[i].begin());
    }
    printf("%d\n", (int)dp.back().size());
    for (int x : dp.back())
        printf("%d ", x);
    printf("\n");

    return 0;
}