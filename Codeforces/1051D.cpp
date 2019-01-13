#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int M = 998244353;

int n, k;
int dp[N][2*N][5];
int cnt[4][4] = {{0, 1, 1, 1}, {0, 0, 2, 0}, {0, 2, 0, 0}, {1, 1, 1, 0}};

int solve(int i, int c, int bit) {
	if(c > k) return 0;
	if(i == n) return (c == k);
	int &cur = dp[i][c][bit];
	if(~cur) return cur;
	cur = 0;
	for(int j = 0; j <= 3; j++) if(c + cnt[bit][j] <= k) cur = (cur + solve(i+1, c+cnt[bit][j], j)) % M;
	return cur;
}

int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d %d", &n, &k);
	int ans = 0;
	ans = (ans + solve(1, 1, 0)) % M;
	ans = (ans + solve(1, 2, 1)) % M;
	ans = (ans + solve(1, 2, 2)) % M;
	ans = (ans + solve(1, 1, 3)) % M;
	printf("%d\n", ans % M);

	return 0;
}