#include <bits/stdc++.h>

using namespace std;

const int N = 3e3+5;

int n, m, ans;
char A[N][N];
bool valid[N][N][2];

int main() {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++) scanf(" %s", A[i]+1);
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
                if(A[i][j] != 'G') continue;
                if(i > 1 && i < n && A[i-1][j] == 'R' && A[i+1][j] == 'W') valid[i][j][0] = true;
                if(j > 1 && j < m && A[i][j-1] == 'R' && A[i][j+1] == 'W') valid[i][j][1] = true;
        }
        for(int sum = 2; sum <= n+m; sum++) {
                int dp[N][3], lst;
                fill_n(dp[0], N*3, 0);
                for(int i = 1, j = sum-i; i <= n; i++, j--) {
                        if(j < 1 || j > m) continue;
                        dp[i][0] = max({ dp[i-1][0], dp[i-1][1], dp[i-1][2] });
                        if(valid[i][j][0]) dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + 1;
                        if(valid[i][j][1]) dp[i][2] = max(dp[i-1][0], dp[i-1][2]) + 1;
                        lst = i;
                }
                ans += max({ dp[lst][0], dp[lst][1], dp[lst][2] });
        }

        printf("%d\n", ans);

        return 0;
}
