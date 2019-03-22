#include <bits/stdc++.h>

#define long long long

using namespace std;

const int M = 1e9+7;

int T;
long ans[55], dp[55][55];

long solve(long N, int K) {
    memset(dp, 0, sizeof dp), memset(ans, 0, sizeof ans);
    ans[0] = ans[1] = 1;
    for(int i = 0; i <= K; i++) dp[0][i] = 1, dp[i+1][i] = 1;
    for(long a = N-1; a; a >>= 1) {
        if(a & 1) {
            long tdp[55];
            memset(tdp, 0, sizeof tdp);
            for(int i = 0; i <= K; i++) for(int j = 0; j <= K; j++) {
                tdp[i] += (dp[i][j] * ans[j]) % M;
                tdp[i] %= M;
            }
            for(int i = 0; i <= K; i++) ans[i] = tdp[i];
        }
        long tdp[55][55];
        memset(tdp, 0, sizeof tdp);
        for(int k = 0; k <= K; k++) for(int i = 0; i <= K; i++) for(int j = 0; j <= K; j++) {
            tdp[i][j] += (dp[i][k] * dp[k][j]) % M;
            tdp[i][j] %= M;
        }
        for(int i = 0; i <= K; i++) for(int j = 0; j <= K; j++) dp[i][j] = tdp[i][j];
    }
    long ret = 0;
    for(int i = 0; i <= K; i++) ret = (ret + ans[i]) % M;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> T;
    
    for(int i = 1; i <= T; i++) {
        long n;
        int k;
        cin >> n >> k;
        cout << "Case #" << i << ": ";
        if(n == 1) {
            if(k <= 1) cout << 1 << endl;
            else cout << 0 << endl; 
        } else if(k > n) cout << 0 << endl;
        else cout << (solve(n, k) - solve(n, k-1) + M) % M << endl;
    }

    return 0;
}