#include "wall.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 21;

int lo[N << 1], hi[N << 1];
int *ret, S;

void puttag(int p, int low, int high) {
	lo[p] = min(high, max(low, lo[p]));
	hi[p] = max(low, min(high, hi[p]));
}

void pushlz(int p, int l, int r) {
	if(l == r) ret[l] = min(hi[p], max(lo[p], ret[l]));
	else {
		puttag(p << 1, lo[p], hi[p]);
		puttag(p << 1 | 1, lo[p], hi[p]);
	}
	lo[p] = 0;
	hi[p] = INT_MAX;
}

void build(int p = 1, int l = 0, int r = S - 1) {
	hi[p] = INT_MAX;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void update(int x, int y, int low, int high, int p = 1, int l = 0, int r = S - 1) {
	if(x > r || l > y) return;
	if(x <= l && r <= y) return puttag(p, low, high);
	pushlz(p, l, r);
	int mid = (l + r) >> 1;
	update(x, y, low, high, p << 1, l, mid);
	update(x, y, low, high, p << 1 | 1, mid + 1, r);
}

void proc(int p = 1, int l = 0, int r = S - 1) {
	pushlz(p, l, r);
	if(l == r) return;
	int mid = (l + r) >> 1;
	proc(p << 1, l, mid);
	proc(p << 1 | 1, mid + 1, r);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	ret = finalHeight;
	S = n;
	build();
	for(int i = 0; i < k; i++) {
		if(op[i] == 1) update(left[i], right[i], height[i], INT_MAX);
		else if(op[i] == 2) update(left[i], right[i], 0, height[i]);
	}
	proc();
}