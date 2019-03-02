#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, m;

struct node {
	int ps, ss, mx, sm;
	node() : ps(0), ss(0), mx(0), sm(0) {}
	node(int ps, int ss, int mx, int sm) : ps(ps), ss(ss), mx(mx), sm(sm) {}
	friend node operator+(const node &a, const node &b) {
		node ret;
		ret.ps = max(a.ps, a.sm+b.ps);
		ret.ss = max(b.ss, a.ss+b.sm);
		ret.mx = max({a.mx, b.mx, a.ss+b.ps});
		ret.sm = a.sm+b.sm;
		return ret;
	}
} t[N<<1];

void update(int x, int k) {
	for(t[x += n] = node(k, k, k, k); x != 1; x >>= 1) {
		if(x & 1) t[x>>1] = t[x^1] + t[x];
		else t[x>>1] = t[x] + t[x^1];
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0, a; i < n; i++) {
		scanf("%d", &a);
		t[n+i] = node(a, a, a, a);
	}
	for(int i = n-1; i; i--) t[i] = t[i<<1] + t[i<<1|1];
	printf("%d\n", t[1].mx);
	while(m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		update(a, b);
		printf("%d\n", t[1].mx);
	}

	return 0;
}