#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, q;
long T, M;

vector<vector<long>> mult(vector<vector<long>> &A, vector<vector<long>> &B) {
    vector<vector<long>> C(n + 1, vector<long>(n + 1, 0));
    for(int k = 0; k <= n; k++) for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j] % M) % M;
    return C;
}

vector<long> mult(vector<vector<long>> &A, vector<long> &B) {
    vector<long> C(n + 1, 0);
    for(int k = 0; k <= n; k++) for(int i = 0; i <= n; i++)
        C[i] = (C[i] + A[i][k] * B[k] % M) % M;
    return C;
}

int main() {
    scanf("%d", &n);

    vector<vector<int>> A(n + 1, vector<int>(n + 1, 0));
    vector<int> B(n + 1);
    for(int i = 0; i <= n; i++) {
        if(i == 0) {
            scanf("%d", &B[n]);
            A[0][n] = A[n][n] = 1;
        } else {
            scanf("%d", &A[0][i - 1]);
            if(i < n) A[i][i - 1] = 1;
        }
    }
    for(int i = n - 1; ~i; i--) scanf("%d", &B[i]);
    
    scanf("%d", &q);
    while(q--) {
        scanf("%lld %lld", &T, &M);
        vector<vector<long>> dp(n + 1, vector<long>(n + 1));
        vector<long> init(n + 1);

        for(int i = 0; i <= n; i++) {
            init[i] = (B[i] % M + M) % M;
            for(int j = 0; j <= n; j++)
                dp[i][j] = (A[i][j] % M + M) % M;
        }

        if(T < n) printf("%lld\n", init[n - 1 - T]);
        else {
            for(T -= n - 1; T; T >>= 1) {
                if(T & 1) init = mult(dp, init);
                dp = mult(dp, dp);
            }
            printf("%lld\n", init[0]);
        }
    }

    return 0;
}