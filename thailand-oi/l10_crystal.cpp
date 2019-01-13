#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int M = 10001;

int n;
int dp[N];

int main() {
       scanf("%d", &n);
       dp[0] = dp[1] = 1;
       for(int i = 2; i <= n; i++)
              for(int j = 0; j < i; j++)
                     dp[i] = (dp[i] + dp[j]*dp[i-j-1]) % M;
       printf("%d\n", dp[n]);

       return 0;
}