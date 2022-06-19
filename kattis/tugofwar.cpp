#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int K = 5e4 + 5;

int n;
bool dp[2][N][K];

int main() {
    scanf("%d", &n);
    int sum = 0;
    dp[0][0][0] = 1;
    for (int i = 0, w; i < n; i++) {
        scanf("%d", &w);
        sum += w;
        int now = i & 1, nex = now ^ 1;

        for (int j = 0; j <= n; j++)
            for (int k = 0; k < K; k++)
                dp[nex][j][k] = 0;
        for (int j = 0; j <= n; j++)
            for (int k = 0; k < K; k++) {
                if (!dp[now][j][k])
                    continue;
                dp[nex][j + 1][k + w] = 1;
                dp[nex][j][k] = 1;
            }
    }
    int diff = 1e9;

    vector<int> vec = {n / 2};
    if (n & 1)
        vec.emplace_back(n / 2 + 1);
    for (int &x : vec)
        for (int k = 0; k < K; k++)
            if (dp[n & 1][x][k])
                diff = min(diff, abs(sum - 2 * k));
    printf("%d %d\n", (sum - diff) / 2, (sum + diff) / 2);

    return 0;
}