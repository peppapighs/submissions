#include "wiring.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

#define long long long

using namespace std;

const int N = 2e5+5;

void update(long t[], int x, long k) {
	for(t[x += N] = k; x != 1; x >>= 1)
		t[x>>1] = min(t[x], t[x^1]);
}

long query(long t[], int l, int r) {
	long ret = 1e18;
	for(l += N, r += N+1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) ret = min(ret, t[l++]);
		if(r & 1) ret = min(ret, t[--r]);
	}
	return ret;
}

int n;
int sz_l[N], sz_r[N], pre[N], pos[N];
long sum_l[N], sum_r[N];
long dp[N], t1[N<<1], t2[N<<1];
vector<pii> all;

long min_total_length(vector<int> r, vector<int> b) {
	n = r.size() + b.size();

	for(int i : r) all.emplace_back(i, 0);
	for(int i : b) all.emplace_back(i, 1);
	all.emplace_back(-1e9, -1e9), all.emplace_back(1e9, 1e9);
	sort(all.begin(), all.end());

	for(int i = 1; i <= n; i++) {
		if(all[i].y == all[i-1].y) {
			sz_l[i] = sz_l[i-1];
			pre[i] = pre[i-1];
			sum_l[i] = sum_l[i-1];
		} else pre[i] = i;
		sum_l[i] += all[i].x - all[pre[i]].x;
		++sz_l[i];
	}
	for(int i = n; i; i--) {
		if(all[i].y == all[i + 1].y) {
			sz_r[i] = sz_r[i+1];
			pos[i] = pos[i+1];
			sum_r[i] = sum_r[i+1];
		} else pos[i] = i;
		sum_r[i] += all[pos[i]].x - all[i].x;
		++sz_r[i];
	}

	for(int i = 1; i <= n; i++) {
		dp[i] = 1e18;
		if(all[i].y == 0) {
			auto it = lower_bound(b.begin(), b.end(), all[i].x);
			if(it != b.end()) dp[i] = min(dp[i], dp[i-1] + *it - all[i].x);
			if(it != b.begin()) dp[i] = min(dp[i], dp[i-1] + all[i].x - *--it);
		} else {
			auto it = lower_bound(r.begin(), r.end(), all[i].x);
			if(it != r.end()) dp[i] = min(dp[i], dp[i-1] + *it - all[i].x);
			if(it != r.begin()) dp[i] = min(dp[i], dp[i-1] + all[i].x - *--it);
		}
		if(pre[i] != 1) {
			int l = pre[pre[i] - 1];
			dp[i] = min(dp[i], query(t1, max(l, pre[i] - sz_l[i]), pre[i]-1) + sum_l[i] + 1ll * sz_l[i] * (all[pre[i]].x - all[pre[i]-1].x));
			dp[i] = min(dp[i], query(t2, l, pre[i] - sz_l[i] - 1) + sum_l[i]);
		}
		update(t1, i, dp[i - 1] + sum_r[i]);
		update(t2, i, dp[i - 1] + sum_r[i] + 1ll * sz_r[i] * (all[pos[i]+1].x - all[pos[i]].x));
	}

	return dp[n];
}
