#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 4e4+5;

int n, m, r;
long L[N], R[N], dp[N][2], ans;
vector<pii> E;

int main() {
    scanf("%d %d %d", &n, &m, &r);
    for(int i = 1; i <= n; i++) scanf("%lld", L+i), dp[i][0] = L[i];
    for(int i = 1; i <= m; i++) scanf("%lld", R+i), dp[i][1] = R[i];
    for(int i = 1, a, b; i <= r; i++) {
        scanf("%d %d", &a, &b);
        E.emplace_back(a, b);
    }
    sort(E.begin(), E.end());
    for(int i = r-1; ~i; i--) {
        int u = E[i].x, v = E[i].y;
        long lhs = L[u] + dp[v][1], rhs = R[v] + dp[u][0];
        dp[u][0] = max(dp[u][0], lhs);
        dp[v][1] = max(dp[v][1], rhs);
    }
    for(int i = 1; i <= max(n, m); i++) ans = max({ans, dp[i][0], dp[i][1]});
    printf("%lld\n", ans);

    return 0;
}