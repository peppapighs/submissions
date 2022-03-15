#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, m;
int dp[16][1 << 15];
long h[16], b[16], sum[1 << 15];

bool solve(int i, int mask) {
    if(i == m) return true;
    if(dp[i][mask] != -1) return dp[i][mask] != -2;

    dp[i][mask] = -2;
    for(int sub = mask; sub; sub = (sub - 1) & mask) {
        if(sum[sub] == b[i] && solve(i + 1, mask - sub)) {
            dp[i][mask] = mask - sub;
            break;
        }
    }
    return dp[i][mask] != -2;
}

int main() {
    memset(dp, -1, sizeof dp);
    
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%lld", h + i);
    for(int i = 0; i < m; i++) scanf("%lld", b + i);

    for(int i = 0; i < 1 << n; i++)
        for(int j = i; j; j -= j & -j)
            sum[i] += h[__builtin_ctz(j & -j)];

    if(!solve(0, (1 << n) - 1))
        return !printf("-1\n");
    
    int mask = (1 << n) - 1;
    for(int i = 0; i < m; i++) {
        printf("%d ", __builtin_popcount(mask - dp[i][mask]));
        for(int j = mask - dp[i][mask]; j; j -= j & -j)
            printf("%d ", __builtin_ctz(j & -j) + 1); 
        printf("\n");
        mask = dp[i][mask];
    }

    return 0;
}