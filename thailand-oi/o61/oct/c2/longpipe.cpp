#include <bits/stdc++.h>

#define long long long

using namespace std;

const int M = 1e9 + 7;

int n;
long ans[3] = {4, 3, 2};
long dp[3][3] = {{1, 2, 1}, {1, 1, 0}, {1, 0, 1}};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int a = n - 1; a; a >>= 1) {
        if (a & 1) {
            long tdp[3];
            memset(tdp, 0, sizeof tdp);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    tdp[i] += (dp[i][j] * ans[j]) % M;
                    tdp[i] %= M;
                }
            for (int i = 0; i < 3; i++)
                ans[i] = tdp[i];
        }
        long tdp[3][3];
        memset(tdp, 0, sizeof tdp);
        for (int k = 0; k < 3; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    tdp[i][j] += (dp[i][k] * dp[k][j]) % M;
                    tdp[i][j] %= M;
                }
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                dp[i][j] = tdp[i][j];
    }
    cout << (ans[0] + ans[1]) % M << endl;

    return 0;
}