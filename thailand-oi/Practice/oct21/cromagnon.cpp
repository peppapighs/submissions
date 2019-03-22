#include <bits/stdc++.h>

using namespace std;

const int MOD = 2009;

int n, m;
int M[25][25], A[105];
int dp[105][105][25];

int main() {
       scanf("%d", &m);
       for(int i = 0; i < m; i++) for(int j = 0; j < m; j++) scanf("%d", &M[i][j]);
       scanf("%d", &n);
       for(int i = 1; i <= n; i++) {
              scanf("%d", A+i);
              ++dp[i][i][A[i]];
       }
       for(int len = 2; len <= n; len++) 
              for(int i = 1, j = i+len-1; j <= n; i++, j++)
                     for(int k = i; k < j; k++)
                            for(int a = 0; a < m; a++)
                                   for(int b = 0; b < m; b++)
                                          dp[i][j][M[a][b]] = (dp[i][j][M[a][b]] + dp[i][k][a]*dp[k+1][j][b]) % MOD;
       
       for(int i = 0; i < m; i++) printf("%d\n", dp[1][n][i]);

       return 0;
}