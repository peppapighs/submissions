#include <bits/stdc++.h>

using namespace std;

const int M = 1e9+7;

int n;
int A[105], B[105], pos[105];
long long dp[105][105][105];

long long solve(int a = 1, int b = 1, int s = n) {
	long long &ret = dp[a][b][s];
	if(~ret) return ret;
	if(!s) return 1LL;
	if(s == 1 && A[a] == B[b]) return 1LL;
	if(s == 1) return 0LL;
	int ino = pos[A[a]];
	if(ino < b || ino >= b+s) return 0LL;
	ret = 0LL;
	int left = ino - b;
	for(int i = 0; i <= s-left-1; i++) {
		long long sum = solve(a+left+1, ino+1, i) * solve(a+left+1+i, ino+1+i, s-left-1-i);
		sum %= M;
		sum *= solve(a+1, b, left);
		sum %= M;
		ret += sum;
		ret %= M;
	}
	return ret;
}

int main() {
	memset(dp, -1LL, sizeof dp);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A+i);
	for(int i = 1; i <= n; i++) scanf("%d", B+i), pos[B[i]] = i;
	printf("%lld\n", solve());
	
	return 0;
}
