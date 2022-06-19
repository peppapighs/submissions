#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int N = 1e5 + 5;

int n;
pii rect[N];
bool dp[N][2];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &rect[i].first, &rect[i].second);
    dp[0][0] = dp[0][1] = true;
    for (int i = 1; i < n; i++) {
        if (rect[i].second <= rect[i - 1].second)
            dp[i][0] = dp[i][0] | dp[i - 1][0];
        if (rect[i].second <= rect[i - 1].first)
            dp[i][0] = dp[i][0] | dp[i - 1][1];
        if (rect[i].first <= rect[i - 1].second)
            dp[i][1] = dp[i][1] | dp[i - 1][0];
        if (rect[i].first <= rect[i - 1].first)
            dp[i][1] = dp[i][1] | dp[i - 1][1];
    }

    if (dp[n - 1][0] | dp[n - 1][1])
        printf("YES");
    else
        printf("NO");

    return 0;
}