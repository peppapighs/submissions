#include <bits/stdc++.h>

using namespace std;

const int M = 1e9 + 7;

int n;
int day[3];
int dp[5][1005][1 << 3];
vector<int> go[3] = {{1, 2}, {2}, {0}};

int solve(int x, int d, int mask) {
	int &now = dp[x][d][mask];
	if(now != -1) return now;
	now = 0;
	if(!d) {
		if(mask == 7) now = 1;
		else now = 0;
	} else for(int i = 1; i <= day[x] && i <= d; i++) {
		if(d - i == 0) now += solve(x, 0, (mask | (1 << x)));
		else for(int next : go[x]) {
			now += solve(next, d - i, (mask | (1 << x)));
			now %= M;
		}
	} 
	now %= M;
	return now;
}

int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d", &n);
	for(int i = 0; i < 3; i++) scanf("%d", &day[i]);
	int ans = solve(0, n, 0) % M;
	printf("%d", ans);

	return 0;
}