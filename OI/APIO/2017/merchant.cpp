#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 105;

int n, m, K;
long B[N][1005], S[N][1005];
long d[N][N], profit[N][N], dp[N][N];

bool chk(long mid) {
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        dp[i][j] = profit[i][j] - d[i][j] * mid;
    for(int i = 1; i <= n; i++) dp[i][i] = -1e9;
    for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j]);
    for(int i = 1; i <= n; i++) if(dp[i][i] >= 0) return true;
    return false;
}

int main() {
    fill_n(d[0], N*N, 1e9);
    scanf("%d %d %d", &n, &m, &K);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= K; j++) scanf("%lld %lld", &B[i][j], &S[i][j]);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        d[a][b] = c;
    }
    for(int i = 1; i <= n; i++) d[i][i] = 0;
    for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 1; k <= K; k++)
        if(~S[j][k] && ~B[i][k]) profit[i][j] = max(profit[i][j], S[j][k] - B[i][k]);
    
    long l = 0, r = 1e9;
    while(l < r) {
        long mid = (l + r + 1) >> 1;
        if(chk(mid)) l = mid;
        else r = mid-1;
    }
    printf("%lld\n", l);

    return 0;
}