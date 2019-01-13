#include <bits/stdc++.h>

using namespace std;

const int N = 3e3+5;

int n;
int dp[2][N];
int A[N], mp[N];

int main() {
       scanf("%d", &n);
       for(int i = 1; i <= n; i++) scanf("%d", A+i);
       for(int i = 1, a; i <= n; i++) scanf("%d", &a), mp[a] = i;
       for(int i = 1; i <= n; i++) {
              int now = i & 1, pre = now ^ 1;
              for(int j = 0; j <= n; j++) dp[now][j] = 0;
              for(int j = 1; j <= n; j++) {
                     dp[now][j] = dp[pre][j];
                     if(mp[A[i]] <= j) dp[now][j] = max(dp[now][j], dp[pre][mp[A[i]]-1] + 1);
              }
       }
       printf("%d\n", dp[n & 1][n]);

       return 0;
}