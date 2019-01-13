#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

int n, m;
int A[N], dp[N][N][3];

int f(int i, int j) {
	if(i < j) return 0;
	else return i - j + 1;
}

int main() {
	scanf("%d", &n);
	m = (n+1) >> 1;
	for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
	for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 1e9;
	dp[0][0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			dp[i][j][0] = min(dp[i-1][j][0], dp[i-1][j][1]);
			dp[i][j][1] = dp[i-1][j][2] + f(A[i], A[i-1]);
		}
		for(int j = 1; j <= m; j++) {
			dp[i][j][2] = dp[i-1][j-1][0] + f(A[i-1], A[i]);
			if(i > 2) dp[i][j][2] = min(dp[i][j][2], dp[i-1][j-1][1] + f(min(A[i-2] - 1, A[i-1]), A[i]));
		}
	}

	for(int i = 1; i <= m; i++) printf("%d ", min(dp[n][i][0], min(dp[n][i][1], dp[n][i][2])));

	return 0;
}
