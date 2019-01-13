#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

long long fac[N], infac[N];

long long powmod(long long x, long long y) {
	if(y == 0) return 1LL;
	else if(y == 1) return x;
	else {
		long long mid = powmod(x, y >> 1);
		long long ret = (mid * mid) % MOD;
		if(y & 1) ret = (ret * x) % MOD;
		return ret;
	}
}

int T;

int main() {
	fac[0] = 1LL;
	infac[0] = 1LL;
	for(int i = 1; i < N; i++) fac[i] = (fac[i - 1] * i) % MOD;
	for(int i = 1; i < N; i++) infac[i] = powmod(fac[i], MOD - 2) % MOD;
	scanf("%d", &T);
	while(T--) {
		int n, r;
		scanf("%d%d", &n, &r);
		long long ans = (fac[n] * infac[r]) % MOD;
		ans = (ans * infac[n - r]) % MOD;
		printf("%lld\n", ans);
	}

	return 0;
}