#include <bits/stdc++.h>

#define long long long

using namespace std;

const int M = 1e9+7;

long ans[5], dp[5][5];
long init[5][5] = { { 2, 3, 1, 0, 0 },
                    { 1, 0, 0, 0, 0 },
                    { 0, 0, 3, 6, 3 },
                    { 0, 0, 0, 3, 3 },
                    { 0, 0, 0, 0, 3 } };

long solve(long n) {
    ans[0] = 1, ans[1] = 1, ans[2] = 36, ans[3] = 18, ans[4] = 9;
    for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) dp[i][j] = init[i][j];
    for(long a = n-1; a; a >>= 1) {
        if(a & 1) {
            long tdp[5];
            memset(tdp, 0, sizeof tdp);
            for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) {
                tdp[i] += (dp[i][j] * ans[j]) % M;
                tdp[i] %= M;
            }
            for(int i = 0; i < 5; i++) ans[i] = tdp[i];
        }
        long tdp[5][5];
        memset(tdp, 0, sizeof tdp);
        for(int k = 0; k < 5; k++) for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) {
            tdp[i][j] += (dp[i][k] * dp[k][j]) % M;
            tdp[i][j] %= M;
        }
        for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) dp[i][j] = tdp[i][j];
    }
    return ans[0];
}

int T;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> T;

    while(T--) {
        long n;
        cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}