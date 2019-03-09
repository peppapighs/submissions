#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e6+5;

int n, M;
long ans = 1;
vector<int> vec, cnt;
bool chk[N];

int cntprime(long p, long x) {
	int ret = 0; long now = p;
	while(now <= x) {
		ret += x / now;
		now *= p;
	}
	return ret;
}

long modpow(long a, long b) {
	long ret = 1;
	for( ; b; b >>= 1) {
		if(b & 1) ret = (ret * a) % M;
		a = (a * a) % M;
	}
	return ret;
}

int main() {
	scanf("%d %d", &n, &M);
	for(int i = 2; i < N; i++) {
		if(chk[i]) continue;
		vec.emplace_back(i);
		for(int j = i + i; j <= 2 * n; j += i) chk[j] = true;
	}
	cnt.resize(vec.size());
	for(int i = 0; i < vec.size(); i++) cnt[i] += cntprime(vec[i], 2 * n) - 2 * cntprime(vec[i], n);
	for(int i = 0; i < vec.size(); i++) ans = (ans * modpow(vec[i], cnt[i])) % M;
	printf("%lld\n", (ans * ans) % M);

	return 0;
}