#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 19;

int n, q;
int pre[N], t[N<<1];
char s[N];

void build(int p = 1, int l = 1, int r = 2*n) {
	if(l == r) return void(t[p] = pre[l]);
	int mid = (l + r) >> 1;
	build(p<<1, l, mid), build(p<<1|1, mid+1, r);
	t[p] = min(t[p<<1], t[p<<1|1]);
}

int query(int x, int y, int p = 1, int l = 1, int r = 2*n) {
	if(x > r || l > y) return INT_MAX;
	else if(x <= l && r <= y) return t[p];
	int mid = (l + r) >> 1;
	return min(query(x, y, p<<1, l, mid), query(x, y, p<<1|1, mid+1, r));
}

int main() {
	scanf(" %s", s+1);
	n = strlen(s+1);
	for(int i = 1; i <= n; i++) {
		if(s[i] == '(') pre[i] = 1;
		else pre[i] = -1;
		pre[i] += pre[i-1];
	}
	for(int i = 1; i <= n; i++) {
		if(s[i] == '(') pre[i+n] = 1;
		else pre[i+n] = -1;
		pre[i+n] += pre[i+n-1];
	}
	build();
	scanf("%d", &q);
	while(q--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(a <= b) {
			int ret = pre[b]-pre[a-1];
			if(!ret && query(a, b)-pre[a-1] >= 0) printf("yes\n");
			else printf("no\n");
		} else {
			b += n;
			int ret = pre[b]-pre[a-1];
			if(!ret && query(a, b)-pre[a-1] >= 0) printf("yes\n");
			else printf("no\n");
		}
	}

	return 0;
}