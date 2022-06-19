#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;

int n, dp[N];
long A[N], pref[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        pref[i] = pref[i - 1] + A[i];
    }

    set<pii, greater<pii>> S;
    S.emplace(0, 0);
    for (int i = 1; i <= n; i++) {
        auto it = S.lower_bound(pii(pref[i], 1e9));

        dp[i] = dp[it->y] + 1;
        long val = 2ll * pref[i] - pref[it->y];
        auto now = S.begin();
        while (now != S.end()) {
            if (now->x >= val)
                now = S.erase(now);
            else
                break;
        }
        S.emplace(val, i);
    }
    printf("%d\n", dp[n]);

    return 0;
}