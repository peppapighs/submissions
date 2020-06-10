#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;
const int M = 1e9 + 7;

int n, s, e;
long dp[N][N];
char S[N];

int main() {
    scanf(" %s %d %d", S + 1, &s, &e);
    n = strlen(S + 1);
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) {
        if(i == s) {
            if(S[i] != 'L') dp[i][j] += dp[i - 1][j - 1];
            if(S[i] != 'R') dp[i][j] += dp[i - 1][j];
        } else if(i == e) dp[i][j] += dp[i - 1][j - 1] + dp[i - 1][j];
        else {
            if(S[i] != 'L') {
                //Append to the back of cc
                dp[i][j] += (j - (i > e)) * dp[i - 1][j];
                //Create new cc
                dp[i][j] += max(0, j - (i > e) - (i > s)) * dp[i - 1][j - 1];
            }
            if(S[i] != 'R') {
                //Append to the front of cc
                dp[i][j] += (j - (i > s)) * dp[i - 1][j];
                //Merge 2 cc
                dp[i][j] += j * dp[i - 1][j + 1];
            }
        }
        dp[i][j] %= M;
   }
   printf("%lld\n", dp[n][1]);

    return 0;
}