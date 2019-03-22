#include <bits/stdc++.h>

#define long long long

using namespace std;

const int M = 1e9+7;

int T;
long ans[4], dp[4][4];
long init[4][4] = { { 3, -1ll, 1, 1 }, { 1, 0, 0, 0 }, { 0, 0, 1, 1 }, { 0, 0, 0, 1 } };

long solve(int n) {
    if(n == 1) return 0;
    if(n == 2) return 1;
    ans[0] = 1, ans[1] = 0, ans[2] = 1, ans[3] = 1;
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) dp[i][j] = (init[i][j] + M) % M;
    for(int a = n-2; a; a >>= 1) {
        if(a & 1) {
            long tdp[4];
            memset(tdp, 0, sizeof tdp);
            for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) {
                tdp[i] += (dp[i][j] * ans[j]) % M;
                tdp[i] %= M;
            }
            for(int i = 0; i < 4; i++) ans[i] = tdp[i];
        }
        long tdp[4][4];
        memset(tdp, 0, sizeof tdp);
        for(int k = 0; k < 4; k++) for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) {
            tdp[i][j] += (dp[i][k] * dp[k][j]) % M;
            tdp[i][j] %= M;
        }
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) dp[i][j] = tdp[i][j];
    }
    return ans[0];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> T;

    while(T--) {
        int n;
        cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}