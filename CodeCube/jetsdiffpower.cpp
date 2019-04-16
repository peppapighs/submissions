#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

int n, C;
long A[N], dp[105], pre[105], suf[105];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", A+i);
	scanf("%d", &C);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= 100; j++) {
			if(i == 1) dp[j] = j * j;
			else {
				int x = A[i] - A[i-1] + j;
				dp[j] = 1e18;
				if(x >= 0) dp[j] = min(dp[j], pre[min(x, 100)] + C * x);
				if(x <= 100) dp[j] = min(dp[j], suf[max(x, 0)] - C * x);
				dp[j] += j * j;
			}
		}
		for(int j = 0; j <= 100; j++) {
			pre[j] = dp[j] - C * j;
			if(j) pre[j] = min(pre[j], pre[j-1]);
		}
		for(int j = 100; ~j; j--) {
			suf[j] = dp[j] + C * j;
			if(j != 100) suf[j] = min(suf[j], suf[j+1]);
		}
	}
	long ans = 1e18;
	for(int i = 0; i <= 100; i++) ans = min(ans, dp[i]);
	printf("%lld\n", ans);

	return 0;
}