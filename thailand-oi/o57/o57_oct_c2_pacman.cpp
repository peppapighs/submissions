#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int n, m;
int A[N][N];
int dp[N][N][3];

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &A[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		dp[i][j][0] = max({dp[i-1][j][0], dp[i-1][j][1], dp[i-1][j][2], dp[i][j-1][0], dp[i][j-1][1], dp[i][j-1][2]});
		dp[i][j][1] = max(dp[i-1][j][0], dp[i][j-1][0]) + A[i][j];
		dp[i][j][2] = max(dp[i-1][j][1], dp[i][j-1][1]) + A[i][j];
	}
	printf("%d\n", max({dp[n][m][0], dp[n][m][1], dp[n][m][2]}));

	return 0;
}