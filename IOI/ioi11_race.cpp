#include "race.h"
#include <bits/stdc++.h>
 
#define pii pair<int, int>
#define x first
#define y second
 
using namespace std;
 
const int N = 2e5 + 5;
const int M = 1e6 + 5;
 
int n, k;
int ans = -1, centroid, mxnode, cnt = 0;
int dep[N], path[M], dp[M];
vector<vector<pii> > g(N);
bitset<N> chk;
 
int subtree(int u, int p) {
	dep[u] = 1;
	for(pii v : g[u]) if(!chk[v.x] && v.x != p) {
		dep[u] += subtree(v.x, u);
	}
	return dep[u];
}
 
void centdecomp(int u, int p, int all) {
	int ret = all - dep[u];
	for(pii v : g[u]) if(!chk[v.x] && v.x != p) {
		centdecomp(v.x, u, all);
		ret = max(ret, dep[v.x]);
	}
	if(ret < mxnode) centroid = u, mxnode = ret;
}
 
void dfs(int u, int p, int cost, int edge, bool fill) {
	if(cost > k) return;
	if(!fill) {
		if(dp[k - cost] == cnt && (edge + path[k - cost] < ans || ans == -1)) ans = edge + path[k - cost];
		if(cost == k && (edge < ans || ans == -1)) ans = edge;
	} else if(dp[cost] < cnt || edge < path[cost]) dp[cost] = cnt, path[cost] = edge;
 
	for(pii v : g[u]) if(!chk[v.x] && v.x != p) {
		dfs(v.x, u, cost + v.y, edge + 1, fill);
	}
}
 
void proc(int u) {
	cnt++;
	if(subtree(u, -1) <= 1) return;
	mxnode = dep[u] + 1;
	centdecomp(u, -1, dep[u]);
	for(pii v : g[centroid]) if(!chk[v.x]) {
		dfs(v.x, centroid, v.y, 1, false);
		dfs(v.x, centroid, v.y, 1, true);
	}
	chk[centroid] = 1;
	for(pii v : g[centroid]) if(!chk[v.x]) {
		proc(v.x);
	}
}
 
int best_path(int N, int K, int H[][2], int L[])
{
	n = N, k = K;
	for(int i = 0; i < N - 1; i++) {
		g[H[i][0]].emplace_back(H[i][1], L[i]);
		g[H[i][1]].emplace_back(H[i][0], L[i]);
	}
 
	proc(0);
 
	return ans;
}