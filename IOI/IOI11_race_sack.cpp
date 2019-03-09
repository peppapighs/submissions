#include <race.h>
#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, k, ans = INT_MAX;
int hv[N], in[N], out[N], pos[N], par[N], dep[N];
long d[N];
map<long, int> mp;
vector<pii> g[N];

int gethv(int u, int p) {
	static int idx = 0;
	int sz = 1; pii ret(0, -1);
	par[u] = p, in[u] = ++idx, pos[idx] = u;
	for(pii v : g[u]) if(v.x != p) {
		d[v.x] = d[u] + v.y;
		dep[v.x] = dep[u] + 1;
		int z = gethv(v.x, u);
		sz += z, ret = max(ret, pii(z, v.x));
	}
	out[u] = idx, hv[u] = ret.y;
	return sz;
}

void add(int u) {
	if(!mp.count(d[u])) mp[d[u]] = dep[u];
	else mp[d[u]] = min(mp[d[u]], dep[u]);
}

void getans(int u, int lca) {
	long ret = k - d[u] + 2*d[lca];
	if(mp.count(ret)) {
		int z = mp[ret] + dep[u] - 2*dep[lca];
		ans = min(ans, z);
	}
}

void dfs(int u, int p, bool keep) {
	for(pii v : g[u]) if(v.x != p && v.x != hv[u]) dfs(v.x, u, 0);
	if(hv[u] != -1) dfs(hv[u], u, 1);
	getans(u, u), add(u);
	for(pii v : g[u]) if(v.x != p && v.x != hv[u]) {
		for(int i = in[v.x]; i <= out[v.x]; i++) getans(pos[i], u);
		for(int i = in[v.x]; i <= out[v.x]; i++) add(pos[i]);
	}
	if(!keep) mp.clear();
}

int best_path(int N, int K, int H[][2], int L[]) {
	n = N, k = K;
	for(int i = 0; i < N - 1; i++) {
		g[H[i][0]].emplace_back(H[i][1], L[i]);
		g[H[i][1]].emplace_back(H[i][0], L[i]);
	}
	gethv(0, 0);
	dfs(0, 0, 1);
 
	return ans == INT_MAX ? -1 : ans;
}