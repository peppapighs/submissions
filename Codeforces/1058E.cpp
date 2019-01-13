#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

int n;
int A[N], qs[N], cnt[N][2];
long long ans;

int popcount(long long x) {
	int ret = 0;
	for( ; x; x >>= 1) ret += (x & 1);
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		long long a;
		scanf("%lld", &a);
		A[i] = popcount(a);
	}
	cnt[n+1][0] = 1;
	for(int i = n; i; i--) {
		qs[i] += qs[i+1] + A[i];
		ans += cnt[i+1][qs[i]&1];
		cnt[i][0] = cnt[i+1][0] + !(qs[i]%2);
		cnt[i][1] = cnt[i+1][1] + (qs[i]&1);
		int mx = A[i];
		for(int j = i+1; j <= min(i+62, n+1); j++) {
			if((qs[i]-qs[j])%2 == 0 && mx > qs[i] - qs[j] - mx) ans--;
			mx = max(mx, A[j]);
		}
	}
	printf("%lld\n", ans);

	return 0;
}