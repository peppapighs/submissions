#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+10;
const int M = 1e5+5;

int n, k;
int t[N<<1];

int query(int l, int r) {
	int sum = 0;
	for(l += M, r += M+1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) sum += t[l++];
		if(r & 1) sum += t[--r];
	}
	return sum;
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		t[M+a]++;
	}
	for(int i = M-1; i; i--) t[i] = t[i<<1] + t[i<<1|1];
	long long l = 0, r = 1e10;
	while(l < r) {
		long long m = (l+r) >> 1;
		long long x = m;
		int low = M, high = 1;
		for(int i = 1; i <= M; i++) {
			x -= (long long)query(0, i);
			if(x < 0) {
				low = i;
				break;
			}
		}
		x = m;
		for(int i = M; i; i--) {
			x -= (long long)query(i, M-1);
			if(x < 0) {
				high = i;
				break;
			}
		}
		if(high-low <= k) r = m;
		else l = m+1;
	}

	printf("%lld\n", r);

	return 0;
}
