#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 18;

int tree[N << 1], lazy[N << 1];
int arr[N];

int n, q;

void pushlz(int p, int l, int r) {
	if(lazy[p]) {
		tree[p] += lazy[p];
		if(l != r) {
			lazy[p << 1] += lazy[p];
			lazy[p << 1 | 1] += lazy[p];
		}
		lazy[p] = 0;
	}
}

void build(int p = 1, int l = 1, int r = n) {
	if(l == r) return void(tree[p] = arr[l]);
	int mid = (l + r) >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

void update(int x, int y, int k, int p = 1, int l = 1, int r = n) {
	pushlz(p, l, r);
	if(x > r || l > y) return;
	if(x <= l && r <= y) {
		lazy[p] += k;
		pushlz(p, l, r);
		return;
	}

	int mid = (l + r) >> 1;
	update(x, y, k, p << 1, l, mid), update(x, y, k, p << 1 | 1, mid + 1, r);
	tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

int query(int x, int y, int p = 1, int l = 1, int r = n) {
	pushlz(p, l, r);
	if(x > r || l > y) return INT_MAX;
	if(x <= l && r <= y) return tree[p];

	int mid = (l + r) >> 1;
	return min(query(x, y, p << 1, l, mid), query(x, y, p << 1 | 1, mid + 1, r));
}

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &arr[i]);
	build();
	while(q--) {
		int t, a, b;
		scanf("%d%d%d", &t, &a, &b);
		if(t == 1) {
			int k;
			scanf("%d", &k);
			update(a, b, k);
		} else if(t == 2) {
			printf("%d\n", query(a, b));
		}
	}

	return 0;
}