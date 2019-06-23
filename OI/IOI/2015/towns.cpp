#include "towns.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 205;

int hubDistance(int n, int sub) {
	vector<vector<int> > d(N, vector<int>(N, 0));
	auto get_dist = [&](int a, int b) {
		if(a == b) return 0;
		else if(d[a][b]) return d[a][b];
		else return d[a][b] = d[b][a] = getDistance(a, b);
	};	

	int a, b;
	for(int i = 0, mx = -1; i < n; i++) if(get_dist(0, i) > mx) a = i, mx = get_dist(0, i);
	for(int i = 0, mx = -1; i < n; i++) if(get_dist(a, i) > mx) b = i, mx = get_dist(a, i);

	int root1 = -1, root2 = -1, ans = INT_MAX;
	for(int i = 0; i < n; i++) {
		int pos = (get_dist(a, i) + get_dist(a, 0) - get_dist(i, 0)) / 2;
		int now = max(pos, get_dist(a, b) - pos);
		if(now <= ans) {
			if(now < ans) root1 = pos, root2 = -1;
			else {
				if(root1 == -1) root1 = pos;
				else if(pos != root1) root2 = pos;
			}
			ans = now;
		}
	}

	auto chk = [&](int root) {
		int l = 0, r = 0;
		for(int i = 0; i < n; i++) {
			int pos = (get_dist(a, i) + get_dist(a, 0) - get_dist(i, 0)) / 2;
			if(pos < root) ++l;
			if(pos > root) ++r;
		}
		return (l <= n / 2 && r <= n / 2);
	};
	if(!chk(root1)) root1 = -1;
	if(root2 == -1 || !chk(root2)) root2 = -1;
	if(root1 == -1 && root2 == -1) return -ans;

	if(root1 < root2) swap(root1, root2);

	auto same = [&](int x, int y) {
		if(x == y) return true;
		int d = get_dist(a, x) + get_dist(0, y) - get_dist(a, 0);
		return d != get_dist(x, y);
	};

	auto vote = [&](int root) {
		int last = -1, cnt = 0, ret, sz = 0;
		bool sm = false;
		vector<int> v;
		for(int i = 0; i < n; i++) {
			int pos = (get_dist(a, i) + get_dist(a, 0) - get_dist(i, 0)) / 2;
			if(pos == root) v.emplace_back(i);
		}
		for(int i = 0; i < v.size(); i++) {
			if(last == -1) last = v[i], ++cnt;
			else if(same(v[i], last)) ++cnt;
			else if(--cnt == 0) last = -1;
		}
		if(!cnt) return true;
		ret = last, last = -1, cnt = 0;
		for(int i = 0; i < v.size(); i++) {
			if(last == -1) {
				if(same(v[i], ret)) sm = true, ++sz;
				last = v[i], ++cnt;
			} else if(same(v[i], last)) sz += sm, ++cnt;
			else {
				if(!sm && same(v[i], ret)) ++sz;
				if(--cnt == 0) last = -1, sm = false;
			}
		}
		return sz <= n / 2;
	};

	if(!vote(root1) && (root2 == -1 || !vote(root2))) return -ans;
	else return ans;
}
