#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3+5;
const int M = 1e9+7;

int n, s, e;
long dp[N][N];

int main() {
    scanf("%d %d %d", &n, &s, &e);
    dp[1][1] = 1;
    for(int i = 2; i <= n; i++) for(int j = 1; j <= i; j++) {
        if(i == s || i == e) {
            dp[i][j] = (dp[i][j] + dp[i-1][j]) % M; //Append to a component
            dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % M; //Add new component
        } else {
            dp[i][j] = (dp[i][j] + dp[i-1][j+1] * j) % M; //Merge two components
            dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (j - (i > s) - (i > e))) % M; //Add new componet (Subtract endings if they're already filled)
        }
    }
    printf("%lld\n", dp[n][1]);

    return 0;
}