#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e3+5;
const long INF = 1e18;

void add(long &a, long b) {
    a += b;
    if(a > INF) a = INF;
}

int n;
long k, dp[N][N];
char S[N];

int main() {
    scanf("%s %lld", S+1, &k);
    n = strlen(S+1), --k;
    dp[n+1][0] = 1;
    for(int i = n; i; i--) for(int j = 0; j <= i; j++) {
        if(S[i] == '.') {
            if(j) add(dp[i][j], dp[i+1][j-1]);
            add(dp[i][j], dp[i+1][j+1]);
        }
        if(S[i] == ')' && j) add(dp[i][j], dp[i+1][j-1]);
        if(S[i] == '(') add(dp[i][j], dp[i+1][j+1]);
    }
    int j = 0;
    for(int i = 1; i <= n; i++) {
        if(S[i] == '.') {
            if(k < dp[i+1][j+1]) printf("("), ++j;
            else printf(")"), k -= dp[i+1][j+1], --j;
        } else {
            if(S[i] == '(') printf("("), ++j;
            else printf(")"), --j;
        }
    }
    printf("\n");

    return 0;
}
