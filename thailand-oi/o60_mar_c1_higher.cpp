#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int n, k;
int t[N<<1];

void update(int k, int x) {
	for(t[x += n] = k; x != 1; x >>= 1) t[x>>1] = max(t[x], t[x^1]);
}

int query(int l, int r) {
	int ret = 0;
	for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) ret = max(ret, t[l++]);
		if(r & 1) ret = max(ret, t[--r]);
	}
	return ret;
}

int main() {
	scanf("%d %d", &n, &k);
	while(k--) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		update(0, a);
		int l = 0, r = n, d = 0;
		while(l <= r) {
			int mid = (l+r) >> 1;
			if(query(max(0, a-mid), min(n-1, a+mid)) <= b) d = mid, l = mid+1;
			else r = mid-1;
		}
		update(b, a);
		printf("%d\n", d);
	}	

	return 0;
}