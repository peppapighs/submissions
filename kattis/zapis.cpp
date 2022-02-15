#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 205;
const int M = 1e5;
const char op[] = {'(', '[', '{'};
const char cl[] = {')', ']', '}'};

int n;
long dp[N][N];
char S[N];

int main() {
    scanf("%d %s", &n, S + 1);
    for(int i = 0; i <= n + 1; i++) for(int j = 0; j < i; j++)
        dp[i][j] = 1;
    for(int len = 2; len <= n; len += 2) for(int i = 1, j = len; j <= n; i++, j++) {
        for(int k = i + 1; k <= j; k += 2) for(int x = 0; x < 3; x++) {
            if((S[i] == op[x] || S[i] == '?') && (S[k] == cl[x] || S[k] == '?')) {
                dp[i][j] += dp[i + 1][k - 1] * dp[k + 1][j];
                if(dp[i][j] >= M) dp[i][j] = M + (dp[i][j] % M);
            }
        }
    }
    if(dp[1][n] < M) printf("%lld\n", dp[1][n]);
    else printf("%05lld\n", dp[1][n] % M);

    return 0;
}