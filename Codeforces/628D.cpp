#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;
const int M = 1e9+7;

int m, d;
long long a, b;
char A[N];
int dp[N][N][2][2];

bool f() {
	int r = 0;
	for(int i = 0; A[i]; i++) {
		int p = A[i]-'0';
		if(!(i & 1) && p == d) return false;
		if((i & 1) && p != d) return false;
		r = (r*10 + p) % m;
	}
	return !r;
}

int solve(int pos = 0, int r = 0, int f = 0, int st = 1) {
	if(!A[pos]) return !r;
	int &ret = dp[pos][r][f][st];
	if(~ret) return ret;
	ret = 0;
	int lim;
	if(!f) lim = A[pos]-'0';
	else lim = 9;
	for(int i = 0; i <= lim; i++) {
		if((pos & 1) && i != d) continue;
		if(!(pos & 1) && i == d) continue;
		if(!i && st) ret = (ret + solve(pos+1, 0, 1, 1)) % M;
		else ret = (ret + solve(pos+1, (r*10 + i) % m, f|(i < lim), 0)) % M; 
	} 
	return ret;
}

int main() {
	scanf("%d %d", &m, &d);
	memset(dp, -1, sizeof dp);
	scanf(" %s", A);
	int ans = -solve() + f();
	memset(dp, -1, sizeof dp);
	scanf(" %s", A);
	ans += solve();
	ans = (ans + M) % M;

	printf("%d\n", ans);

	return 0;
}