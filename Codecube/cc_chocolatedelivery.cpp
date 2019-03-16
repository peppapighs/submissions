#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3+5;
const int M = 1e9+7;

long fac[200005], inv[200005];

long modpow(long a, long b) {
	long ret = 1;
	for( ; b; b >>= 1) {
		if(b & 1) ret = (ret * a) % M;
		a = (a * a) % M;
	}
	return ret;
}

long ncr(int n, int r) {
	long ret = (fac[n] * inv[r]) % M;
	return (ret * inv[n-r]) % M;
}

long comb(pii a, pii b) {
	return ncr(abs(a.x - b.x) + abs(a.y - b.y), abs(a.x - b.x));
}

int n, q;
long cnt[N];
pii A[N];

int main() {
	fac[0] = 1;
	for(int i = 1; i < 200005; i++) fac[i] = (fac[i-1] * i) % M;
	for(int i = 0; i < 200005; i++) inv[i] = modpow(fac[i], M-2);
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d %d", &A[i].x, &A[i].y);	
	sort(A + 1, A + n + 1);
	for(int i = 1; i <= n; i++) {
		cnt[i] = comb(pii(1, 1), A[i]);
		for(int j = 1; j < i; j++) if(A[j].y <= A[i].y) {
			long sub = (cnt[j] * comb(A[j], A[i])) % M;
			cnt[i] = (cnt[i] - sub + M) % M;
		}
	}
	for(int i = 1; i <= q; i++) {
		pii now;
		scanf("%d %d", &now.x, &now.y);
		long ans = comb(pii(1, 1), now);
		for(int j = 1; j <= n; j++) if(A[j].x <= now.x && A[j].y <= now.y) {
			long sub = (cnt[j] * comb(A[j], now)) % M;
			ans = (ans - sub + M) % M;
		}
		printf("%lld\n", ans);
	}

	return 0;
}