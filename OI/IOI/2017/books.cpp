#include "books.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6+5;

int n, x, y;
int chk[N], id[N], L[N], R[N];
long ans;

void extend(int &l, int &r) {
	int ll = l, rr = r;
	ll = min(ll, min(L[id[l]], L[id[r]]));
	rr = max(rr, max(R[id[l]], R[id[r]]));

	while(ll < l || r < rr) {
		if(ll < l) --l;
		else ++r;
		ll = min(ll, min(L[id[l]], L[id[r]]));
		rr = max(rr, max(R[id[l]], R[id[r]]));
	}
}

long solve(int l, int r) {
	long ret = 0;
	while(x < l || r < y) {
		int a_l = l, a_r = r;
		int b_l = l, b_r = r;
		long cost_l = 0, cost_r = 0;
		bool valid_l = false, valid_r = false;
		while(x < a_l && a_r == r) {
			cost_l += 2;
			extend(--a_l, a_r);
		}
		if(a_r > r) valid_l = true;
		while(b_r < y && b_l == l) {
			cost_r += 2;
			extend(b_l, ++b_r);
		}
		if(b_l < l) valid_r = true;
		if(valid_l && valid_r) ret += min(cost_l, cost_r);
		else ret += cost_l + cost_r;

		l = min(a_l, b_l), r = max(a_r, b_r);
	}
	return ret;
}
 

long minimum_walk(vector<int> p, int s) {
	n = p.size(), x = y = s;

	for(int i = 0; i < n; i++) ans += abs(i - p[i]);
	for(int i = 0, ptr = 0; i < n; i++) if(!chk[i]) {
		int now = i;
		++ptr;
		L[ptr] = R[ptr] = i;
		while(!chk[now]) {
			chk[now] = true, id[now] = ptr;
			L[ptr] = min(L[ptr], now);
			R[ptr] = max(R[ptr], now);
			now = p[now];
		}
		if(i != p[i]) {
			x = min(x, L[ptr]);
			y = max(y, R[ptr]);
		}
	}

	int t_l = s, t_r = s;
	extend(t_l, t_r);
	return ans + solve(t_l, t_r);
}
