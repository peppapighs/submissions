#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1005;
const int M = 1e9 + 7;

long inv[N];

long modpow(long a, long b) {
    long ret = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

int n, a[N], b[N];
long dp[N][N];
vector<int> coord;

int main() {
    for (int i = 1; i < N; i++)
        inv[i] = modpow(i, M - 2);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", a + i, b + i);
        coord.emplace_back(a[i]);
        coord.emplace_back(++b[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (int i = 1; i <= n; i++) {
        a[i] =
            lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1;
        b[i] =
            lower_bound(coord.begin(), coord.end(), b[i]) - coord.begin() + 1;
    }
    for (int i = 0; i < N; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j < b[i]; j++) {
            long p = coord[j] - coord[j - 1], cnt = 1;
            for (int k = i - 1; ~k; k--) {
                dp[i][j] = (dp[i][j] + (p * dp[k][j - 1]) % M) % M;
                if (a[k] <= j && j < b[k]) {
                    ++cnt;
                    p = (p * (coord[j] - coord[j - 1] + cnt - 1)) % M;
                    p = (p * inv[cnt]) % M;
                }
            }
        }
        for (int j = 1; j < N; j++)
            dp[i][j] = (dp[i][j] + dp[i][j - 1]) % M;
    }
    long ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + dp[i][N - 1]) % M;
    printf("%lld\n", ans);

    return 0;
}