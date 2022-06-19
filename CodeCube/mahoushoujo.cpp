#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k;
int A[N], dp[N];
deque<int> idx[1005];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    fill(begin(dp), end(dp), 1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        idx[A[i]].emplace_back(i);
        for (int j = 1; j < A[i]; j++)
            idx[j].clear();
        int cur = max(0, i - k);
        for (int j = 1000; j >= A[i]; j--) {
            while (!idx[j].empty() && idx[j].front() < i - k + 1)
                idx[j].pop_front();
            if (idx[j].empty())
                continue;
            dp[i] = min(dp[i], j + dp[cur]);
            cur = max(cur, idx[j].back());
        }
    }

    printf("%d", dp[n]);

    return 0;
}
