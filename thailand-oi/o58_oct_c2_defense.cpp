#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, k;
int A[N], dp[N][N][2];

int f(int k) {
	if(k < 0) return 0;
	return k;
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
	for(int i = 1; i <= n; i++) for(int j = 0; j <= k; j++) dp[i][j][0] = dp[i][j][1] = 1e9;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			dp[i][j][0] = min(dp[i][j-1][0], dp[f(i-j)][k-j][0] + A[i]);
			if(j < k) dp[i][j][1] = min(dp[i][j-1][1], dp[f(i-j)][k-j-1][0]);
		}
	}

	printf("%d\n", min(dp[n][k][0], dp[n][k-1][1]));

	return 0;
}