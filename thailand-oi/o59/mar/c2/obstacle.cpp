#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
const int M = 2e4 + 5;

int n, s;
int dp[M];
vector<int> v[N];

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1, sz; i <= n; i++) {
        scanf("%d", &sz);
        v[i].resize(sz);
        for (int &x : v[i])
            scanf("%d", &x);
    }
    for (int i = n; i; i--) {
        for (int j = s; j; j--)
            dp[j] = dp[j - 1];
        for (int j = 1; j < v[i].size(); j++)
            v[i][j] += v[i][j - 1];
        for (int j = s; ~j; j--)
            for (int k = 0; k < v[i].size() && k < j; k++)
                dp[j] = max(dp[j], dp[j - k - 1] + v[i][k]);
    }
    printf("%d\n", dp[s]);

    return 0;
}
