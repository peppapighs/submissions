#include <bits/stdc++.h>

using namespace std;

const int N = 5e3+1;

int n, ans, h[N];
float dp[N][N];

int main() {
	fill_n(dp[0], N*N, -1e9);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", h+i), dp[i][1] = 1e9;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < i; j++) {
			float d = (float)(h[i] - h[j]) / (float)(i - j);
			int l = 1, r = n - 1;
			while(l < r) {
				int mid = (l + r + 1) >> 1;
				if(dp[j][mid] >= d) l = mid;
				else r = mid - 1;
			}
			dp[i][l+1] = max(dp[i][l+1], d);
		}
		float mx = -1e9;
		for(int j = n; j; j--) {
			dp[i][j] = max(dp[i][j], mx);
			mx = max(mx, dp[i][j]);
		}
		for(int j = 1; j <= n; j++) if(dp[i][j] != -1e9) ans = max(ans, j);
	}
	printf("%d\n", ans);

	return 0;
}