#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
const int M = 9901;

int n, m;
int pref[N], q[N];
int dp[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &pref[i]), pref[i] += pref[i - 1];
	while(m--) {
		int a;
		scanf("%d", &a);
		int l = 1, r = n, res;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(pref[mid] >= a) res = mid, r = mid - 1;
			else l = mid + 1;
		}
		q[a] = res;
	}
	dp[1][1] = 1;
	for(int j = 1; j <= n; j++) {
		for(int i = 2; i <= pref[n]; i++) {
			if(q[i] && j != q[i]) continue;
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
			dp[i][j] %= M;
		}
	}

	printf("%d", dp[pref[n]][n]);

	return 0;
}