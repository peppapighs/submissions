#include "mountains.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e3+5;

int n, dp[N][N];

int maximum_deevs(vector<int> y) {
    n = y.size();

    for(int r = 0; r < n; r++) {
        dp[r][r] = 1;
        int high = r, cnt = 0;
        for(int l = r-1; ~l; l--) {
            pii vec1(high - l, y[high] - y[l]);
            pii vec2(r - l, y[r] - y[l]);
            if(1ll * vec1.x * vec2.y >= 1ll * vec1.y * vec2.x) {
                cnt += dp[l+1][high-1];
                high = l;
            }
            dp[l][r] = max(dp[l][r-1], dp[l][high-1] + cnt + 1);
        }
    } 
    
    return dp[0][n-1];
}