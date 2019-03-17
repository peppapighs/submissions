#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, m, ans, A[N][N];
int dp1[N][N], dp2[N][N];

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &A[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) A[i][j] += A[i-1][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) {
		int mx = 0;
		for(int k = 1; k <= m; k++) {
			mx += A[i][k] - A[j-1][k];
			ans = max(ans, mx + dp1[j-1][k]);
			dp1[i][k] = max(dp1[i][k], mx);
			if(mx < 0) mx = 0;
		}
		mx = 0;
		for(int k = m; k; k--) {
			mx += A[i][k] - A[j-1][k];
			ans = max(ans, mx + dp2[j-1][k]);
			dp2[i][k] = max(dp2[i][k], mx);
			if(mx < 0) mx = 0;
		}
	}
	printf("%d\n", ans);

	return 0;
}
