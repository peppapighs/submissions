#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int B = 512;

int n, k, last[N];
long A[N], dp[N], pref[N], ans;
deque<pii> Q;

int main() {
    scanf("%d %d", &n, &k);
    long sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        sum += A[i];
    }
    if (set<int>(A + 1, A + n + 1).size() == n && sum <= k)
        return !printf("%lld\n", sum);

    for (int step = 1; step <= B; step++) {
        fill_n(dp, N, -1e18), fill_n(last, N, 0), Q.clear();
        for (int i = 1; i <= n; i++)
            pref[i] = pref[i - 1] + A[i];

        dp[0] = 0;
        Q.emplace_back(0, 0);
        for (int i = 1, ptr = 0; i < n; i++) {
            ptr = max(ptr, last[A[i]]);
            while (pref[i] - pref[ptr] > k)
                ++ptr;
            while (!Q.empty() && Q.front().y < ptr)
                Q.pop_front();
            dp[i] = max(dp[i - 1], pref[i] + Q.front().x);

            while (!Q.empty() && Q.back().x <= dp[i - 1] - pref[i])
                Q.pop_back();
            Q.emplace_back(dp[i - 1] - pref[i], i);
            last[A[i]] = i;
        }
        ans = max(ans, dp[n - 1]);
        rotate(A + 1, A + 2, A + 1 + n);
    }
    printf("%lld\n", ans);

    return 0;
}